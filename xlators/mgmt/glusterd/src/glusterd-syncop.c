/*
   Copyright (c) 2012-2012 Red Hat, Inc. <http://www.redhat.com>
   This file is part of GlusterFS.

   This file is licensed to you under your choice of the GNU Lesser
   General Public License, version 3 or any later version (LGPLv3 or
   later), or the GNU General Public License, version 2 (GPLv2), in all
   cases as published by the Free Software Foundation.
*/
/* rpc related syncops */
#include "rpc-clnt.h"
#include "protocol-common.h"
#include "xdr-generic.h"
#include "glusterd1-xdr.h"
#include "glusterd-syncop.h"

#include "glusterd.h"
#include "glusterd-op-sm.h"
#include "glusterd-utils.h"

static inline void
// 障碍，屏障，分界线
gd_synctask_barrier_wait (struct syncargs *args, int count)
{
        glusterd_conf_t *conf = THIS->private;

        synclock_unlock (&conf->big_lock);
        // contain barrier wait
        synctask_barrier_wait (args, count);
        synclock_lock (&conf->big_lock);

	syncbarrier_destroy (&args->barrier);
}

static void
gd_collate_errors (struct syncargs *args, int op_ret, int op_errno,
                   char *op_errstr)
{
        if (args->op_ret)
                return;
        args->op_ret = op_ret;
        args->op_errno = op_errno;
        if (op_ret && op_errstr && strcmp (op_errstr, ""))
                args->errstr = gf_strdup (op_errstr);
}

static void
gd_syncargs_init (struct syncargs *args, dict_t *op_ctx)
{
        args->dict = op_ctx;
        pthread_mutex_init (&args->lock_dict, NULL);
}

static void
gd_stage_op_req_free (gd1_mgmt_stage_op_req *req)
{
        if (!req)
                return;

        GF_FREE (req->buf.buf_val);
        GF_FREE (req);
}

static void
gd_commit_op_req_free (gd1_mgmt_commit_op_req *req)
{
        if (!req)
                return;

        GF_FREE (req->buf.buf_val);
        GF_FREE (req);
}

static void
gd_brick_op_req_free (gd1_mgmt_brick_op_req *req)
{
        if (!req)
                return;

        if (strcmp (req->name, "") != 0)
                GF_FREE (req->name);
        GF_FREE (req->input.input_val);
        GF_FREE (req);
}

int
gd_syncop_submit_request (struct rpc_clnt *rpc, void *req,
                          void *cookie, rpc_clnt_prog_t *prog,
                          int procnum, fop_cbk_fn_t cbkfn, xdrproc_t xdrproc)
{
        int            ret      = -1;
        struct iobuf  *iobuf    = NULL;
        struct iobref *iobref   = NULL;
        int            count    = 0;
        struct iovec   iov      = {0, };
        ssize_t        req_size = 0;
        call_frame_t  *frame    = NULL;

        GF_ASSERT (rpc);
        if (!req)
                goto out;

        req_size = xdr_sizeof (xdrproc, req);
        iobuf = iobuf_get2 (rpc->ctx->iobuf_pool, req_size);
        if (!iobuf)
                goto out;

        iobref = iobref_new ();
        if (!iobref)
                goto out;

        frame = create_frame (THIS, THIS->ctx->pool);
        if (!frame)
                goto out;

        iobref_add (iobref, iobuf);

        iov.iov_base = iobuf->ptr;
        iov.iov_len  = iobuf_pagesize (iobuf);

        /* Create the xdr payload */
        ret = xdr_serialize_generic (iov, req, xdrproc);
        if (ret == -1)
                goto out;

        iov.iov_len = ret;
        count = 1;

        frame->local = cookie;

        /* Send the msg */
        ret = rpc_clnt_submit (rpc, prog, procnum, cbkfn,
                               &iov, count, NULL, 0, iobref,
                               frame, NULL, 0, NULL, 0, NULL);

        /* TODO: do we need to start ping also? */

out:
        iobref_unref (iobref);
        iobuf_unref (iobuf);

        return ret;
}

/* Defined in glusterd-rpc-ops.c */
extern struct rpc_clnt_program gd_mgmt_prog;
extern struct rpc_clnt_program gd_brick_prog;

static int
glusterd_syncop_aggr_rsp_dict (glusterd_op_t op, dict_t *aggr, dict_t *rsp)
{
        int ret = 0;

        switch (op) {
        case GD_OP_REPLACE_BRICK:
                ret = glusterd_rb_use_rsp_dict (aggr, rsp);
                if (ret)
                        goto out;
        break;

        case GD_OP_SYNC_VOLUME:
                ret = glusterd_sync_use_rsp_dict (aggr, rsp);
                if (ret)
                        goto out;
        break;

        case GD_OP_PROFILE_VOLUME:
                ret = glusterd_profile_volume_use_rsp_dict (aggr, rsp);
                if (ret)
                        goto out;
        break;

        case GD_OP_GSYNC_SET:
                ret = glusterd_gsync_use_rsp_dict (aggr, rsp, NULL);
                if (ret)
                        goto out;
        break;

        case GD_OP_STATUS_VOLUME:
                ret = glusterd_volume_status_copy_to_op_ctx_dict (aggr, rsp);
                if (ret)
                        goto out;
        break;

        case GD_OP_REBALANCE:
        case GD_OP_DEFRAG_BRICK_VOLUME:
                ret = glusterd_volume_rebalance_use_rsp_dict (aggr, rsp);
                if (ret)
                        goto out;
        break;

        case GD_OP_HEAL_VOLUME:
                ret = glusterd_volume_heal_use_rsp_dict (aggr, rsp);
                if (ret)
                        goto out;

        break;

        case GD_OP_CLEARLOCKS_VOLUME:
                ret = glusterd_volume_clearlocks_use_rsp_dict (aggr, rsp);
                if (ret)
                        goto out;

        break;

        default:
        break;
        }
out:
        return ret;
}

int32_t
_gd_syncop_mgmt_lock_cbk (struct rpc_req *req, struct iovec *iov,
                          int count, void *myframe)
{
        int                         ret         = -1;
        struct syncargs             *args       = NULL;
        gd1_mgmt_cluster_lock_rsp   rsp         = {{0},};
        call_frame_t                *frame      = NULL;

        frame  = myframe;
        args   = frame->local;
        frame->local = NULL;

        if (-1 == req->rpc_status) {
                args->op_errno = ENOTCONN;
                goto out;
        }

        ret = xdr_to_generic (*iov, &rsp,
                              (xdrproc_t)xdr_gd1_mgmt_cluster_lock_rsp);
        if (ret < 0)
                goto out;

        gd_collate_errors (args, rsp.op_ret, rsp.op_errno, NULL);
        uuid_copy (args->uuid, rsp.uuid);

out:
        STACK_DESTROY (frame->root);
        synctask_barrier_wake(args);
        return 0;
}

int32_t
gd_syncop_mgmt_lock_cbk (struct rpc_req *req, struct iovec *iov,
                         int count, void *myframe)
{
        return glusterd_big_locked_cbk (req, iov, count, myframe,
                                        _gd_syncop_mgmt_lock_cbk);
}

int
gd_syncop_mgmt_lock (struct rpc_clnt *rpc, struct syncargs *args,
                     uuid_t my_uuid, uuid_t recv_uuid)
{
        int                       ret = -1;
        gd1_mgmt_cluster_lock_req req  = {{0},};
        glusterd_conf_t           *conf = THIS->private;

        uuid_copy (req.uuid, my_uuid);
        synclock_unlock (&conf->big_lock);
        ret = gd_syncop_submit_request (rpc, &req, args, &gd_mgmt_prog,
                                        GLUSTERD_MGMT_CLUSTER_LOCK,
                                        gd_syncop_mgmt_lock_cbk,
                                        (xdrproc_t) xdr_gd1_mgmt_cluster_lock_req);
        synclock_lock (&conf->big_lock);
        return ret;
}

int32_t
_gd_syncop_mgmt_unlock_cbk (struct rpc_req *req, struct iovec *iov,
                            int count, void *myframe)
{
        int                         ret         = -1;
        struct syncargs             *args       = NULL;
        gd1_mgmt_cluster_unlock_rsp rsp         = {{0},};
        call_frame_t                *frame      = NULL;

        frame = myframe;
        args  = frame->local;
        frame->local = NULL;

        if (-1 == req->rpc_status) {
                args->op_errno = ENOTCONN;
                goto out;
        }

        ret = xdr_to_generic (*iov, &rsp,
                              (xdrproc_t)xdr_gd1_mgmt_cluster_unlock_rsp);
        if (ret < 0)
                goto out;

        gd_collate_errors (args, rsp.op_ret, rsp.op_errno, NULL);
        uuid_copy (args->uuid, rsp.uuid);

out:
        STACK_DESTROY (frame->root);
        synctask_barrier_wake(args);
        return 0;
}

int32_t
gd_syncop_mgmt_unlock_cbk (struct rpc_req *req, struct iovec *iov,
                           int count, void *myframe)
{
        return glusterd_big_locked_cbk (req, iov, count, myframe,
                                        _gd_syncop_mgmt_unlock_cbk);
}


int
gd_syncop_mgmt_unlock (struct rpc_clnt *rpc, struct syncargs *args,
                       uuid_t my_uuid, uuid_t recv_uuid)
{
        int                         ret     = -1;
        gd1_mgmt_cluster_unlock_req req     = {{0},};
        glusterd_conf_t             *conf   = THIS->private;

        uuid_copy (req.uuid, my_uuid);
        synclock_unlock (&conf->big_lock);
        ret = gd_syncop_submit_request (rpc, &req, args, &gd_mgmt_prog,
                                        GLUSTERD_MGMT_CLUSTER_UNLOCK,
                                        gd_syncop_mgmt_unlock_cbk,
                                        (xdrproc_t) xdr_gd1_mgmt_cluster_lock_req);
        synclock_lock (&conf->big_lock);
        return ret;
}

int32_t
_gd_syncop_stage_op_cbk (struct rpc_req *req, struct iovec *iov,
                         int count, void *myframe)
{
        int                         ret         = -1;
        gd1_mgmt_stage_op_rsp       rsp         = {{0},};
        struct syncargs             *args       = NULL;
        xlator_t                    *this       = NULL;
        dict_t                      *rsp_dict   = NULL;
        call_frame_t                *frame      = NULL;

        this  = THIS;
        frame = myframe;
        args  = frame->local;
        frame->local = NULL;

        if (-1 == req->rpc_status) {
                args->op_ret   = -1;
                args->op_errno = ENOTCONN;
                goto out;
        }

        ret = xdr_to_generic (*iov, &rsp,
                              (xdrproc_t)xdr_gd1_mgmt_stage_op_rsp);
        if (ret < 0)
                goto out;

        if (rsp.dict.dict_len) {
                /* Unserialize the dictionary */
                rsp_dict  = dict_new ();

                ret = dict_unserialize (rsp.dict.dict_val,
                                        rsp.dict.dict_len,
                                        &rsp_dict);
                if (ret < 0) {
                        GF_FREE (rsp.dict.dict_val);
                        goto out;
                } else {
                        rsp_dict->extra_stdfree = rsp.dict.dict_val;
                }
        }

        gd_collate_errors (args, rsp.op_ret, rsp.op_errno, rsp.op_errstr);
        uuid_copy (args->uuid, rsp.uuid);
        if (rsp.op == GD_OP_REPLACE_BRICK) {
                pthread_mutex_lock (&args->lock_dict);
                {
                        ret = glusterd_syncop_aggr_rsp_dict (rsp.op, args->dict,
                                                             rsp_dict);
                        if (ret)
                                gf_log (this->name, GF_LOG_ERROR, "%s",
                                        "Failed to aggregate response from "
                                        " node/brick");
                }
                pthread_mutex_unlock (&args->lock_dict);
        }

out:
        if (rsp_dict)
                dict_unref (rsp_dict);

        STACK_DESTROY (frame->root);
        synctask_barrier_wake(args);
        return 0;
}

int32_t
gd_syncop_stage_op_cbk (struct rpc_req *req, struct iovec *iov,
                        int count, void *myframe)
{
        return glusterd_big_locked_cbk (req, iov, count, myframe,
                                        _gd_syncop_stage_op_cbk);
}


int
gd_syncop_mgmt_stage_op (struct rpc_clnt *rpc, struct syncargs *args,
                         uuid_t my_uuid, uuid_t recv_uuid, int op,
                         dict_t *dict_out, dict_t *op_ctx)
{
        gd1_mgmt_stage_op_req *req  = NULL;
        glusterd_conf_t       *conf = THIS->private;
        int                   ret   = -1;

        req = GF_CALLOC (1, sizeof (*req), gf_gld_mt_mop_stage_req_t);
        if (!req)
                goto out;

        uuid_copy (req->uuid, my_uuid);
        req->op = op;

        ret = dict_allocate_and_serialize (dict_out,
                                           &req->buf.buf_val, &req->buf.buf_len);
        if (ret)
                goto out;

        synclock_unlock (&conf->big_lock);
        ret = gd_syncop_submit_request (rpc, req, args, &gd_mgmt_prog,
                                        GLUSTERD_MGMT_STAGE_OP,
                                        gd_syncop_stage_op_cbk,
                                        (xdrproc_t) xdr_gd1_mgmt_stage_op_req);
        synclock_lock (&conf->big_lock);
out:
        gd_stage_op_req_free (req);
        return ret;

}

int32_t
_gd_syncop_brick_op_cbk (struct rpc_req *req, struct iovec *iov,
                        int count, void *myframe)
{
        struct syncargs        *args  = NULL;
        gd1_mgmt_brick_op_rsp  rsp   = {0,};
        int                    ret   = -1;
        call_frame_t           *frame = NULL;

        frame = myframe;
        args = frame->local;
        frame->local = NULL;

        /* initialize */
        args->op_ret   = -1;
        args->op_errno = EINVAL;

        if (-1 == req->rpc_status) {
                args->op_errno = ENOTCONN;
                goto out;
        }

        ret = xdr_to_generic (*iov, &rsp,
                              (xdrproc_t)xdr_gd1_mgmt_brick_op_rsp);
        if (ret < 0)
                goto out;

        if (rsp.output.output_len) {
                args->dict  = dict_new ();
                if (!args->dict) {
                        ret = -1;
                        args->op_errno = ENOMEM;
                        goto out;
                }

                ret = dict_unserialize (rsp.output.output_val,
                                        rsp.output.output_len,
                                        &args->dict);
                if (ret < 0)
                        goto out;
        }

        args->op_ret = rsp.op_ret;
        args->op_errno = rsp.op_errno;
        args->errstr = gf_strdup (rsp.op_errstr);

out:
        free (rsp.op_errstr);
        free (rsp.output.output_val);

        STACK_DESTROY (frame->root);
        __wake (args);

        return 0;
}

int32_t
gd_syncop_brick_op_cbk (struct rpc_req *req, struct iovec *iov,
                        int count, void *myframe)
{
        return glusterd_big_locked_cbk (req, iov, count, myframe,
                                        _gd_syncop_brick_op_cbk);
}

int
gd_syncop_mgmt_brick_op (struct rpc_clnt *rpc, glusterd_pending_node_t *pnode,
                         int op, dict_t *dict_out, dict_t *op_ctx,
                         char **errstr)
{
        struct syncargs        args = {0, };
        gd1_mgmt_brick_op_req  *req  = NULL;
        int                    ret  = 0;
        xlator_t               *this = NULL;

        this = THIS;
        args.op_ret = -1;
        args.op_errno = ENOTCONN;

        if ((pnode->type == GD_NODE_NFS) ||
            ((pnode->type == GD_NODE_SHD) &&
            (op == GD_OP_STATUS_VOLUME))) {
                ret = glusterd_node_op_build_payload
                        (op, &req, dict_out);

        } else {
                ret = glusterd_brick_op_build_payload
                        (op, pnode->node, &req, dict_out);

        }

        if (ret)
                goto out;

        GD_SYNCOP (rpc, (&args), gd_syncop_brick_op_cbk,
                   req, &gd_brick_prog, req->op,
                   xdr_gd1_mgmt_brick_op_req);

        if (args.errstr && errstr)
                *errstr = args.errstr;
        else
                GF_FREE (args.errstr);

        if (GD_OP_STATUS_VOLUME == op) {
                ret = dict_set_int32 (args.dict, "index", pnode->index);
                if (ret) {
                        gf_log (this->name, GF_LOG_ERROR,
                                "Error setting index on brick status"
                                " rsp dict");
                        args.op_ret = -1;
                        goto out;
                }
        }
        if (args.op_ret == 0)
                glusterd_handle_node_rsp (dict_out, pnode->node, op,
                                          args.dict, op_ctx, errstr,
                                          pnode->type);

out:
        errno = args.op_errno;
        if (args.dict)
                dict_unref (args.dict);
        gd_brick_op_req_free (req);
        return args.op_ret;

}

int32_t
_gd_syncop_commit_op_cbk (struct rpc_req *req, struct iovec *iov,
                          int count, void *myframe)
{
        int                         ret         = -1;
        gd1_mgmt_commit_op_rsp      rsp         = {{0},};
        struct syncargs             *args       = NULL;
        xlator_t                    *this       = NULL;
        dict_t                      *rsp_dict   = NULL;
        call_frame_t                *frame      = NULL;

        this  = THIS;
        frame = myframe;
        args  = frame->local;
        frame->local = NULL;

        if (-1 == req->rpc_status) {
                args->op_errno = ENOTCONN;
                goto out;
        }

        ret = xdr_to_generic (*iov, &rsp,
                              (xdrproc_t)xdr_gd1_mgmt_commit_op_rsp);
        if (ret < 0) {
                goto out;
        }

        if (rsp.dict.dict_len) {
                /* Unserialize the dictionary */
                rsp_dict  = dict_new ();

                ret = dict_unserialize (rsp.dict.dict_val,
                                        rsp.dict.dict_len,
                                        &rsp_dict);
                if (ret < 0) {
                        GF_FREE (rsp.dict.dict_val);
                        goto out;
                } else {
                        rsp_dict->extra_stdfree = rsp.dict.dict_val;
                }
        }

        gd_collate_errors (args, rsp.op_ret, rsp.op_errno, rsp.op_errstr);
        uuid_copy (args->uuid, rsp.uuid);
        pthread_mutex_lock (&args->lock_dict);
        {
                ret = glusterd_syncop_aggr_rsp_dict (rsp.op, args->dict,
                                                     rsp_dict);
                if (ret)
                        gf_log (this->name, GF_LOG_ERROR, "%s",
                                "Failed to aggregate response from "
                                " node/brick");
        }
        pthread_mutex_unlock (&args->lock_dict);
out:
        if (rsp_dict)
                dict_unref (rsp_dict);

        STACK_DESTROY (frame->root);
        synctask_barrier_wake(args);

        return 0;
}

int32_t
gd_syncop_commit_op_cbk (struct rpc_req *req, struct iovec *iov,
                         int count, void *myframe)
{
        return glusterd_big_locked_cbk (req, iov, count, myframe,
                                        _gd_syncop_commit_op_cbk);
}


int
gd_syncop_mgmt_commit_op (struct rpc_clnt *rpc, struct syncargs *args,
                          uuid_t my_uuid, uuid_t recv_uuid,
                          int op, dict_t *dict_out, dict_t *op_ctx)
{
        glusterd_conf_t        *conf = THIS->private;
        gd1_mgmt_commit_op_req *req  = NULL;
        int                    ret  = -1;

        req = GF_CALLOC (1, sizeof (*req), gf_gld_mt_mop_commit_req_t);
        if (!req)
                goto out;

        uuid_copy (req->uuid, my_uuid);
        req->op = op;

        ret = dict_allocate_and_serialize (dict_out,
                                           &req->buf.buf_val, &req->buf.buf_len);
        if (ret)
                goto out;

        synclock_unlock (&conf->big_lock);
        ret = gd_syncop_submit_request (rpc, req, args, &gd_mgmt_prog,
                                        GLUSTERD_MGMT_COMMIT_OP ,
                                        gd_syncop_commit_op_cbk,
                                        (xdrproc_t) xdr_gd1_mgmt_commit_op_req);
        synclock_lock (&conf->big_lock);
out:
        gd_commit_op_req_free (req);
        return ret;
}

int
gd_build_peers_list (struct list_head *peers, struct list_head *xact_peers,
                     glusterd_op_t op)
{
        glusterd_peerinfo_t *peerinfo = NULL;
        int                 npeers      = 0;

        list_for_each_entry (peerinfo, peers, uuid_list) {
                if (!peerinfo->connected)
                        continue;
                if (op != GD_OP_SYNC_VOLUME &&
                    peerinfo->state.state != GD_FRIEND_STATE_BEFRIENDED)
                        continue;
                list_add_tail (&peerinfo->op_peers_list, xact_peers);
                npeers++;
        }
        return npeers;
}

int
gd_lock_op_phase (struct list_head *peers, glusterd_op_t op, dict_t *op_ctx,
                  char **op_errstr, int npeers)
{
        int                 ret         = -1;
        int                 peer_cnt    = 0;
        uuid_t              peer_uuid   = {0};
        xlator_t            *this       = NULL;
        glusterd_peerinfo_t *peerinfo   = NULL;
        struct syncargs     args        = {0};

        if (!npeers) {
                ret = 0;
                goto out;
        }

        this = THIS;
        synctask_barrier_init((&args));
        peer_cnt = 0;
        list_for_each_entry (peerinfo, peers, op_peers_list) {
                gd_syncop_mgmt_lock (peerinfo->rpc, &args, MY_UUID, peer_uuid);
                peer_cnt++;
        }
        gd_synctask_barrier_wait((&args), peer_cnt);
        ret = args.op_ret;
        if (ret) {
                gf_asprintf (op_errstr, "Another transaction could be "
                             "in progress. Please try again after "
                             "sometime.");
                gf_log (this->name, GF_LOG_ERROR, "Failed to acquire lock");
                goto out;
        }

        ret = 0;
out:
        return ret;
}

int
gd_stage_op_phase (struct list_head *peers, glusterd_op_t op, dict_t *op_ctx,
                   dict_t *req_dict, char **op_errstr, int npeers)
{
        int                 ret             = -1;
        int                 peer_cnt           = 0;
        dict_t              *rsp_dict       = NULL;
        char                *hostname       = NULL;
        xlator_t            *this           = NULL;
        glusterd_peerinfo_t *peerinfo       = NULL;
        uuid_t              tmp_uuid        = {0};
        char                *errstr         = NULL;
        struct syncargs     args            = {0};

        this = THIS;
        ret = -1;
        rsp_dict = dict_new ();
        if (!rsp_dict)
                goto out;

        ret = glusterd_op_stage_validate (op, req_dict, op_errstr, rsp_dict);
        if (ret) {
                hostname = "localhost";
                goto stage_done;
        }

        if ((op == GD_OP_REPLACE_BRICK) ||
            (op == GD_OP_CLEARLOCKS_VOLUME)) {
                ret = glusterd_syncop_aggr_rsp_dict (op, op_ctx, rsp_dict);
                if (ret) {
                        gf_log (this->name, GF_LOG_ERROR, "%s",
                                (*op_errstr)? *op_errstr: "Failed to aggregate "
                                "response from node/brick");
                        goto out;
                }
        }
        dict_unref (rsp_dict);
        rsp_dict = NULL;

stage_done:
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR, LOGSTR_STAGE_FAIL,
                        gd_op_list[op], hostname, (*op_errstr) ? ":" : " ",
                        (*op_errstr) ? *op_errstr : " ");
                if (op_errstr == NULL)
                        gf_asprintf (op_errstr, OPERRSTR_STAGE_FAIL, hostname);
                goto out;
        }

        if (!npeers) {
                ret = 0;
                goto out;
        }

        gd_syncargs_init (&args, op_ctx);
        synctask_barrier_init((&args));
        peer_cnt = 0;
        list_for_each_entry (peerinfo, peers, op_peers_list) {
                ret = gd_syncop_mgmt_stage_op (peerinfo->rpc, &args,
                                               MY_UUID, tmp_uuid,
                                               op, req_dict, op_ctx);
                peer_cnt++;
        }
        gd_synctask_barrier_wait((&args), peer_cnt);
        ret = args.op_ret;
        if (dict_get_str (op_ctx, "errstr", &errstr) == 0)
                *op_errstr = gf_strdup (errstr);

out:
        if (rsp_dict)
                dict_unref (rsp_dict);
        return ret;
}

int
gd_commit_op_phase (struct list_head *peers, glusterd_op_t op, dict_t *op_ctx,
                    dict_t *req_dict, char **op_errstr, int npeers)
{
        dict_t                      *rsp_dict       = NULL;
        int                         peer_cnt        = -1;
        int                         ret             = -1;
        char                        *hostname       = NULL;
        glusterd_peerinfo_t         *peerinfo       = NULL;
        xlator_t                    *this           = NULL;
        uuid_t                      tmp_uuid        = {0};
        char                        *errstr         = NULL;
        struct syncargs             args            = {0};

        this = THIS;
        rsp_dict = dict_new ();
        if (!rsp_dict) {
                ret = -1;
                goto out;
        }

        ret = glusterd_op_commit_perform (op, req_dict, op_errstr, rsp_dict);
        if (ret) {
                hostname = "localhost";
                goto commit_done;
        }
        if (op != GD_OP_SYNC_VOLUME) {
                ret =  glusterd_syncop_aggr_rsp_dict (op, op_ctx, rsp_dict);
                if (ret) {
                        gf_log (this->name, GF_LOG_ERROR, "%s",
                                "Failed to aggregate response "
                                "from node/brick");
                        goto out;
                }
        }
        dict_unref (rsp_dict);
        rsp_dict = NULL;

commit_done:
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR, LOGSTR_COMMIT_FAIL,
                        gd_op_list[op], hostname, (*op_errstr) ? ":" : " ",
                        (*op_errstr) ? *op_errstr : " ");
                if (*op_errstr == NULL)
                        gf_asprintf (op_errstr, OPERRSTR_COMMIT_FAIL,
                                     hostname);
                goto out;
        }

        if (!npeers) {
                ret = 0;
                goto out;
        }
        gd_syncargs_init (&args, op_ctx);
        synctask_barrier_init((&args));
        peer_cnt = 0;
        list_for_each_entry (peerinfo, peers, op_peers_list) {
                ret = gd_syncop_mgmt_commit_op (peerinfo->rpc, &args,
                                                MY_UUID, tmp_uuid,
                                                op, req_dict, op_ctx);
                peer_cnt++;
        }
        gd_synctask_barrier_wait((&args), peer_cnt);
        ret = args.op_ret;
        if (dict_get_str (op_ctx, "errstr", &errstr) == 0)
                *op_errstr = gf_strdup (errstr);

out:
        if (!ret)
                glusterd_op_modify_op_ctx (op, op_ctx);

        if (rsp_dict)
                dict_unref (rsp_dict);
        return ret;
}

int
gd_unlock_op_phase (struct list_head *peers, glusterd_op_t op, int op_ret,
                    rpcsvc_request_t *req, dict_t *op_ctx, char *op_errstr,
                    int npeers)
{
        glusterd_peerinfo_t *peerinfo   = NULL;
        glusterd_peerinfo_t *tmp        = NULL;
        uuid_t              tmp_uuid    = {0};
        int                 peer_cnt       = 0;
        int                 ret         = -1;
        xlator_t            *this       = NULL;
        struct syncargs     args        = {0};

        if (!npeers) {
                ret = 0;
                goto out;
        }

        this = THIS;
        synctask_barrier_init((&args));
        peer_cnt = 0;
        list_for_each_entry_safe (peerinfo, tmp, peers, op_peers_list) {
                gd_syncop_mgmt_unlock (peerinfo->rpc, &args, MY_UUID, tmp_uuid);
                list_del_init (&peerinfo->op_peers_list);
                peer_cnt++;
        }
        gd_synctask_barrier_wait((&args), peer_cnt);
        ret = args.op_ret;
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR, "Failed to unlock "
                        "on some peer(s)");
        }

out:
        glusterd_op_send_cli_response (op, op_ret, 0, req, op_ctx, op_errstr);
        glusterd_op_clear_op (op);
        glusterd_unlock (MY_UUID);

        return 0;
}

int
gd_get_brick_count (struct list_head *bricks)
{
        glusterd_pending_node_t *pending_node = NULL;
        int                     npeers        = 0;
        list_for_each_entry (pending_node, bricks, list) {
                npeers++;
        }
        return npeers;
}

int
gd_brick_op_phase (glusterd_op_t op, dict_t *op_ctx, dict_t *req_dict, char **op_errstr)
{
        glusterd_pending_node_t *pending_node = NULL;
        struct list_head        selected = {0,};
        xlator_t                *this = NULL;
        int                     brick_count = 0;
        int                     ret = -1;
        rpc_clnt_t              *rpc = NULL;
        dict_t                  *rsp_dict = NULL;
        glusterd_conf_t         *conf = NULL;

        this = THIS;
        conf = this->private;
        rsp_dict = dict_new ();
        if (!rsp_dict) {
                ret = -1;
                goto out;
        }

        INIT_LIST_HEAD (&selected);
        ret = glusterd_op_bricks_select (op, req_dict, op_errstr, &selected);
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR, "%s",
                       (*op_errstr)? *op_errstr: "Brick op failed. Check "
                       "glusterd log file for more details.");
                goto out;
        }

        if (op == GD_OP_HEAL_VOLUME) {
                ret = glusterd_syncop_aggr_rsp_dict (op, op_ctx, rsp_dict);
                if (ret)
                        goto out;
        }
        dict_unref (rsp_dict);
        rsp_dict = NULL;

        brick_count = 0;
        list_for_each_entry (pending_node, &selected, list) {
                rpc = glusterd_pending_node_get_rpc (pending_node);
                if (!rpc) {
                        if (pending_node->type == GD_NODE_REBALANCE) {
                                ret = 0;
                                glusterd_defrag_volume_node_rsp (req_dict,
                                                                 NULL, op_ctx);
                                goto out;
                        }

                        ret = -1;
                        gf_log (this->name, GF_LOG_ERROR, "Brick Op failed "
                                "due to rpc failure.");
                        goto out;
                }
                ret = gd_syncop_mgmt_brick_op (rpc, pending_node, op, req_dict,
                                               op_ctx, op_errstr);
                if (ret)
                        goto out;

                brick_count++;
        }

        ret = 0;
out:
        if (rsp_dict)
                dict_unref (rsp_dict);
        gf_log (this->name, GF_LOG_DEBUG, "Sent op req to %d bricks",
                brick_count);
        return ret;
}

void
gd_sync_task_begin (dict_t *op_ctx, rpcsvc_request_t * req)
{
        int                         ret             = -1;
        int                         npeers          = 0;
        dict_t                      *req_dict       = NULL;
        glusterd_conf_t             *conf           = NULL;
        glusterd_op_t               op              = 0;
        int32_t                     tmp_op          = 0;
        char                        *op_errstr      = NULL;
        xlator_t                    *this           = NULL;

        this = THIS;
        GF_ASSERT (this);
        conf = this->private;
        GF_ASSERT (conf);

        ret = dict_get_int32 (op_ctx, GD_SYNC_OPCODE_KEY, &tmp_op);
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR, "Failed to get volume "
                        "operation");
                goto out;
        }

        op = tmp_op;
        ret = glusterd_lock (MY_UUID);
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR, "Unable to acquire lock");
                gf_asprintf (&op_errstr, "Another transaction is in progress. "
                             "Please try again after sometime.");
                goto out;
        }

        /* storing op globally to access in synctask code paths
         * This is still acceptable, as we are performing this under
         * the 'cluster' lock*/
        glusterd_op_set_op  (op);
        INIT_LIST_HEAD (&conf->xaction_peers);
        npeers = gd_build_peers_list  (&conf->peers, &conf->xaction_peers, op);

        ret = gd_lock_op_phase (&conf->xaction_peers, op, op_ctx, &op_errstr, npeers);
        if (ret)
                goto out;

        ret = glusterd_op_build_payload (&req_dict, &op_errstr, op_ctx);
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR, LOGSTR_BUILD_PAYLOAD,
                        gd_op_list[op]);
                if (op_errstr == NULL)
                        gf_asprintf (&op_errstr, OPERRSTR_BUILD_PAYLOAD);
                goto out;
        }

        ret = gd_stage_op_phase (&conf->xaction_peers, op, op_ctx, req_dict,
                                 &op_errstr, npeers);
        if (ret)
                goto out;

        ret = gd_brick_op_phase (op, op_ctx, req_dict, &op_errstr);
        if (ret)
                goto out;

        ret = gd_commit_op_phase (&conf->xaction_peers, op, op_ctx, req_dict,
                                  &op_errstr, npeers);
        if (ret)
                goto out;

        ret = 0;
out:
        (void) gd_unlock_op_phase (&conf->xaction_peers, op, ret, req,
                                   op_ctx, op_errstr, npeers);

        if (req_dict)
                dict_unref (req_dict);

        if (op_errstr)
                GF_FREE (op_errstr);

        return;
}

int32_t
glusterd_op_begin_synctask (rpcsvc_request_t *req, glusterd_op_t op,
                            void *dict)
{
        int              ret = 0;

        ret = dict_set_int32 (dict, GD_SYNC_OPCODE_KEY, op);
        if (ret) {
                gf_log (THIS->name, GF_LOG_ERROR,
                        "dict set failed for setting operations");
                goto out;
        }

        gd_sync_task_begin (dict, req);
        ret = 0;
out:

        return ret;
}
