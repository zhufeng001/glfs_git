/*
  Copyright (c) 2008-2012 Red Hat, Inc. <http://www.redhat.com>
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

#include "inode.h"
#include "fd.h"
#include "common-utils.h"
#include "statedump.h"
#include <pthread.h>
#include <sys/types.h>
#include <stdint.h>
#include "list.h"
#include <time.h>
#include <assert.h>

/* TODO:
   move latest accessed dentry to list_head of inode
*/

#define INODE_DUMP_LIST(head, key_buf, key_prefix, list_type)           \
        {                                                               \
                int i = 1;                                              \
                inode_t *inode = NULL;                                  \
                list_for_each_entry (inode, head, list) {               \
                        gf_proc_dump_build_key(key_buf, key_prefix,     \
                                               "%s.%d",list_type, i++); \
                        gf_proc_dump_add_section(key_buf);              \
                        inode_dump(inode, key);                         \
                }                                                       \
        }

static inode_t *
__inode_unref (inode_t *inode);

static int
inode_table_prune (inode_table_t *table);

void
fd_dump (struct list_head *head, char *prefix);

static int
hash_dentry (inode_t *parent, const char *name, int mod)
{
	// mod is hashsize
	// get dentry hash by name ??
        int hash = 0;
        int ret = 0;

        hash = *name;
        if (hash) {
                for (name += 1; *name != '\0'; name++) {
                        hash = (hash << 5) - hash + *name;
                }
        }
        ret = (hash + (unsigned long)parent) % mod;

        return ret;
}


static int
hash_gfid (uuid_t uuid, int mod)
{
        int ret = 0;

        ret = uuid[15] + (uuid[14] << 8);

        return ret;
}


static void
__dentry_hash (dentry_t *dentry)
{
	// cal hash of dentry by name and parent; and delete from prev hash list and insert to table->name_hash;
        inode_table_t   *table = NULL;
        int              hash = 0;

        if (!dentry) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "dentry not found");
                return;
        }

        table = dentry->inode->table;
        hash = hash_dentry (dentry->parent, dentry->name,
                            table->hashsize);

        list_del_init (&dentry->hash);
        list_add (&dentry->hash, &table->name_hash[hash]);
}


static int
__is_dentry_hashed (dentry_t *dentry)
{
	// check dentry->hash
        if (!dentry) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "dentry not found");
                return 0;
        }

        return !list_empty (&dentry->hash);
}


static void
__dentry_unhash (dentry_t *dentry)
{
	// delete from dentry->hash list;
        if (!dentry) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "dentry not found");
                return;
        }

        list_del_init (&dentry->hash);
}


static void
__dentry_unset (dentry_t *dentry)
{
	// free dentry;
	// from dentry and delete from list;
        if (!dentry) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "dentry not found");
                return;
        }

        __dentry_unhash (dentry);
        // delete from inode_list;

        list_del_init (&dentry->inode_list);

        GF_FREE (dentry->name);

        if (dentry->parent) {
                __inode_unref (dentry->parent);
                dentry->parent = NULL;
        }

        mem_put (dentry);
}


static int
__foreach_ancestor_dentry (dentry_t *dentry,
                           int (per_dentry_fn) (dentry_t *dentry,
                                                void *data),
                           void *data)
{
	// per_dentry_fn(parent->dentry ,inode)
		//对祖先来一遍过滤.
        inode_t  *parent = NULL;
        dentry_t *each = NULL;
        int       ret = 0;

        if (!dentry) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "dentry not found");
                return 0;
        }

        ret = per_dentry_fn (dentry, data);
        if (ret) {
                gf_log (THIS->name, GF_LOG_WARNING, "per dentry fn returned %d", ret);
                goto out;
        }

        parent = dentry->parent;
        if (!parent) {
                gf_log (THIS->name, GF_LOG_WARNING, "parent not found");
                goto out;
        }

        list_for_each_entry (each, &parent->dentry_list, inode_list) {
                ret = __foreach_ancestor_dentry (each, per_dentry_fn, data);
                if (ret)
                        goto out;
        }
out:
        return ret;
}


static int
__check_cycle (dentry_t *a_dentry, void *data)
{
	// check if dentry's parent is link_inode (data)
        inode_t *link_inode = NULL;

        link_inode = data;

        if (a_dentry->parent == link_inode)
                return 1;

        return 0;
}


static int
__is_dentry_cyclic (dentry_t *dentry)
{
        int       ret = 0;
        inode_t  *inode = NULL;
        char     *name = "<nul>";

        ret = __foreach_ancestor_dentry (dentry, __check_cycle,
                                         dentry->inode);
        if (ret) {
        	// exists dentry->parent equal link_node;
                inode = dentry->inode;

                if (dentry->name)
                        name = dentry->name;

                gf_log (dentry->inode->table->name, GF_LOG_CRITICAL,
                        "detected cyclic loop formation during inode linkage."
                        " inode (%s) linking under itself as %s",
                        uuid_utoa (inode->gfid), name);
        }

        return ret;
}


static void
__inode_unhash (inode_t *inode)
{
	// del node from hash list;
        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return;
        }

        list_del_init (&inode->hash);
}


static int
// check inode->hash list;
__is_inode_hashed (inode_t *inode)
{
        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return 0;
        }

        return !list_empty (&inode->hash);
}


static void
__inode_hash (inode_t *inode)
{
        inode_table_t *table = NULL;
        int            hash = 0;

        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return;
        }
        // cal hash by gfid ;
        // insert inode to inode'table->inode_hash
        // inode->table
        table = inode->table;
        hash = hash_gfid (inode->gfid, 65536);

        list_del_init (&inode->hash);
        list_add (&inode->hash, &table->inode_hash[hash]);
}


static dentry_t *
__dentry_search_for_inode (inode_t *inode, uuid_t pargfid, const char *name)
{
		// inode and name can't be null

        dentry_t *dentry = NULL;
        dentry_t *tmp = NULL;

        if (!inode || !name) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode || name not found");
                return NULL;
        }

        /* earlier, just the ino was sent, which could have been 0, now
           we deal with gfid, and if sent gfid is null or 0, no need to
           continue with the check */
        if (!pargfid || uuid_is_null (pargfid))
                return NULL;

        // get dentry by pargfid and name;

        list_for_each_entry (tmp, &inode->dentry_list, inode_list) {
                if ((uuid_compare (tmp->parent->gfid, pargfid) == 0) &&
                    !strcmp (tmp->name, name)) {
                        dentry = tmp;
                        break;
                }
        }

        return dentry;
}


static void
__inode_destroy (inode_t *inode)
{
        int          index = 0;
        xlator_t    *xl = NULL;
        xlator_t    *old_THIS = NULL;

        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return;
        }

        if (!inode->_ctx) {
                gf_log (THIS->name, GF_LOG_WARNING, "_ctx not found");
                goto noctx;
        }

        for (index = 0; index < inode->table->ctxcount; index++) {
                if (inode->_ctx[index].xl_key) {
                        xl = (xlator_t *)(long)inode->_ctx[index].xl_key;
                        old_THIS = THIS;
                        THIS = xl;
                        if (xl->cbks->forget)
                                xl->cbks->forget (xl, inode);
                        THIS = old_THIS;
                }
        }

        GF_FREE (inode->_ctx);
noctx:
        LOCK_DESTROY (&inode->lock);
        //  memset (inode, 0xb, sizeof (*inode));
        mem_put (inode);
}


static void
__inode_activate (inode_t *inode)
{
        if (!inode)
                return;

        list_move (&inode->list, &inode->table->active);
        inode->table->active_size++;
}


static void
__inode_passivate (inode_t *inode)
{
        dentry_t      *dentry = NULL;
        dentry_t      *t = NULL;

        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return;
        }

        list_move_tail (&inode->list, &inode->table->lru);
        inode->table->lru_size++;

        list_for_each_entry_safe (dentry, t, &inode->dentry_list, inode_list) {
                if (!__is_dentry_hashed (dentry))
                        __dentry_unset (dentry);
        }
}


static void
__inode_retire (inode_t *inode)
{
	// table->purge and table->purge_size
	// put inode to purge list;

        dentry_t      *dentry = NULL;
        dentry_t      *t = NULL;

        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return;
        }

        list_move_tail (&inode->list, &inode->table->purge);
        inode->table->purge_size++;

        __inode_unhash (inode);
        // get dentry from inode->dentry_list ;and free dentry;
        list_for_each_entry_safe (dentry, t, &inode->dentry_list, inode_list) {
                __dentry_unset (dentry);
        }
}


static inode_t *
__inode_unref (inode_t *inode)
{
        if (!inode)
                return NULL;

        if (__is_root_gfid(inode->gfid))
                return inode;

        GF_ASSERT (inode->ref);

        --inode->ref;

        if (!inode->ref) {
                inode->table->active_size--;

                if (inode->nlookup)
                        __inode_passivate (inode);
                else
                        __inode_retire (inode);
        }

        return inode;
}


static inode_t *
__inode_ref (inode_t *inode)
{
        if (!inode)
                return NULL;

        if (!inode->ref) {
                inode->table->lru_size--;
                __inode_activate (inode);
        }
        inode->ref++;

        return inode;
}


inode_t *
inode_unref (inode_t *inode)
{
        inode_table_t *table = NULL;

        if (!inode)
                return NULL;

        table = inode->table;

        pthread_mutex_lock (&table->lock);
        {
                inode = __inode_unref (inode);
        }
        pthread_mutex_unlock (&table->lock);

        inode_table_prune (table);

        return inode;
}


inode_t *
inode_ref (inode_t *inode)
{
        inode_table_t *table = NULL;

        if (!inode)
                return NULL;

        table = inode->table;

        pthread_mutex_lock (&table->lock);
        {
                inode = __inode_ref (inode);
        }
        pthread_mutex_unlock (&table->lock);

        return inode;
}


static dentry_t *
__dentry_create (inode_t *inode, inode_t *parent, const char *name)
{
	// malloc new dentry ;and init member inode,parent ,name;
	// add to inode->dentry_list;
        dentry_t      *newd = NULL;

        if (!inode || !parent || !name) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING,
                                  "inode || parent || name not found");
                return NULL;
        }

        newd = mem_get0 (parent->table->dentry_pool);
        if (newd == NULL) {
                goto out;
        }

        INIT_LIST_HEAD (&newd->inode_list);
        INIT_LIST_HEAD (&newd->hash);

        newd->name = gf_strdup (name);
        if (newd->name == NULL) {
                mem_put (newd);
                newd = NULL;
                goto out;
        }

        if (parent)
                newd->parent = __inode_ref (parent);

        list_add (&newd->inode_list, &inode->dentry_list);
        newd->inode = inode;

out:
        return newd;
}


static inode_t *
__inode_create (inode_table_t *table)
{
        inode_t  *newi = NULL;

        if (!table) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "table not found");
                return NULL;
        }
        // malloc newi
        // melloc newi->_ctx and insert newi to table->lru;
        // fd_list ? dentry_list ?
        newi = mem_get0 (table->inode_pool);
        if (!newi) {
                goto out;
        }

        newi->table = table;

        LOCK_INIT (&newi->lock);

        INIT_LIST_HEAD (&newi->fd_list);
        INIT_LIST_HEAD (&newi->list);
        INIT_LIST_HEAD (&newi->hash);
        INIT_LIST_HEAD (&newi->dentry_list);

        newi->_ctx = GF_CALLOC (1, (sizeof (struct _inode_ctx) * table->ctxcount),
                                gf_common_mt_inode_ctx);

        if (newi->_ctx == NULL) {
                LOCK_DESTROY (&newi->lock);
                mem_put (newi);
                newi = NULL;
                goto out;
        }

        list_add (&newi->list, &table->lru);
        table->lru_size++;

out:

        return newi;
}


inode_t *
inode_new (inode_table_t *table)
{
	// create new inode ; malloc and init
        inode_t *inode = NULL;

        if (!table) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return NULL;
        }

        pthread_mutex_lock (&table->lock);
        {
                inode = __inode_create (table);
                if (inode != NULL) {
                        __inode_ref (inode);
                }
        }
        pthread_mutex_unlock (&table->lock);

        return inode;
}


static inode_t *
__inode_lookup (inode_t *inode)
{
        if (!inode)
                return NULL;

        inode->nlookup++;

        return inode;
}


static inode_t *
__inode_forget (inode_t *inode, uint64_t nlookup)
{
	// nlookup ??
        if (!inode)
                return NULL;

        GF_ASSERT (inode->nlookup >= nlookup);

        inode->nlookup -= nlookup;

        if (!nlookup)
                inode->nlookup = 0;

        return inode;
}


dentry_t *
__dentry_grep (inode_table_t *table, inode_t *parent, const char *name)
{
	// find dentry by name'hash and parent inode;
        int       hash = 0;
        dentry_t *dentry = NULL;
        dentry_t *tmp = NULL;

        if (!table || !name || !parent)
                return NULL;

        hash = hash_dentry (parent, name, table->hashsize);

        // name_hash ?
        list_for_each_entry (tmp, &table->name_hash[hash], hash) {
                if (tmp->parent == parent && !strcmp (tmp->name, name)) {
                        dentry = tmp;
                        break;
                }
        }

        return dentry;
}


inode_t *
inode_grep (inode_table_t *table, inode_t *parent, const char *name)
{
        inode_t   *inode = NULL;
        dentry_t  *dentry = NULL;

        if (!table || !parent || !name) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING,
                                  "table || parent || name not found");
                return NULL;
        }

        pthread_mutex_lock (&table->lock);
        {
                dentry = __dentry_grep (table, parent, name);

                if (dentry)
                        inode = dentry->inode;

                if (inode)
                        __inode_ref (inode);
        }
        pthread_mutex_unlock (&table->lock);

        return inode;
}


inode_t *
inode_resolve (inode_table_t *table, char *path)
{
        char    *tmp   = NULL, *bname = NULL, *str = NULL, *saveptr = NULL;
        inode_t *inode = NULL, *parent = NULL;

        if ((path == NULL) || (table == NULL)) {
                goto out;
        }

        parent = inode_ref (table->root);
        str = tmp = gf_strdup (path);

        while (1) {
                bname = strtok_r (str, "/", &saveptr);
                if (bname == NULL) {
                        break;
                }

                if (inode != NULL) {
                        inode_unref (inode);
                }

                inode = inode_grep (table, parent, bname);
                if (inode == NULL) {
                        break;
                }

                if (parent != NULL) {
                        inode_unref (parent);
                }

                parent = inode_ref (inode);
                str = NULL;
        }

        inode_unref (parent);
        GF_FREE (tmp);
out:
        return inode;
}


int
inode_grep_for_gfid (inode_table_t *table, inode_t *parent, const char *name,
                     uuid_t gfid, ia_type_t *type)
{
        inode_t   *inode = NULL;
        dentry_t  *dentry = NULL;
        int        ret = -1;

        if (!table || !parent || !name) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING,
                                  "table || parent || name not found");
                return ret;
        }

        pthread_mutex_lock (&table->lock);
        {
                dentry = __dentry_grep (table, parent, name);

                if (dentry)
                        inode = dentry->inode;

                if (inode) {
                        uuid_copy (gfid, inode->gfid);
                        *type = inode->ia_type;
                        ret = 0;
                }
        }
        pthread_mutex_unlock (&table->lock);

        return ret;
}


/* return 1 if gfid is of root, 0 if not */
gf_boolean_t
__is_root_gfid (uuid_t gfid)
{
	// check gfid is root ?
        uuid_t  root;

        memset (root, 0, 16);
        root[15] = 1;

        if (uuid_compare (gfid, root) == 0)
                return _gf_true;

        return _gf_false;
}


inode_t *
__inode_find (inode_table_t *table, uuid_t gfid)
{
	//get inode from table->inode_hash by cmd gfid
        inode_t   *inode = NULL;
        inode_t   *tmp = NULL;
        int        hash = 0;

        if (!table) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "table not found");
                goto out;
        }

        if (__is_root_gfid (gfid))
                return table->root;

        // from gfid get hash
        hash = hash_gfid (gfid, 65536);

        list_for_each_entry (tmp, &table->inode_hash[hash], hash) {
                if (uuid_compare (tmp->gfid, gfid) == 0) {
                        inode = tmp;
                        break;
                }
        }

out:
        return inode;
}


inode_t *
inode_find (inode_table_t *table, uuid_t gfid)
{
	// find inode from table by gfid

        inode_t   *inode = NULL;
        // check table
        if (!table) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "table not found");
                return NULL;
        }

        pthread_mutex_lock (&table->lock);
        {
                inode = __inode_find (table, gfid);
                if (inode)
                        __inode_ref (inode);
        }
        pthread_mutex_unlock (&table->lock);

        return inode;
}


static inode_t *
__inode_link (inode_t *inode, inode_t *parent, const char *name,
              struct iatt *iatt)
{
	// get link_node ;(which is inode or old_inode)
        dentry_t      *dentry = NULL;
        dentry_t      *old_dentry = NULL;
        inode_t       *old_inode = NULL;
        inode_table_t *table = NULL;
        inode_t       *link_inode = NULL;

        if (!inode)
                return NULL;

        table = inode->table;
        if (!table)
                return NULL;

        if (parent) {
                /* We should prevent inode linking between different
                   inode tables. This can cause errors which is very
                   hard to catch/debug. */
                if (inode->table != parent->table) {
                        GF_ASSERT (!"link attempted b/w inodes of diff table");
                }
        }

        link_inode = inode;
        // hash list is empty
        if (!__is_inode_hashed (inode)) {
                if (!iatt)
                        return NULL;

                if (uuid_is_null (iatt->ia_gfid))
                        return NULL;
                //
                old_inode = __inode_find (table, iatt->ia_gfid);

                if (old_inode) {
                	// find old_inode and assign to link_inode by iatt->ia_gfid
                        link_inode = old_inode;
                } else {
                	// else hash inode;
                        uuid_copy (inode->gfid, iatt->ia_gfid);
                        inode->ia_type    = iatt->ia_type;
                        __inode_hash (inode);
                }
        }
        // check name and . ' ..
        if (name) {
                if (!strcmp(name, ".") || !strcmp(name, ".."))
                        return link_inode;
        }

        /* use only link_inode beyond this point */
        if (parent) {
                old_dentry = __dentry_grep (table, parent, name);

                if (!old_dentry || old_dentry->inode != link_inode) {
                        dentry = __dentry_create (link_inode, parent, name);
                        if (!dentry) {
                                gf_log_callingfn (THIS->name, GF_LOG_ERROR,
                                                  "dentry create failed on "
                                                  "inode %s with parent %s",
                                                  uuid_utoa (link_inode->gfid),
                                                  uuid_utoa (parent->gfid));
                                return NULL;
                        }
                        if (old_inode && __is_dentry_cyclic (dentry)) {
                                __dentry_unset (dentry);
                                return NULL;
                        }
                        __dentry_hash (dentry);

                        if (old_dentry)
                                __dentry_unset (old_dentry);
                }
        }

        return link_inode;
}


inode_t *
inode_link (inode_t *inode, inode_t *parent, const char *name,
            struct iatt *iatt)
{
	// get linknode from inode and parent and name;
        inode_table_t *table = NULL;
        inode_t       *linked_inode = NULL;

        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return NULL;
        }

        table = inode->table;

        pthread_mutex_lock (&table->lock);
        {
                linked_inode = __inode_link (inode, parent, name, iatt);

                if (linked_inode)
                        __inode_ref (linked_inode);
        }
        pthread_mutex_unlock (&table->lock);

        inode_table_prune (table);

        return linked_inode;
}


int
inode_lookup (inode_t *inode)
{
	// inode->nlookup ++
        inode_table_t *table = NULL;

        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return -1;
        }

        table = inode->table;

        pthread_mutex_lock (&table->lock);
        {
                __inode_lookup (inode);
        }
        pthread_mutex_unlock (&table->lock);

        return 0;
}


int
inode_forget (inode_t *inode, uint64_t nlookup)
{
        inode_table_t *table = NULL;

        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return -1;
        }

        table = inode->table;

        pthread_mutex_lock (&table->lock);
        {
                __inode_forget (inode, nlookup);
        }
        pthread_mutex_unlock (&table->lock);

        inode_table_prune (table);

        return 0;
}

/*
 * Invalidate an inode. This is invoked when a translator decides that an inode's
 * cache is no longer valid. Any translator interested in taking action in this
 * situation can define the invalidate callback.
 */
int
inode_invalidate(inode_t *inode)
{
	int ret = 0;
	xlator_t *xl = NULL;
	xlator_t *old_THIS = NULL;

	if (!inode) {
		gf_log_callingfn(THIS->name, GF_LOG_WARNING, "inode not found");
		return -1;
	}

	/*
	 * The master xlator is not in the graph but it can define an invalidate
	 * handler.
	 */
	xl = inode->table->xl->ctx->master;
	if (xl && xl->cbks->invalidate) {
		old_THIS = THIS;
		THIS = xl;
		ret = xl->cbks->invalidate(xl, inode);
		THIS = old_THIS;
		if (ret)
			return ret;
	}

	xl = inode->table->xl->graph->first;
	while (xl) {
		old_THIS = THIS;
		THIS = xl;
		if (xl->cbks->invalidate)
			ret = xl->cbks->invalidate(xl, inode);
		THIS = old_THIS;

		if (ret)
			break;

		xl = xl->next;
	}

	return ret;
}


static void
__inode_unlink (inode_t *inode, inode_t *parent, const char *name)
{
        dentry_t *dentry = NULL;

        if (!inode || !parent || !name)
                return;

        dentry = __dentry_search_for_inode (inode, parent->gfid, name);

        /* dentry NULL for corrupted backend */
        if (dentry)
                __dentry_unset (dentry);
}


void
inode_unlink (inode_t *inode, inode_t *parent, const char *name)
{
        inode_table_t *table = NULL;

        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return;
        }

        table = inode->table;

        pthread_mutex_lock (&table->lock);
        {
                __inode_unlink (inode, parent, name);
        }
        pthread_mutex_unlock (&table->lock);

        inode_table_prune (table);
}


int
inode_rename (inode_table_t *table, inode_t *srcdir, const char *srcname,
              inode_t *dstdir, const char *dstname, inode_t *inode,
              struct iatt *iatt)
{
        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return -1;
        }

        table = inode->table;

        pthread_mutex_lock (&table->lock);
        {
                __inode_link (inode, dstdir, dstname, iatt);
                __inode_unlink (inode, srcdir, srcname);
        }
        pthread_mutex_unlock (&table->lock);

        inode_table_prune (table);

        return 0;
}


static dentry_t *
__dentry_search_arbit (inode_t *inode)
{
	// inode-> dentry_list ??
	// from inode->dentry_list get trav;
        dentry_t *dentry = NULL;
        dentry_t *trav = NULL;

        if (!inode)
                return NULL;

        list_for_each_entry (trav, &inode->dentry_list, inode_list) {
        	// check trav->hash
                if (__is_dentry_hashed (trav)) {
                        dentry = trav;
                        break;
                }
        }

        if (!dentry) {
                list_for_each_entry (trav, &inode->dentry_list, inode_list) {
                        dentry = trav;
                        break;
                }
        }

        return dentry;
}


inode_t *
inode_parent (inode_t *inode, uuid_t pargfid, const char *name)
{
	// found parent inode by pargfid and name;
	// get dentry->parent;
        inode_t       *parent = NULL;
        inode_table_t *table = NULL;
        dentry_t      *dentry = NULL;

        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return NULL;
        }

        table = inode->table;

        pthread_mutex_lock (&table->lock);
        {
                if (pargfid && !uuid_is_null (pargfid) && name) {
                        dentry = __dentry_search_for_inode (inode, pargfid, name);
                } else {
                        dentry = __dentry_search_arbit (inode);
                }

                if (dentry)
                        parent = dentry->parent;

                if (parent)
                        __inode_ref (parent);
        }
        pthread_mutex_unlock (&table->lock);

        return parent;
}


int
__inode_path (inode_t *inode, const char *name, char **bufp)
{
	// put name to bufp; inode is the last child ?

        inode_table_t *table = NULL;
        inode_t       *itrav = NULL;
        dentry_t      *trav  = NULL;
        size_t         i     = 0, size = 0;
        int64_t        ret   = 0;
        int            len   = 0;
        char          *buf   = NULL;
        // check inode and gfid
        if (!inode || uuid_is_null (inode->gfid)) {
                GF_ASSERT (0);
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "invalid inode");
                return -1;
        }

        table = inode->table;

        // get all parent ?? get path; every trav is level
        // store in trav->name
        // get path length
        itrav = inode;
        for (trav = __dentry_search_arbit (itrav); trav;
             trav = __dentry_search_arbit (itrav)) {
                itrav = trav->parent;
                i ++; /* "/" */
                i += strlen (trav->name);
                if (i > PATH_MAX) {
                        gf_log (table->name, GF_LOG_CRITICAL,
                                "possible infinite loop detected, "
                                "forcing break. name=(%s)", name);
                        ret = -ENOENT;
                        goto out;
                }
        }

        if (!__is_root_gfid (itrav->gfid)) {
                /* "<gfid:00000000-0000-0000-0000-000000000000>"/path */
                i += GFID_STR_PFX_LEN;
        }

        if (name) {
                i++;
                i += strlen (name);
        }

        ret = i;
        size = i + 1;
        buf = GF_CALLOC (size, sizeof (char), gf_common_mt_char);
        if (buf) {

                buf[size - 1] = 0;

                if (name) {
                        len = strlen (name);
                        strncpy (buf + (i - len), name, len);
                        buf[i-len-1] = '/';
                        i -= (len + 1);
                }
                // cp name and trav->name to buf;
                itrav = inode;
                for (trav = __dentry_search_arbit (itrav); trav;
                     trav = __dentry_search_arbit (itrav)) {
                        itrav = trav->parent;
                        len = strlen (trav->name);
                        strncpy (buf + (i - len), trav->name, len);
                        buf[i-len-1] = '/';
                        i -= (len + 1);
                }

                if (!__is_root_gfid (itrav->gfid)) {
                        snprintf (&buf[i-GFID_STR_PFX_LEN], GFID_STR_PFX_LEN,
                                  INODE_PATH_FMT, uuid_utoa (itrav->gfid));
                        buf[i-1] = '>';
                }

                *bufp = buf;
        } else {
                ret = -ENOMEM;
        }

out:
        if (__is_root_gfid (inode->gfid) && !name) {
                ret = 1;
                GF_FREE (buf);
                buf = GF_CALLOC (ret + 1, sizeof (char), gf_common_mt_char);
                if (buf) {
                        strcpy (buf, "/");
                        *bufp = buf;
                } else {
                        ret = -ENOMEM;
                }
        }

        if (ret < 0)
                *bufp = NULL;
        return ret;
}


int
inode_path (inode_t *inode, const char *name, char **bufp)
{
	// convert inode and name to bufp as path
        inode_table_t *table = NULL;
        int            ret   = -1;

        if (!inode)
                return -1;

        table = inode->table;

        pthread_mutex_lock (&table->lock);
        {
                ret = __inode_path (inode, name, bufp);
        }
        pthread_mutex_unlock (&table->lock);

        return ret;
}


static int
inode_table_prune (inode_table_t *table)
{
        int               ret = 0;
        struct list_head  purge = {0, };
        inode_t          *del = NULL;
        inode_t          *tmp = NULL;
        inode_t          *entry = NULL;

        if (!table)
                return -1;

        INIT_LIST_HEAD (&purge);

        pthread_mutex_lock (&table->lock);
        {
                while (table->lru_limit
                       && table->lru_size > (table->lru_limit)) {
                	// del entry inode until lru_size < limit ??
                		// get enry of inode_t
                        entry = list_entry (table->lru.next, inode_t, list);

                        table->lru_size--;
                        __inode_retire (entry);

                        ret++;
                }

                list_splice_init (&table->purge, &purge);
                table->purge_size = 0;
        }
        pthread_mutex_unlock (&table->lock);

        {
                list_for_each_entry_safe (del, tmp, &purge, list) {
                	// delete del from purge list;
                	// free del;
                        list_del_init (&del->list);
                        __inode_forget (del, 0);
                        __inode_destroy (del);
                }
        }

        return ret;
}


static void
__inode_table_init_root (inode_table_t *table)
{
        inode_t     *root = NULL;
        struct iatt  iatt = {0, };

        if (!table)
                return;

        root = __inode_create (table);

        iatt.ia_gfid[15] = 1;
        iatt.ia_ino = 1;
        iatt.ia_type = IA_IFDIR;

        __inode_link (root, NULL, NULL, &iatt);
        table->root = root;
}


inode_table_t *
inode_table_new (size_t lru_limit, xlator_t *xl)
{
        inode_table_t *new = NULL;
        int            ret = -1;
        int            i = 0;

        new = (void *)GF_CALLOC(1, sizeof (*new), gf_common_mt_inode_table_t);
        if (!new)
                return NULL;

        new->xl = xl;
        new->ctxcount = xl->graph->xl_count + 1;

        new->lru_limit = lru_limit;

        new->hashsize = 14057; /* TODO: Random Number?? */

        /* In case FUSE is initing the inode table. */
        if (lru_limit == 0)
                lru_limit = DEFAULT_INODE_MEMPOOL_ENTRIES;

        new->inode_pool = mem_pool_new (inode_t, lru_limit);

        if (!new->inode_pool)
                goto out;

        new->dentry_pool = mem_pool_new (dentry_t, lru_limit);

        if (!new->dentry_pool)
                goto out;

        new->inode_hash = (void *)GF_CALLOC (65536,
                                             sizeof (struct list_head),
                                             gf_common_mt_list_head);
        if (!new->inode_hash)
                goto out;

        new->name_hash = (void *)GF_CALLOC (new->hashsize,
                                            sizeof (struct list_head),
                                            gf_common_mt_list_head);
        if (!new->name_hash)
                goto out;

        /* if number of fd open in one process is more than this,
           we may hit perf issues */
        new->fd_mem_pool = mem_pool_new (fd_t, 1024);

        if (!new->fd_mem_pool)
                goto out;

        for (i = 0; i < 65536; i++) {
                INIT_LIST_HEAD (&new->inode_hash[i]);
        }


        for (i = 0; i < new->hashsize; i++) {
                INIT_LIST_HEAD (&new->name_hash[i]);
        }

        INIT_LIST_HEAD (&new->active);
        INIT_LIST_HEAD (&new->lru);
        INIT_LIST_HEAD (&new->purge);

        ret = gf_asprintf (&new->name, "%s/inode", xl->name);
        if (-1 == ret) {
                /* TODO: This should be ok to continue, check with avati */
                ;
        }

        __inode_table_init_root (new);

        pthread_mutex_init (&new->lock, NULL);

        ret = 0;
out:
        if (ret) {
                if (new) {
                        GF_FREE (new->inode_hash);
                        GF_FREE (new->name_hash);
                        if (new->dentry_pool)
                                mem_pool_destroy (new->dentry_pool);
                        if (new->inode_pool)
                                mem_pool_destroy (new->inode_pool);
                        GF_FREE (new);
                        new = NULL;
                }
        }

        return new;
}


inode_t *
inode_from_path (inode_table_t *itable, const char *path)
{
        inode_t  *inode = NULL;
        inode_t  *parent = NULL;
        inode_t  *root = NULL;
        inode_t  *curr = NULL;
        char     *pathname = NULL;
        char     *component = NULL, *next_component = NULL;
        char     *strtokptr = NULL;

        if (!itable || !path)
                return NULL;

        /* top-down approach */
        pathname = gf_strdup (path);
        if (pathname == NULL) {
                goto out;
        }

        root = itable->root;
        parent = inode_ref (root);
        component = strtok_r (pathname, "/", &strtokptr);

        if (component == NULL)
                /* root inode */
                inode = inode_ref (parent);

        while (component) {
                curr = inode_grep (itable, parent, component);

                if (curr == NULL) {
                        strtok_r (NULL, "/", &strtokptr);
                        break;
                }

                next_component = strtok_r (NULL, "/", &strtokptr);

                if (next_component) {
                        inode_unref (parent);
                        parent = curr;
                        curr = NULL;
                } else {
                        inode = curr;
                }

                component = next_component;
        }

        if (parent)
                inode_unref (parent);

        GF_FREE (pathname);

out:
        return inode;
}


int
__inode_ctx_set2 (inode_t *inode, xlator_t *xlator, uint64_t *value1_p,
                  uint64_t *value2_p)
{
	// xlator as key,v1 and v2 as val ,set to inode->_ctx
	// inode->table->ctxcount ??

        int ret = 0;
        int index = 0;
        int set_idx = -1;

        if (!inode || !xlator)
                return -1;

        for (index = 0; index < inode->table->ctxcount; index++) {
                if (!inode->_ctx[index].xl_key) {
                        if (set_idx == -1)
                                set_idx = index;
                        /* dont break, to check if key already exists
                           further on */
                }
                if (inode->_ctx[index].xl_key == xlator) {
                        set_idx = index;
                        break;
                }
        }

        if (set_idx == -1) {
                ret = -1;
                goto out;;
        }

        inode->_ctx[set_idx].xl_key = xlator;
        if (value1_p)
                inode->_ctx[set_idx].value1 = *value1_p;
        if (value2_p)
                inode->_ctx[set_idx].value2 = *value2_p;
out:
        return ret;
}


int
inode_ctx_set2 (inode_t *inode, xlator_t *xlator, uint64_t *value1_p,
                uint64_t *value2_p)
{
        int ret = 0;

        if (!inode || !xlator)
                return -1;

        LOCK (&inode->lock);
        {
                ret = __inode_ctx_set2 (inode, xlator, value1_p, value2_p);
        }
        UNLOCK (&inode->lock);

        return ret;
}


int
__inode_ctx_get2 (inode_t *inode, xlator_t *xlator, uint64_t *value1,
                  uint64_t *value2)
{
	// get value1,value2 from inode->_ctx by cmp _ctx[index].xl_key and xlator;
        int index = 0;
        int ret = 0;

        if (!inode || !xlator)
                return -1;

        for (index = 0; index < inode->table->ctxcount; index++) {
                if (inode->_ctx[index].xl_key == xlator)
                        break;
        }

        if (index == inode->table->ctxcount) {
                ret = -1;
                goto out;
        }

        if (value1)
                *value1 = inode->_ctx[index].value1;

        if (value2)
                *value2 = inode->_ctx[index].value2;

out:
        return ret;
}


int
inode_ctx_get2 (inode_t *inode, xlator_t *xlator, uint64_t *value1,
                uint64_t *value2)
{
        int ret = 0;

        if (!inode || !xlator)
                return -1;

        LOCK (&inode->lock);
        {
                ret = __inode_ctx_get2 (inode, xlator, value1, value2);
        }
        UNLOCK (&inode->lock);

        return ret;
}


int
inode_ctx_del2 (inode_t *inode, xlator_t *xlator, uint64_t *value1,
                uint64_t *value2)
{
        int index = 0;
        int ret = 0;

        if (!inode || !xlator)
                return -1;

        LOCK (&inode->lock);
        {
                for (index = 0; index < inode->table->ctxcount; index++) {
                        if (inode->_ctx[index].xl_key == xlator)
                                break;
                }

                if (index == inode->table->ctxcount) {
                        ret = -1;
                        goto unlock;
                }

                if (value1)
                        *value1 = inode->_ctx[index].value1;
                if (value2)
                        *value2 = inode->_ctx[index].value2;

                inode->_ctx[index].key    = 0;
                inode->_ctx[index].value1 = 0;
                inode->_ctx[index].value2 = 0;
        }
unlock:
        UNLOCK (&inode->lock);

        return ret;
}


void
inode_dump (inode_t *inode, char *prefix)
{
        int                ret       = -1;
        xlator_t          *xl        = NULL;
        int                i         = 0;
        fd_t              *fd        = NULL;
        struct _inode_ctx *inode_ctx = NULL;
        struct list_head fd_list;

        if (!inode)
                return;

        INIT_LIST_HEAD (&fd_list);

        ret = TRY_LOCK(&inode->lock);
        if (ret != 0) {
                return;
        }

        {
                gf_proc_dump_write("gfid", "%s", uuid_utoa (inode->gfid));
                gf_proc_dump_write("nlookup", "%ld", inode->nlookup);
                gf_proc_dump_write("fd-count", "%u", inode->fd_count);
                gf_proc_dump_write("ref", "%u", inode->ref);
                gf_proc_dump_write("ia_type", "%d", inode->ia_type);
                if (inode->_ctx) {
                        inode_ctx = GF_CALLOC (inode->table->ctxcount,
                                               sizeof (*inode_ctx),
                                               gf_common_mt_inode_ctx);
                        if (inode_ctx == NULL) {
                                goto unlock;
                        }

                        for (i = 0; i < inode->table->ctxcount; i++) {
                                inode_ctx[i] = inode->_ctx[i];
                        }
                }

		if (dump_options.xl_options.dump_fdctx != _gf_true)
			goto unlock;


                list_for_each_entry (fd, &inode->fd_list, inode_list) {
                        fd_ctx_dump (fd, prefix);
                }
        }
unlock:
        UNLOCK(&inode->lock);

        if (inode_ctx && (dump_options.xl_options.dump_inodectx == _gf_true)) {
                for (i = 0; i < inode->table->ctxcount; i++) {
                        if (inode_ctx[i].xl_key) {
                                xl = (xlator_t *)(long)inode_ctx[i].xl_key;
                                if (xl->dumpops && xl->dumpops->inodectx)
                                        xl->dumpops->inodectx (xl, inode);
                        }
                }
        }

        GF_FREE (inode_ctx);

        return;
}

void
inode_table_dump (inode_table_t *itable, char *prefix)
{

        char    key[GF_DUMP_MAX_BUF_LEN];
        int     ret = 0;

        if (!itable)
                return;

        memset(key, 0, sizeof(key));
        ret = pthread_mutex_trylock(&itable->lock);

        if (ret != 0) {
                return;
        }

        gf_proc_dump_build_key(key, prefix, "hashsize");
        gf_proc_dump_write(key, "%d", itable->hashsize);
        gf_proc_dump_build_key(key, prefix, "name");
        gf_proc_dump_write(key, "%s", itable->name);

        gf_proc_dump_build_key(key, prefix, "lru_limit");
        gf_proc_dump_write(key, "%d", itable->lru_limit);
        gf_proc_dump_build_key(key, prefix, "active_size");
        gf_proc_dump_write(key, "%d", itable->active_size);
        gf_proc_dump_build_key(key, prefix, "lru_size");
        gf_proc_dump_write(key, "%d", itable->lru_size);
        gf_proc_dump_build_key(key, prefix, "purge_size");
        gf_proc_dump_write(key, "%d", itable->purge_size);

        INODE_DUMP_LIST(&itable->active, key, prefix, "active");
        INODE_DUMP_LIST(&itable->lru, key, prefix, "lru");
        INODE_DUMP_LIST(&itable->purge, key, prefix, "purge");

        pthread_mutex_unlock(&itable->lock);
}

void
inode_dump_to_dict (inode_t *inode, char *prefix, dict_t *dict)
{
        int             ret = -1;
        char            key[GF_DUMP_MAX_BUF_LEN] = {0,};

        ret = TRY_LOCK (&inode->lock);
        if (ret)
                return;

        memset (key, 0, sizeof (key));
        snprintf (key, sizeof (key), "%s.gfid", prefix);
        ret = dict_set_dynstr (dict, key, gf_strdup (uuid_utoa (inode->gfid)));
        if (ret)
                goto out;

        memset (key, 0, sizeof (key));
        snprintf (key, sizeof (key), "%s.nlookup", prefix);
        ret = dict_set_uint64 (dict, key, inode->nlookup);
        if (ret)
                goto out;

        memset (key, 0, sizeof (key));
        snprintf (key, sizeof (key), "%s.ref", prefix);
        ret = dict_set_uint32 (dict, key, inode->ref);
        if (ret)
                goto out;

        memset (key, 0, sizeof (key));
        snprintf (key, sizeof (key), "%s.ia_type", prefix);
        ret = dict_set_int32 (dict, key, inode->ia_type);

out:
        UNLOCK (&inode->lock);
        return;
}

void
inode_table_dump_to_dict (inode_table_t *itable, char *prefix, dict_t *dict)
{
        char            key[GF_DUMP_MAX_BUF_LEN] = {0,};
        int             ret = 0;
        inode_t         *inode = NULL;
        int             count = 0;

        ret = pthread_mutex_trylock (&itable->lock);
        if (ret)
                return;

        memset (key, 0, sizeof (key));
        snprintf (key, sizeof (key), "%s.itable.active_size", prefix);
        ret = dict_set_uint32 (dict, key, itable->active_size);
        if (ret)
                goto out;

        memset (key, 0, sizeof (key));
        snprintf (key, sizeof (key), "%s.itable.lru_size", prefix);
        ret = dict_set_uint32 (dict, key, itable->lru_size);
        if (ret)
                goto out;

        memset (key, 0, sizeof (key));
        snprintf (key, sizeof (key), "%s.itable.purge_size", prefix);
        ret = dict_set_uint32 (dict, key, itable->purge_size);
        if (ret)
                goto out;

        list_for_each_entry (inode, &itable->active, list) {
                memset (key, 0, sizeof (key));
                snprintf (key, sizeof (key), "%s.itable.active%d", prefix,
                          count++);
                inode_dump_to_dict (inode, key, dict);
        }
        count = 0;

        list_for_each_entry (inode, &itable->lru, list) {
                memset (key, 0, sizeof (key));
                snprintf (key, sizeof (key), "%s.itable.lru%d", prefix,
                          count++);
                inode_dump_to_dict (inode, key, dict);
        }
        count = 0;

        list_for_each_entry (inode, &itable->purge, list) {
                memset (key, 0, sizeof (key));
                snprintf (key, sizeof (key), "%s.itable.purge%d", prefix,
                          count++);
                inode_dump_to_dict (inode, key, dict);
        }

out:
        pthread_mutex_unlock (&itable->lock);

        return;
}
