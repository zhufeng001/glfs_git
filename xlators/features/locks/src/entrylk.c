/*
   Copyright (c) 2006-2012 Red Hat, Inc. <http://www.redhat.com>
   This file is part of GlusterFS.

   This file is licensed to you under your choice of the GNU Lesser
   General Public License, version 3 or any later version (LGPLv3 or
   later), or the GNU General Public License, version 2 (GPLv2), in all
   cases as published by the Free Software Foundation.
*/
#ifndef _CONFIG_H
#define _CONFIG_H
#include "config.h"
#endif

#include "glusterfs.h"
#include "compat.h"
#include "xlator.h"
#include "inode.h"
#include "logging.h"
#include "common-utils.h"
#include "list.h"

#include "locks.h"
#include "common.h"

static pl_entry_lock_t *
new_entrylk_lock (pl_inode_t *pinode, const char *basename, entrylk_type type,
                  void *trans, pid_t client_pid, gf_lkowner_t *owner,
                  const char *volume)

{
        pl_entry_lock_t *newlock = NULL;

        newlock = GF_CALLOC (1, sizeof (pl_entry_lock_t),
                             gf_locks_mt_pl_entry_lock_t);
        if (!newlock) {
                goto out;
        }

        newlock->basename   = basename ? gf_strdup (basename) : NULL;
        newlock->type       = type;
        newlock->trans      = trans;
        newlock->volume     = volume;
        newlock->client_pid = client_pid;
        newlock->owner      = *owner;

        INIT_LIST_HEAD (&newlock->domain_list);
        INIT_LIST_HEAD (&newlock->blocked_locks);

out:
        return newlock;
}


/**
 * all_names - does a basename represent all names?
 * @basename: name to check
 */

#define all_names(basename) ((basename == NULL) ? 1 : 0)

/**
 * names_conflict - do two names conflict?
 * @n1: name
 * @n2: name
 */

static int
names_conflict (const char *n1, const char *n2)
{
        return all_names (n1) || all_names (n2) || !strcmp (n1, n2);
}


static inline int
__same_entrylk_owner (pl_entry_lock_t *l1, pl_entry_lock_t *l2)
{

        return (is_same_lkowner (&l1->owner, &l2->owner) &&
                (l1->trans  == l2->trans));
}


/**
 * lock_grantable - is this lock grantable?
 * @inode: inode in which to look
 * @basename: name we're trying to lock
 * @type: type of lock
 */
static pl_entry_lock_t *
__lock_grantable (pl_dom_list_t *dom, const char *basename, entrylk_type type)
{
        pl_entry_lock_t *lock = NULL;

        if (list_empty (&dom->entrylk_list))
                return NULL;

        list_for_each_entry (lock, &dom->entrylk_list, domain_list) {
                if (names_conflict (lock->basename, basename))
                        return lock;
        }

        return NULL;
}

static pl_entry_lock_t *
__blocked_lock_conflict (pl_dom_list_t *dom, const char *basename, entrylk_type type)
{
        pl_entry_lock_t *lock = NULL;

        if (list_empty (&dom->blocked_entrylks))
                return NULL;

        list_for_each_entry (lock, &dom->blocked_entrylks, blocked_locks) {
                if (names_conflict (lock->basename, basename))
                        return lock;
        }

        return NULL;
}

static int
__owner_has_lock (pl_dom_list_t *dom, pl_entry_lock_t *newlock)
{
        pl_entry_lock_t *lock = NULL;

        list_for_each_entry (lock, &dom->entrylk_list, domain_list) {
                if (__same_entrylk_owner (lock, newlock))
                        return 1;
        }

        list_for_each_entry (lock, &dom->blocked_entrylks, blocked_locks) {
                if (__same_entrylk_owner (lock, newlock))
                        return 1;
        }

        return 0;
}

static int
names_equal (const char *n1, const char *n2)
{
        return (n1 == NULL && n2 == NULL) || (n1 && n2 && !strcmp (n1, n2));
}

void
pl_print_entrylk (char *str, int size, entrylk_cmd cmd, entrylk_type type,
                  const char *basename, const char *domain)
{
        char *cmd_str = NULL;
        char *type_str = NULL;

        switch (cmd) {
        case ENTRYLK_LOCK:
                cmd_str = "LOCK";
                break;

        case ENTRYLK_LOCK_NB:
                cmd_str = "LOCK_NB";
                break;

        case ENTRYLK_UNLOCK:
                cmd_str = "UNLOCK";
                break;

        default:
                cmd_str = "UNKNOWN";
                break;
        }

        switch (type) {
        case ENTRYLK_RDLCK:
                type_str = "READ";
                break;
        case ENTRYLK_WRLCK:
                type_str = "WRITE";
                break;
        default:
                type_str = "UNKNOWN";
                break;
        }

        snprintf (str, size, "lock=ENTRYLK, cmd=%s, type=%s, basename=%s, domain: %s",
                  cmd_str, type_str, basename, domain);
}


void
entrylk_trace_in (xlator_t *this, call_frame_t *frame, const char *domain,
                  fd_t *fd, loc_t *loc, const char *basename,
                  entrylk_cmd cmd, entrylk_type type)
{
        posix_locks_private_t  *priv = NULL;
        char                    pl_locker[256];
        char                    pl_lockee[256];
        char                    pl_entrylk[256];

        priv = this->private;

        if (!priv->trace)
                return;

        pl_print_locker (pl_locker, 256, this, frame);
        pl_print_lockee (pl_lockee, 256, fd, loc);
        pl_print_entrylk (pl_entrylk, 256, cmd, type, basename, domain);

        gf_log (this->name, GF_LOG_INFO,
                "[REQUEST] Locker = {%s} Lockee = {%s} Lock = {%s}",
                pl_locker, pl_lockee, pl_entrylk);
}


void
entrylk_trace_out (xlator_t *this, call_frame_t *frame, const char *domain,
                   fd_t *fd, loc_t *loc, const char *basename,
                   entrylk_cmd cmd, entrylk_type type, int op_ret, int op_errno)
{
        posix_locks_private_t  *priv = NULL;
        char                    pl_locker[256];
        char                    pl_lockee[256];
        char                    pl_entrylk[256];
        char                    verdict[32];

        priv = this->private;

        if (!priv->trace)
                return;

        pl_print_locker (pl_locker, 256, this, frame);
        pl_print_lockee (pl_lockee, 256, fd, loc);
        pl_print_entrylk (pl_entrylk, 256, cmd, type, basename, domain);
        pl_print_verdict (verdict, 32, op_ret, op_errno);

        gf_log (this->name, GF_LOG_INFO,
                "[%s] Locker = {%s} Lockee = {%s} Lock = {%s}",
                verdict, pl_locker, pl_lockee, pl_entrylk);
}


void
entrylk_trace_block (xlator_t *this, call_frame_t *frame, const char *volume,
                     fd_t *fd, loc_t *loc, const char *basename,
                     entrylk_cmd cmd, entrylk_type type)

{
        posix_locks_private_t  *priv = NULL;
        char                    pl_locker[256];
        char                    pl_lockee[256];
        char                    pl_entrylk[256];

        priv = this->private;

        if (!priv->trace)
                return;

        pl_print_locker (pl_locker, 256, this, frame);
        pl_print_lockee (pl_lockee, 256, fd, loc);
        pl_print_entrylk (pl_entrylk, 256, cmd, type, basename, volume);

        gf_log (this->name, GF_LOG_INFO,
                "[BLOCKED] Locker = {%s} Lockee = {%s} Lock = {%s}",
                pl_locker, pl_lockee, pl_entrylk);
}

/**
 * __find_most_matching_lock - find the lock struct which most matches in order of:
 *                           lock on the exact basename ||
 *                           an all_names lock
 *
 *
 * @inode: inode in which to look
 * @basename: name to search for
 */

static pl_entry_lock_t *
__find_most_matching_lock (pl_dom_list_t *dom, const char *basename)
{
        pl_entry_lock_t *lock;
        pl_entry_lock_t *all = NULL;
        pl_entry_lock_t *exact = NULL;

        if (list_empty (&dom->entrylk_list))
                return NULL;

        list_for_each_entry (lock, &dom->entrylk_list, domain_list) {
                if (all_names (lock->basename))
                        all = lock;
                else if (names_equal (lock->basename, basename))
                        exact = lock;
        }

        return (exact ? exact : all);
}

/**
 * __lock_name - lock a name in a directory
 * @inode: inode for the directory in which to lock
 * @basename: name of the entry to lock
 *            if null, lock the entire directory
 *
 * the entire directory being locked is represented as: a single
 * pl_entry_lock_t present in the entrylk_locks list with its
 * basename = NULL
 */

int
__lock_name (pl_inode_t *pinode, const char *basename, entrylk_type type,
             call_frame_t *frame, pl_dom_list_t *dom, xlator_t *this, int nonblock)
{
        pl_entry_lock_t *lock       = NULL;
        pl_entry_lock_t *conf       = NULL;
        void            *trans      = NULL;
        pid_t            client_pid = 0;
        int              ret        = -EINVAL;

        trans = frame->root->trans;
        client_pid = frame->root->pid;

        lock = new_entrylk_lock (pinode, basename, type, trans, client_pid,
                                 &frame->root->lk_owner, dom->domain);
        if (!lock) {
                ret = -ENOMEM;
                goto out;
        }

        lock->frame   = frame;
        lock->this    = this;
        lock->trans   = trans;

        conf = __lock_grantable (dom, basename, type);
        if (conf) {
                ret = -EAGAIN;
                if (nonblock){
                        GF_FREE ((char *)lock->basename);
                        GF_FREE (lock);
                        goto out;

                }

                gettimeofday (&lock->blkd_time, NULL);
                list_add_tail (&lock->blocked_locks, &dom->blocked_entrylks);

                gf_log (this->name, GF_LOG_TRACE,
                        "Blocking lock: {pinode=%p, basename=%s}",
                        pinode, basename);

                goto out;
        }

        if ( __blocked_lock_conflict (dom, basename, type) && !(__owner_has_lock (dom, lock))) {
                ret = -EAGAIN;
                if (nonblock) {
                        GF_FREE ((char *) lock->basename);
                        GF_FREE (lock);
                        goto out;

                }
                lock->frame     = frame;
                lock->this      = this;

                gettimeofday (&lock->blkd_time, NULL);
                list_add_tail (&lock->blocked_locks, &dom->blocked_entrylks);

                gf_log (this->name, GF_LOG_TRACE,
                        "Lock is grantable, but blocking to prevent starvation");
                gf_log (this->name, GF_LOG_TRACE,
                        "Blocking lock: {pinode=%p, basename=%s}",
                        pinode, basename);

                ret = -EAGAIN;
                goto out;
        }
        switch (type) {

        case ENTRYLK_WRLCK:
                gettimeofday (&lock->granted_time, NULL);
                list_add_tail (&lock->domain_list, &dom->entrylk_list);
                break;

        default:

                gf_log (this->name, GF_LOG_DEBUG,
                        "Invalid type for entrylk specified: %d", type);
                ret = -EINVAL;
                goto out;
        }

        ret = 0;
out:
        return ret;
}

/**
 * __unlock_name - unlock a name in a directory
 * @inode: inode for the directory to unlock in
 * @basename: name of the entry to unlock
 *            if null, unlock the entire directory
 */

pl_entry_lock_t *
__unlock_name (pl_dom_list_t *dom, const char *basename, entrylk_type type)
{
        pl_entry_lock_t *lock = NULL;
        pl_entry_lock_t *ret_lock = NULL;

        lock = __find_most_matching_lock (dom, basename);

        if (!lock) {
                gf_log ("locks", GF_LOG_DEBUG,
                        "unlock on %s (type=ENTRYLK_WRLCK) attempted but no matching lock found",
                        basename);
                goto out;
        }

        if (names_equal (lock->basename, basename)
            && lock->type == type) {

                if (type == ENTRYLK_WRLCK) {
                        list_del_init (&lock->domain_list);
                        ret_lock = lock;
                }
        } else {
                gf_log ("locks", GF_LOG_DEBUG,
                        "Unlock for a non-existing lock!");
                goto out;
        }

out:
        return ret_lock;
}

uint32_t
check_entrylk_on_basename (xlator_t *this, inode_t *parent, char *basename)
{
        uint32_t        entrylk = 0;
        pl_inode_t      *pinode = 0;
        pl_dom_list_t   *dom = NULL;
        pl_entry_lock_t *conf       = NULL;

        pinode = pl_inode_get (this, parent);
        if (!pinode)
                goto out;
        pthread_mutex_lock (&pinode->mutex);
        {
                list_for_each_entry (dom, &pinode->dom_list, inode_list) {
                        conf = __lock_grantable (dom, basename, ENTRYLK_WRLCK);
                        if (conf && conf->basename) {
                                entrylk = 1;
                                break;
                        }
                }
        }
        pthread_mutex_unlock (&pinode->mutex);

out:
        return entrylk;
}

void
__grant_blocked_entry_locks (xlator_t *this, pl_inode_t *pl_inode,
                             pl_dom_list_t *dom, struct list_head *granted)
{
        int              bl_ret = 0;
        pl_entry_lock_t *bl   = NULL;
        pl_entry_lock_t *tmp  = NULL;

        struct list_head blocked_list;

        INIT_LIST_HEAD (&blocked_list);
        list_splice_init (&dom->blocked_entrylks, &blocked_list);

        list_for_each_entry_safe (bl, tmp, &blocked_list,
                                  blocked_locks) {

                list_del_init (&bl->blocked_locks);


                gf_log ("locks", GF_LOG_TRACE,
                        "Trying to unblock: {pinode=%p, basename=%s}",
                        pl_inode, bl->basename);

                bl_ret = __lock_name (pl_inode, bl->basename, bl->type,
                                      bl->frame, dom, bl->this, 0);

                if (bl_ret == 0) {
                        list_add (&bl->blocked_locks, granted);
                } else {
                        gf_log (this->name, GF_LOG_DEBUG,
                                "should never happen");
                        GF_FREE ((char *)bl->basename);
                        GF_FREE (bl);
                }
        }
        return;
}

/* Grants locks if possible which are blocked on a lock */
void
grant_blocked_entry_locks (xlator_t *this, pl_inode_t *pl_inode,
                           pl_entry_lock_t *unlocked, pl_dom_list_t *dom)
{
        struct list_head  granted_list;
        pl_entry_lock_t  *tmp = NULL;
        pl_entry_lock_t  *lock = NULL;

        INIT_LIST_HEAD (&granted_list);

        pthread_mutex_lock (&pl_inode->mutex);
        {
                __grant_blocked_entry_locks (this, pl_inode, dom, &granted_list);
        }
        pthread_mutex_unlock (&pl_inode->mutex);

        list_for_each_entry_safe (lock, tmp, &granted_list, blocked_locks) {
                list_del_init (&lock->blocked_locks);

                entrylk_trace_out (this, lock->frame, NULL, NULL, NULL,
                                   lock->basename, ENTRYLK_LOCK, lock->type,
                                   0, 0);

                STACK_UNWIND_STRICT (entrylk, lock->frame, 0, 0, NULL);

        }

        GF_FREE ((char *)unlocked->basename);
        GF_FREE (unlocked);

        return;
}

/**
 * release_entry_locks_for_transport: release all entry locks from this
 * transport for this loc_t
 */

static int
release_entry_locks_for_transport (xlator_t *this, pl_inode_t *pinode,
                                   pl_dom_list_t *dom, void *trans)
{
        pl_entry_lock_t  *lock = NULL;
        pl_entry_lock_t  *tmp = NULL;
        struct list_head  granted;
        struct list_head  released;

        INIT_LIST_HEAD (&granted);
        INIT_LIST_HEAD (&released);

        pthread_mutex_lock (&pinode->mutex);
        {
                list_for_each_entry_safe (lock, tmp, &dom->blocked_entrylks,
                                          blocked_locks) {
                        if (lock->trans != trans)
                                continue;

                        list_del_init (&lock->blocked_locks);

                        gf_log (this->name, GF_LOG_TRACE,
                                "releasing lock on  held by "
                                "{transport=%p}",trans);

                        list_add (&lock->blocked_locks, &released);

                }

                list_for_each_entry_safe (lock, tmp, &dom->entrylk_list,
                                          domain_list) {
                        if (lock->trans != trans)
                                continue;

                        list_del_init (&lock->domain_list);

                        gf_log (this->name, GF_LOG_TRACE,
                                "releasing lock on  held by "
                                "{transport=%p}",trans);

                        GF_FREE ((char *)lock->basename);
                        GF_FREE (lock);
                }

                __grant_blocked_entry_locks (this, pinode, dom, &granted);

        }

        pthread_mutex_unlock (&pinode->mutex);

        list_for_each_entry_safe (lock, tmp, &released, blocked_locks) {
                list_del_init (&lock->blocked_locks);

                STACK_UNWIND_STRICT (entrylk, lock->frame, -1, EAGAIN, NULL);

                GF_FREE ((char *)lock->basename);
                GF_FREE (lock);

        }

        list_for_each_entry_safe (lock, tmp, &granted, blocked_locks) {
                list_del_init (&lock->blocked_locks);

                STACK_UNWIND_STRICT (entrylk, lock->frame, 0, 0, NULL);

                GF_FREE ((char *)lock->basename);
                GF_FREE (lock);
        }

        return 0;
}

/* Common entrylk code called by pl_entrylk and pl_fentrylk */
int
pl_common_entrylk (call_frame_t *frame, xlator_t *this,
                   const char *volume, inode_t *inode, const char *basename,
                   entrylk_cmd cmd, entrylk_type type, loc_t *loc, fd_t *fd)
{
        int32_t  op_ret   = -1;
        int32_t  op_errno = 0;

        void *        transport = NULL;

        pl_inode_t *     pinode   = NULL;
        int              ret      = -1;
        pl_entry_lock_t *unlocked = NULL;
        char             unwind   = 1;

        pl_dom_list_t          *dom = NULL;

        pinode = pl_inode_get (this, inode);
        if (!pinode) {
                op_errno = ENOMEM;
                goto out;
        }

        dom = get_domain (pinode, volume);
        if (!dom){
                op_errno = ENOMEM;
                goto out;
        }

        entrylk_trace_in (this, frame, volume, fd, loc, basename, cmd, type);

        transport = frame->root->trans;

        if (frame->root->lk_owner.len == 0) {
                /*
                  this is a special case that means release
                  all locks from this transport
                */

                gf_log (this->name, GF_LOG_TRACE,
                        "Releasing locks for transport %p", transport);

                release_entry_locks_for_transport (this, pinode, dom, transport);
                op_ret = 0;

                goto out;
        }

        switch (cmd) {
        case ENTRYLK_LOCK:
                pthread_mutex_lock (&pinode->mutex);
                {
                        ret = __lock_name (pinode, basename, type,
                                           frame, dom, this, 0);
                }
                pthread_mutex_unlock (&pinode->mutex);

                op_errno = -ret;
                if (ret < 0) {
                        if (ret == -EAGAIN)
                                unwind = 0;
                        else
                                unwind = 1;
                        goto out;
                } else {
                        op_ret = 0;
                        op_errno = 0;
                        unwind = 1;
                        goto out;
                }

                break;

        case ENTRYLK_LOCK_NB:
                unwind = 1;
                pthread_mutex_lock (&pinode->mutex);
                {
                        ret = __lock_name (pinode, basename, type,
                                           frame, dom, this, 1);
                }
                pthread_mutex_unlock (&pinode->mutex);

                if (ret < 0) {
                        op_errno = -ret;
                        goto out;
                }

                break;

        case ENTRYLK_UNLOCK:
                pthread_mutex_lock (&pinode->mutex);
                {
                        unlocked = __unlock_name (dom, basename, type);
                }
                pthread_mutex_unlock (&pinode->mutex);

                if (unlocked)
                        grant_blocked_entry_locks (this, pinode, unlocked, dom);

                break;

        default:
                gf_log (this->name, GF_LOG_ERROR,
                        "Unexpected case in entrylk (cmd=%d). Please file"
                        "a bug report at http://bugs.gluster.com", cmd);
                goto out;
        }

        op_ret = 0;
out:
        pl_update_refkeeper (this, inode);
        if (unwind) {
                entrylk_trace_out (this, frame, volume, fd, loc, basename,
                                   cmd, type, op_ret, op_errno);

                STACK_UNWIND_STRICT (entrylk, frame, op_ret, op_errno, NULL);
        } else {
                entrylk_trace_block (this, frame, volume, fd, loc, basename,
                                     cmd, type);
        }


        return 0;
}

/**
 * pl_entrylk:
 *
 * Locking on names (directory entries)
 */

int
pl_entrylk (call_frame_t *frame, xlator_t *this,
            const char *volume, loc_t *loc, const char *basename,
            entrylk_cmd cmd, entrylk_type type)
{

        pl_common_entrylk (frame, this, volume, loc->inode, basename, cmd, type, loc, NULL);

        return 0;
}


/**
 * pl_fentrylk:
 *
 * Locking on names (directory entries)
 */

int
pl_fentrylk (call_frame_t *frame, xlator_t *this,
             const char *volume, fd_t *fd, const char *basename,
             entrylk_cmd cmd, entrylk_type type)
{

        pl_common_entrylk (frame, this, volume, fd->inode, basename, cmd, type, NULL, fd);

        return 0;
}


int32_t
__get_entrylk_count (xlator_t *this, pl_inode_t *pl_inode)
{
        int32_t            count = 0;
        pl_entry_lock_t   *lock  = NULL;
        pl_dom_list_t     *dom   = NULL;

        list_for_each_entry (dom, &pl_inode->dom_list, inode_list) {
                list_for_each_entry (lock, &dom->entrylk_list, domain_list) {
                        count++;
                }

                list_for_each_entry (lock, &dom->blocked_entrylks, blocked_locks) {
                        count++;
                }

        }

        return count;
}

int32_t
get_entrylk_count (xlator_t *this, inode_t *inode)
{
        pl_inode_t   *pl_inode = NULL;
        uint64_t      tmp_pl_inode = 0;
        int           ret      = 0;
        int32_t       count    = 0;

        ret = inode_ctx_get (inode, this, &tmp_pl_inode);
        if (ret != 0) {
                goto out;
        }

        pl_inode = (pl_inode_t *)(long) tmp_pl_inode;

        pthread_mutex_lock (&pl_inode->mutex);
        {
                count = __get_entrylk_count (this, pl_inode);
        }
        pthread_mutex_unlock (&pl_inode->mutex);

out:
        return count;
}
