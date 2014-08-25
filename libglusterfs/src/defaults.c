/*
  Copyright (c) 2008-2012 Red Hat, Inc. <http://www.redhat.com>
  This file is part of GlusterFS.

  This file is licensed to you under your choice of the GNU Lesser
  General Public License, version 3 or any later version (LGPLv3 or
  later), or the GNU General Public License, version 2 (GPLv2), in all
  cases as published by the Free Software Foundation.
*/

/* libglusterfs/src/defaults.c:
   This file contains functions, which are used to fill the 'fops', 'cbk'
   structures in the xlator structures, if they are not written. Here, all the
   function calls are plainly forwared to the first child of the xlator, and
   all the *_cbk function does plain STACK_UNWIND of the frame, and returns.

   This function also implements *_resume () functions, which does same
   operation as a fop().

   All the functions are plain enough to understand.
*/

#ifndef _CONFIG_H
#define _CONFIG_H
#include "config.h"
#endif

#include "xlator.h"

/* _CBK function section */

int32_t
default_lookup_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                    int32_t op_ret, int32_t op_errno, inode_t *inode,
                    struct iatt *buf, dict_t *xdata, struct iatt *postparent)
{
        STACK_UNWIND_STRICT (lookup, frame, op_ret, op_errno, inode, buf,
                             xdata, postparent);
        return 0;
}

int32_t
default_stat_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int32_t op_ret, int32_t op_errno, struct iatt *buf,
                  dict_t *xdata)
{
        STACK_UNWIND_STRICT (stat, frame, op_ret, op_errno, buf, xdata);
        return 0;
}


int32_t
default_truncate_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno, struct iatt *prebuf,
                      struct iatt *postbuf,
                      dict_t *xdata)
{
        STACK_UNWIND_STRICT (truncate, frame, op_ret, op_errno, prebuf,
                             postbuf, xdata);
        return 0;
}

int32_t
default_ftruncate_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                       int32_t op_ret, int32_t op_errno, struct iatt *prebuf,
                       struct iatt *postbuf,
                       dict_t *xdata)
{
        STACK_UNWIND_STRICT (ftruncate, frame, op_ret, op_errno, prebuf,
                             postbuf, xdata);
        return 0;
}

int32_t
default_access_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                    int32_t op_ret, int32_t op_errno,
                    dict_t *xdata)
{
        STACK_UNWIND_STRICT (access, frame, op_ret, op_errno, xdata);
        return 0;
}

int32_t
default_readlink_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno, const char *path,
                      struct iatt *buf, dict_t *xdata)
{
        STACK_UNWIND_STRICT (readlink, frame, op_ret, op_errno, path, buf,
                             xdata);
        return 0;
}


int32_t
default_mknod_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, inode_t *inode,
                   struct iatt *buf, struct iatt *preparent,
                   struct iatt *postparent, dict_t *xdata)
{
        STACK_UNWIND_STRICT (mknod, frame, op_ret, op_errno, inode,
                             buf, preparent, postparent, xdata);
        return 0;
}

int32_t
default_mkdir_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, inode_t *inode,
                   struct iatt *buf, struct iatt *preparent,
                   struct iatt *postparent, dict_t *xdata)
{
        STACK_UNWIND_STRICT (mkdir, frame, op_ret, op_errno, inode,
                             buf, preparent, postparent, xdata);
        return 0;
}

int32_t
default_unlink_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                    int32_t op_ret, int32_t op_errno, struct iatt *preparent,
                    struct iatt *postparent, dict_t *xdata)
{
        STACK_UNWIND_STRICT (unlink, frame, op_ret, op_errno, preparent,
                             postparent, xdata);
        return 0;
}

int32_t
default_rmdir_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, struct iatt *preparent,
                   struct iatt *postparent,
                   dict_t *xdata)
{
        STACK_UNWIND_STRICT (rmdir, frame, op_ret, op_errno, preparent,
                             postparent, xdata);
        return 0;
}


int32_t
default_symlink_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno, inode_t *inode,
                     struct iatt *buf, struct iatt *preparent,
                     struct iatt *postparent, dict_t *xdata)
{
        STACK_UNWIND_STRICT (symlink, frame, op_ret, op_errno, inode, buf,
                             preparent, postparent, xdata);
        return 0;
}


int32_t
default_rename_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                    int32_t op_ret, int32_t op_errno, struct iatt *buf,
                    struct iatt *preoldparent, struct iatt *postoldparent,
                    struct iatt *prenewparent, struct iatt *postnewparent,
                    dict_t *xdata)
{
        STACK_UNWIND_STRICT (rename, frame, op_ret, op_errno, buf, preoldparent,
                             postoldparent, prenewparent, postnewparent, xdata);
        return 0;
}


int32_t
default_link_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int32_t op_ret, int32_t op_errno, inode_t *inode,
                  struct iatt *buf, struct iatt *preparent,
                  struct iatt *postparent,
                  dict_t *xdata)
{
        STACK_UNWIND_STRICT (link, frame, op_ret, op_errno, inode, buf,
                             preparent, postparent, xdata);
        return 0;
}


int32_t
default_create_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                    int32_t op_ret, int32_t op_errno, fd_t *fd, inode_t *inode,
                    struct iatt *buf, struct iatt *preparent,
                    struct iatt *postparent,
                    dict_t *xdata)
{
        STACK_UNWIND_STRICT (create, frame, op_ret, op_errno, fd, inode, buf,
                             preparent, postparent, xdata);
        return 0;
}

int32_t
default_open_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int32_t op_ret, int32_t op_errno, fd_t *fd,
                  dict_t *xdata)
{
        STACK_UNWIND_STRICT (open, frame, op_ret, op_errno, fd, xdata);
        return 0;
}

int32_t
default_readv_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, struct iovec *vector,
                   int32_t count, struct iatt *stbuf, struct iobref *iobref,
                   dict_t *xdata)
{
        STACK_UNWIND_STRICT (readv, frame, op_ret, op_errno, vector, count,
                             stbuf, iobref, xdata);
        return 0;
}


int32_t
default_writev_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                    int32_t op_ret, int32_t op_errno, struct iatt *prebuf,
                    struct iatt *postbuf,
                    dict_t *xdata)
{
        STACK_UNWIND_STRICT (writev, frame, op_ret, op_errno, prebuf, postbuf, xdata);
        return 0;
}


int32_t
default_flush_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno,
                   dict_t *xdata)
{
        STACK_UNWIND_STRICT (flush, frame, op_ret, op_errno, xdata);
        return 0;
}



int32_t
default_fsync_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, struct iatt *prebuf,
                   struct iatt *postbuf,
                   dict_t *xdata)
{
        STACK_UNWIND_STRICT (fsync, frame, op_ret, op_errno, prebuf, postbuf,
                             xdata);
        return 0;
}

int32_t
default_fstat_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, struct iatt *buf,
                   dict_t *xdata)
{
        STACK_UNWIND_STRICT (fstat, frame, op_ret, op_errno, buf, xdata);
        return 0;
}

int32_t
default_opendir_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno, fd_t *fd,
                     dict_t *xdata)
{
        STACK_UNWIND_STRICT (opendir, frame, op_ret, op_errno, fd, xdata);
        return 0;
}

int32_t
default_fsyncdir_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno,
                      dict_t *xdata)
{
        STACK_UNWIND_STRICT (fsyncdir, frame, op_ret, op_errno, xdata);
        return 0;
}

int32_t
default_statfs_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                    int32_t op_ret, int32_t op_errno, struct statvfs *buf,
                    dict_t *xdata)
{
        STACK_UNWIND_STRICT (statfs, frame, op_ret, op_errno, buf, xdata);
        return 0;
}


int32_t
default_setxattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno,
                      dict_t *xdata)
{
        STACK_UNWIND_STRICT (setxattr, frame, op_ret, op_errno, xdata);
        return 0;
}


int32_t
default_fsetxattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                       int32_t op_ret, int32_t op_errno,
                       dict_t *xdata)
{
        STACK_UNWIND_STRICT (fsetxattr, frame, op_ret, op_errno, xdata);
        return 0;
}



int32_t
default_fgetxattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                       int32_t op_ret, int32_t op_errno, dict_t *dict,
                       dict_t *xdata)
{
        STACK_UNWIND_STRICT (fgetxattr, frame, op_ret, op_errno, dict, xdata);
        return 0;
}


int32_t
default_getxattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno, dict_t *dict,
                      dict_t *xdata)
{
        STACK_UNWIND_STRICT (getxattr, frame, op_ret, op_errno, dict, xdata);
        return 0;
}

int32_t
default_xattrop_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno, dict_t *dict,
                     dict_t *xdata)
{
        STACK_UNWIND_STRICT (xattrop, frame, op_ret, op_errno, dict, xdata);
        return 0;
}

int32_t
default_fxattrop_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno, dict_t *dict,
                      dict_t *xdata)
{
        STACK_UNWIND_STRICT (fxattrop, frame, op_ret, op_errno, dict, xdata);
        return 0;
}


int32_t
default_removexattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                         int32_t op_ret, int32_t op_errno,
                         dict_t *xdata)
{
        STACK_UNWIND_STRICT (removexattr, frame, op_ret, op_errno, xdata);
        return 0;
}


int32_t
default_fremovexattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                          int32_t op_ret, int32_t op_errno,
                          dict_t *xdata)
{
        STACK_UNWIND_STRICT (fremovexattr, frame, op_ret, op_errno, xdata);
        return 0;
}

int32_t
default_lk_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                int32_t op_ret, int32_t op_errno, struct gf_flock *lock,
                dict_t *xdata)
{
        STACK_UNWIND_STRICT (lk, frame, op_ret, op_errno, lock, xdata);
        return 0;
}

int32_t
default_inodelk_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno,
                     dict_t *xdata)
{
        STACK_UNWIND_STRICT (inodelk, frame, op_ret, op_errno, xdata);
        return 0;
}


int32_t
default_finodelk_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno,
                      dict_t *xdata)
{
        STACK_UNWIND_STRICT (finodelk, frame, op_ret, op_errno, xdata);
        return 0;
}

int32_t
default_entrylk_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno,
                     dict_t *xdata)
{
        STACK_UNWIND_STRICT (entrylk, frame, op_ret, op_errno, xdata);
        return 0;
}

int32_t
default_fentrylk_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno,
                      dict_t *xdata)
{
        STACK_UNWIND_STRICT (fentrylk, frame, op_ret, op_errno, xdata);
        return 0;
}


int32_t
default_rchecksum_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                       int32_t op_ret, int32_t op_errno, uint32_t weak_checksum,
                       uint8_t *strong_checksum,
                       dict_t *xdata)
{
        STACK_UNWIND_STRICT (rchecksum, frame, op_ret, op_errno, weak_checksum,
                             strong_checksum, xdata);
        return 0;
}


int32_t
default_readdir_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno, gf_dirent_t *entries,
                     dict_t *xdata)
{
        STACK_UNWIND_STRICT (readdir, frame, op_ret, op_errno, entries, xdata);
        return 0;
}


int32_t
default_readdirp_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno, gf_dirent_t *entries,
                      dict_t *xdata)
{
        STACK_UNWIND_STRICT (readdirp, frame, op_ret, op_errno, entries, xdata);
        return 0;
}

int32_t
default_setattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno, struct iatt *statpre,
                     struct iatt *statpost,
                     dict_t *xdata)
{
        STACK_UNWIND_STRICT (setattr, frame, op_ret, op_errno, statpre,
                             statpost, xdata);
        return 0;
}

int32_t
default_fsetattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno, struct iatt *statpre,
                      struct iatt *statpost,
                      dict_t *xdata)
{
        STACK_UNWIND_STRICT (fsetattr, frame, op_ret, op_errno, statpre,
                             statpost, xdata);
        return 0;
}

int32_t
default_getspec_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno, char *spec_data)
{
        STACK_UNWIND_STRICT (getspec, frame, op_ret, op_errno, spec_data);
        return 0;
}

/* RESUME */

int32_t
default_fgetxattr_resume (call_frame_t *frame, xlator_t *this, fd_t *fd,
                          const char *name, dict_t *xdata)
{
        STACK_WIND (frame, default_fgetxattr_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->fgetxattr, fd, name, xdata);
        return 0;
}

int32_t
default_fsetxattr_resume (call_frame_t *frame, xlator_t *this, fd_t *fd,
                          dict_t *dict, int32_t flags, dict_t *xdata)
{
        STACK_WIND (frame, default_fsetxattr_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->fsetxattr, fd, dict, flags, xdata);
        return 0;
}

int32_t
default_setxattr_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                         dict_t *dict, int32_t flags, dict_t *xdata)
{
        STACK_WIND (frame, default_setxattr_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->setxattr, loc, dict, flags, xdata);
        return 0;
}

int32_t
default_statfs_resume (call_frame_t *frame, xlator_t *this, loc_t *loc, dict_t *xdata)
{
        STACK_WIND (frame, default_statfs_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->statfs, loc, xdata);
        return 0;
}

int32_t
default_fsyncdir_resume (call_frame_t *frame, xlator_t *this, fd_t *fd,
                         int32_t flags, dict_t *xdata)
{
        STACK_WIND (frame, default_fsyncdir_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->fsyncdir, fd, flags, xdata);
        return 0;
}

int32_t
default_opendir_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                        fd_t *fd, dict_t *xdata)
{
        STACK_WIND (frame, default_opendir_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->opendir, loc, fd, xdata);
        return 0;
}

int32_t
default_fstat_resume (call_frame_t *frame, xlator_t *this, fd_t *fd, dict_t *xdata)
{
        STACK_WIND (frame, default_fstat_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->fstat, fd, xdata);
        return 0;
}

int32_t
default_fsync_resume (call_frame_t *frame, xlator_t *this, fd_t *fd,
                      int32_t flags, dict_t *xdata)
{
        STACK_WIND (frame, default_fsync_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->fsync, fd, flags, xdata);
        return 0;
}

int32_t
default_flush_resume (call_frame_t *frame, xlator_t *this, fd_t *fd, dict_t *xdata)
{
        STACK_WIND (frame, default_flush_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->flush, fd, xdata);
        return 0;
}

int32_t
default_writev_resume (call_frame_t *frame, xlator_t *this, fd_t *fd,
                       struct iovec *vector, int32_t count, off_t off,
                       uint32_t flags, struct iobref *iobref, dict_t *xdata)
{
        STACK_WIND (frame, default_writev_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->writev, fd, vector, count, off,
                    flags, iobref, xdata);
        return 0;
}

int32_t
default_readv_resume (call_frame_t *frame, xlator_t *this, fd_t *fd,
                      size_t size, off_t offset, uint32_t flags, dict_t *xdata)
{
        STACK_WIND (frame, default_readv_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->readv, fd, size, offset, flags, xdata);
        return 0;
}


int32_t
default_open_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                     int32_t flags, fd_t *fd, dict_t *xdata)
{
        STACK_WIND (frame, default_open_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->open, loc, flags, fd, xdata);
        return 0;
}

int32_t
default_create_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                       int32_t flags, mode_t mode, mode_t umask, fd_t *fd,
                       dict_t *xdata)
{
        STACK_WIND (frame, default_create_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->create, loc, flags, mode, umask,
                    fd, xdata);
        return 0;
}

int32_t
default_link_resume (call_frame_t *frame, xlator_t *this, loc_t *oldloc,
                     loc_t *newloc, dict_t *xdata)
{
        STACK_WIND (frame, default_link_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->link, oldloc, newloc, xdata);
        return 0;
}

int32_t
default_rename_resume (call_frame_t *frame, xlator_t *this, loc_t *oldloc,
                       loc_t *newloc, dict_t *xdata)
{
        STACK_WIND (frame, default_rename_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->rename, oldloc, newloc, xdata);
        return 0;
}


int
default_symlink_resume (call_frame_t *frame, xlator_t *this,
                        const char *linkpath, loc_t *loc, mode_t umask,
                        dict_t *xdata)
{
        STACK_WIND (frame, default_symlink_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->symlink, linkpath, loc, umask,
                    xdata);
        return 0;
}

int32_t
default_rmdir_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                      int flags, dict_t *xdata)
{
        STACK_WIND (frame, default_rmdir_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->rmdir, loc, flags, xdata);
        return 0;
}

int32_t
default_unlink_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                       int xflag, dict_t *xdata)
{
        STACK_WIND (frame, default_unlink_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->unlink, loc, xflag, xdata);
        return 0;
}

int
default_mkdir_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                      mode_t mode, mode_t umask, dict_t *xdata)
{
        STACK_WIND (frame, default_mkdir_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->mkdir, loc, mode, umask, xdata);
        return 0;
}


int
default_mknod_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                      mode_t mode, dev_t rdev, mode_t umask, dict_t *xdata)
{
        STACK_WIND (frame, default_mknod_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->mknod, loc, mode, rdev, umask,
                    xdata);
        return 0;
}

int32_t
default_readlink_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                         size_t size, dict_t *xdata)
{
        STACK_WIND (frame, default_readlink_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->readlink, loc, size, xdata);
        return 0;
}


int32_t
default_access_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                       int32_t mask, dict_t *xdata)
{
        STACK_WIND (frame, default_access_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->access, loc, mask, xdata);
        return 0;
}

int32_t
default_ftruncate_resume (call_frame_t *frame, xlator_t *this, fd_t *fd,
                          off_t offset, dict_t *xdata)
{
        STACK_WIND (frame, default_ftruncate_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->ftruncate, fd, offset, xdata);
        return 0;
}

int32_t
default_getxattr_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                         const char *name, dict_t *xdata)
{
        STACK_WIND (frame, default_getxattr_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->getxattr, loc, name, xdata);
        return 0;
}


int32_t
default_xattrop_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                        gf_xattrop_flags_t flags, dict_t *dict, dict_t *xdata)
{
        STACK_WIND (frame, default_xattrop_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->xattrop, loc, flags, dict, xdata);
        return 0;
}

int32_t
default_fxattrop_resume (call_frame_t *frame, xlator_t *this, fd_t *fd,
                         gf_xattrop_flags_t flags, dict_t *dict, dict_t *xdata)
{
        STACK_WIND (frame, default_fxattrop_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->fxattrop, fd, flags, dict, xdata);
        return 0;
}

int32_t
default_removexattr_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                            const char *name, dict_t *xdata)
{
        STACK_WIND (frame, default_removexattr_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->removexattr, loc, name, xdata);
        return 0;
}

int32_t
default_fremovexattr_resume (call_frame_t *frame, xlator_t *this, fd_t *fd,
                             const char *name, dict_t *xdata)
{
        STACK_WIND (frame, default_fremovexattr_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->fremovexattr, fd, name, xdata);
        return 0;
}

int32_t
default_lk_resume (call_frame_t *frame, xlator_t *this, fd_t *fd,
                   int32_t cmd, struct gf_flock *lock, dict_t *xdata)
{
        STACK_WIND (frame, default_lk_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->lk, fd, cmd, lock, xdata);
        return 0;
}


int32_t
default_inodelk_resume (call_frame_t *frame, xlator_t *this,
                        const char *volume, loc_t *loc, int32_t cmd,
                        struct gf_flock *lock,
                        dict_t *xdata)
{
        STACK_WIND (frame, default_inodelk_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->inodelk,
                    volume, loc, cmd, lock, xdata);
        return 0;
}

int32_t
default_finodelk_resume (call_frame_t *frame, xlator_t *this,
                         const char *volume, fd_t *fd, int32_t cmd,
                         struct gf_flock *lock,
                         dict_t *xdata)
{
        STACK_WIND (frame, default_finodelk_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->finodelk,
                    volume, fd, cmd, lock, xdata);
        return 0;
}

int32_t
default_entrylk_resume (call_frame_t *frame, xlator_t *this,
                        const char *volume, loc_t *loc, const char *basename,
                        entrylk_cmd cmd, entrylk_type type,
                        dict_t *xdata)
{
        STACK_WIND (frame, default_entrylk_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->entrylk,
                    volume, loc, basename, cmd, type, xdata);
        return 0;
}

int32_t
default_fentrylk_resume (call_frame_t *frame, xlator_t *this,
                         const char *volume, fd_t *fd, const char *basename,
                         entrylk_cmd cmd, entrylk_type type,
                         dict_t *xdata)
{
        STACK_WIND (frame, default_fentrylk_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->fentrylk,
                    volume, fd, basename, cmd, type, xdata);
        return 0;
}

int32_t
default_rchecksum_resume (call_frame_t *frame, xlator_t *this, fd_t *fd,
                          off_t offset, int32_t len,
                          dict_t *xdata)
{
        STACK_WIND (frame, default_rchecksum_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->rchecksum, fd, offset, len, xdata);
        return 0;
}


int32_t
default_readdir_resume (call_frame_t *frame, xlator_t *this, fd_t *fd,
                        size_t size, off_t off,
                        dict_t *xdata)
{
        STACK_WIND (frame, default_readdir_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->readdir, fd, size, off, xdata);
        return 0;
}


int32_t
default_readdirp_resume (call_frame_t *frame, xlator_t *this, fd_t *fd,
                         size_t size, off_t off, dict_t *xdata)
{
        STACK_WIND (frame, default_readdirp_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->readdirp, fd, size, off, xdata);
        return 0;
}

int32_t
default_setattr_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                        struct iatt *stbuf, int32_t valid,
                        dict_t *xdata)
{
        STACK_WIND (frame, default_setattr_cbk, FIRST_CHILD (this),
                    FIRST_CHILD (this)->fops->setattr, loc, stbuf, valid, xdata);
        return 0;
}

int32_t
default_truncate_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                         off_t offset,
                         dict_t *xdata)
{
        STACK_WIND (frame, default_truncate_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->truncate, loc, offset, xdata);
        return 0;
}

int32_t
default_stat_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                     dict_t *xdata)
{
        STACK_WIND (frame, default_stat_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->stat, loc, xdata);
        return 0;
}

int32_t
default_lookup_resume (call_frame_t *frame, xlator_t *this, loc_t *loc,
                       dict_t *xdata)
{
        STACK_WIND (frame, default_lookup_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->lookup, loc, xdata);
        return 0;
}

int32_t
default_fsetattr_resume (call_frame_t *frame, xlator_t *this, fd_t *fd,
                         struct iatt *stbuf, int32_t valid,
                         dict_t *xdata)
{
        STACK_WIND (frame, default_fsetattr_cbk, FIRST_CHILD (this),
                    FIRST_CHILD (this)->fops->fsetattr, fd, stbuf, valid, xdata);
        return 0;
}

/* FOPS */

int32_t
default_fgetxattr (call_frame_t *frame, xlator_t *this, fd_t *fd,
                   const char *name, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->fgetxattr, fd, name, xdata);
        return 0;
}

int32_t
default_fsetxattr (call_frame_t *frame, xlator_t *this, fd_t *fd, dict_t *dict,
                   int32_t flags, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->fsetxattr, fd, dict, flags,
                         xdata);
        return 0;
}

int32_t
default_setxattr (call_frame_t *frame, xlator_t *this, loc_t *loc, dict_t *dict,
                  int32_t flags, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->setxattr, loc, dict, flags,
                         xdata);
        return 0;
}

int32_t
default_statfs (call_frame_t *frame, xlator_t *this, loc_t *loc, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->statfs, loc, xdata);
        return 0;
}

int32_t
default_fsyncdir (call_frame_t *frame, xlator_t *this, fd_t *fd, int32_t flags, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->fsyncdir, fd, flags, xdata);
        return 0;
}

int32_t
default_opendir (call_frame_t *frame, xlator_t *this, loc_t *loc, fd_t *fd, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->opendir, loc, fd, xdata);
        return 0;
}

int32_t
default_fstat (call_frame_t *frame, xlator_t *this, fd_t *fd, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->fstat, fd, xdata);
        return 0;
}

int32_t
default_fsync (call_frame_t *frame, xlator_t *this, fd_t *fd, int32_t flags, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->fsync, fd, flags, xdata);
        return 0;
}

int32_t
default_flush (call_frame_t *frame, xlator_t *this, fd_t *fd, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->flush, fd, xdata);
        return 0;
}

int32_t
default_writev (call_frame_t *frame, xlator_t *this, fd_t *fd,
                struct iovec *vector, int32_t count, off_t off, uint32_t flags,
                struct iobref *iobref, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->writev, fd, vector, count,
                         off, flags, iobref, xdata);
        return 0;
}

int32_t
default_readv (call_frame_t *frame, xlator_t *this, fd_t *fd, size_t size,
               off_t offset, uint32_t flags, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->readv, fd, size, offset,
                         flags, xdata);
        return 0;
}


int32_t
default_open (call_frame_t *frame, xlator_t *this, loc_t *loc, int32_t flags,
              fd_t *fd, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->open, loc, flags, fd, xdata);
        return 0;
}

int32_t
default_create (call_frame_t *frame, xlator_t *this, loc_t *loc, int32_t flags,
                mode_t mode, mode_t umask, fd_t *fd, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->create, loc, flags, mode,
                         umask, fd, xdata);
        return 0;
}

int32_t
default_link (call_frame_t *frame, xlator_t *this, loc_t *oldloc, loc_t *newloc,
              dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->link, oldloc, newloc, xdata);
        return 0;
}

int32_t
default_rename (call_frame_t *frame, xlator_t *this, loc_t *oldloc,
                loc_t *newloc, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->rename, oldloc, newloc,
                         xdata);
        return 0;
}


int
default_symlink (call_frame_t *frame, xlator_t *this, const char *linkpath,
                 loc_t *loc, mode_t umask, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->symlink, linkpath, loc,
                         umask, xdata);
        return 0;
}

int32_t
default_rmdir (call_frame_t *frame, xlator_t *this, loc_t *loc, int flags,
               dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->rmdir, loc, flags, xdata);
        return 0;
}

int32_t
default_unlink (call_frame_t *frame, xlator_t *this, loc_t *loc, int xflag,
                dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->unlink, loc, xflag, xdata);
        return 0;
}

int
default_mkdir (call_frame_t *frame, xlator_t *this, loc_t *loc, mode_t mode,
               mode_t umask, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->mkdir, loc, mode, umask,
                         xdata);
        return 0;
}


int
default_mknod (call_frame_t *frame, xlator_t *this, loc_t *loc, mode_t mode,
               dev_t rdev, mode_t umask, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->mknod, loc, mode, rdev,
                         umask, xdata);
        return 0;
}

int32_t
default_readlink (call_frame_t *frame, xlator_t *this, loc_t *loc, size_t size, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->readlink, loc, size, xdata);
        return 0;
}


int32_t
default_access (call_frame_t *frame, xlator_t *this, loc_t *loc, int32_t mask, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->access, loc, mask, xdata);
        return 0;
}

int32_t
default_ftruncate (call_frame_t *frame, xlator_t *this, fd_t *fd, off_t offset, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->ftruncate, fd, offset, xdata);
        return 0;
}

int32_t
default_getxattr (call_frame_t *frame, xlator_t *this, loc_t *loc,
                  const char *name, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->getxattr, loc, name, xdata);
        return 0;
}


int32_t
default_xattrop (call_frame_t *frame, xlator_t *this, loc_t *loc,
                 gf_xattrop_flags_t flags, dict_t *dict, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->xattrop, loc, flags, dict,
                         xdata);
        return 0;
}

int32_t
default_fxattrop (call_frame_t *frame, xlator_t *this, fd_t *fd,
                  gf_xattrop_flags_t flags, dict_t *dict, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->fxattrop, fd, flags, dict,
                         xdata);
        return 0;
}

int32_t
default_removexattr (call_frame_t *frame, xlator_t *this, loc_t *loc,
                     const char *name, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->removexattr, loc, name,
                         xdata);
        return 0;
}

int32_t
default_fremovexattr (call_frame_t *frame, xlator_t *this, fd_t *fd,
                      const char *name, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->fremovexattr, fd, name,
                         xdata);
        return 0;
}

int32_t
default_lk (call_frame_t *frame, xlator_t *this, fd_t *fd,
            int32_t cmd, struct gf_flock *lock, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->lk, fd, cmd, lock, xdata);
        return 0;
}


int32_t
default_inodelk (call_frame_t *frame, xlator_t *this,
                 const char *volume, loc_t *loc, int32_t cmd,
                 struct gf_flock *lock,
                 dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->inodelk, volume, loc, cmd,
                         lock, xdata);
        return 0;
}

int32_t
default_finodelk (call_frame_t *frame, xlator_t *this,
                  const char *volume, fd_t *fd, int32_t cmd, struct gf_flock *lock,
                  dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->finodelk, volume, fd, cmd,
                         lock, xdata);
        return 0;
}

int32_t
default_entrylk (call_frame_t *frame, xlator_t *this,
                 const char *volume, loc_t *loc, const char *basename,
                 entrylk_cmd cmd, entrylk_type type,
                 dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->entrylk, volume, loc,
                         basename, cmd, type, xdata);
        return 0;
}

int32_t
default_fentrylk (call_frame_t *frame, xlator_t *this,
                  const char *volume, fd_t *fd, const char *basename,
                  entrylk_cmd cmd, entrylk_type type,
                  dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->fentrylk, volume, fd,
                         basename, cmd, type, xdata);
        return 0;
}

int32_t
default_rchecksum (call_frame_t *frame, xlator_t *this, fd_t *fd, off_t offset,
                   int32_t len,
                   dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->rchecksum, fd, offset, len,
                         xdata);
        return 0;
}


int32_t
default_readdir (call_frame_t *frame, xlator_t *this, fd_t *fd,
                 size_t size, off_t off,
                 dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->readdir, fd, size, off,
                         xdata);
        return 0;
}


int32_t
default_readdirp (call_frame_t *frame, xlator_t *this, fd_t *fd,
                  size_t size, off_t off, dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->readdirp, fd, size, off,
                         xdata);
        return 0;
}

int32_t
default_setattr (call_frame_t *frame, xlator_t *this, loc_t *loc,
                 struct iatt *stbuf, int32_t valid,
                 dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD (this),
                         FIRST_CHILD (this)->fops->setattr, loc, stbuf, valid,
                         xdata);
        return 0;
}

int32_t
default_truncate (call_frame_t *frame, xlator_t *this, loc_t *loc, off_t offset,
                  dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->truncate, loc, offset, xdata);
        return 0;
}

int32_t
default_stat (call_frame_t *frame, xlator_t *this, loc_t *loc,
              dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->stat, loc, xdata);
        return 0;
}

int32_t
default_lookup (call_frame_t *frame, xlator_t *this, loc_t *loc,
                dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->lookup, loc, xdata);
        return 0;
}

int32_t
default_fsetattr (call_frame_t *frame, xlator_t *this, fd_t *fd,
                  struct iatt *stbuf, int32_t valid,
                  dict_t *xdata)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD (this),
                         FIRST_CHILD (this)->fops->fsetattr, fd, stbuf, valid,
                         xdata);
        return 0;
}


int32_t
default_forget (xlator_t *this, inode_t *inode)
{
        gf_log_callingfn (this->name, GF_LOG_WARNING, "xlator does not "
                          "implement forget_cbk");
        return 0;
}


int32_t
default_releasedir (xlator_t *this, fd_t *fd)
{
        gf_log_callingfn (this->name, GF_LOG_WARNING, "xlator does not "
                          "implement releasedir_cbk");
        return 0;
}

int32_t
default_release (xlator_t *this, fd_t *fd)
{
        gf_log_callingfn (this->name, GF_LOG_WARNING, "xlator does not "
                          "implement release_cbk");
        return 0;
}

/* End of FOP/_CBK/_RESUME section */


/* Management operations */

int32_t
default_getspec (call_frame_t *frame, xlator_t *this, const char *key,
                 int32_t flags)
{
        STACK_WIND_TAIL (frame, FIRST_CHILD(this),
                         FIRST_CHILD(this)->fops->getspec, key, flags);
        return 0;
}

/* notify */
int
default_notify (xlator_t *this, int32_t event, void *data, ...)
{
        switch (event)
        {
        case GF_EVENT_PARENT_UP:
        case GF_EVENT_PARENT_DOWN:
        {
                xlator_list_t *list = this->children;

                while (list) {
                		// data is 'this'
                		// send event and this to every child  GF_EVENT_PARENT_DOWN GF_EVENT_PARENT_UP
                        xlator_notify (list->xlator, event, this);
                        list = list->next;
                }
        }
        break;
        case GF_EVENT_CHILD_CONNECTING:
        case GF_EVENT_CHILD_MODIFIED:
        case GF_EVENT_CHILD_DOWN:
        case GF_EVENT_CHILD_UP:
        case GF_EVENT_AUTH_FAILED:
        {
                xlator_list_t *parent = this->parents;
                /* Handle case of CHILD_* & AUTH_FAILED event specially, send it to fuse */
                if (!parent && this->ctx && this->ctx->master)
                		// data is this->graph not this
                        xlator_notify (this->ctx->master, event, this->graph, NULL);

                while (parent) {
                		// data is 'this'
                	    // send event and this to every parent about child event
                        if (parent->xlator->init_succeeded)
                                xlator_notify (parent->xlator, event,
                                               this, NULL);
                        parent = parent->next;
                }
        }
        break;
        default:
        {
                xlator_list_t *parent = this->parents;
                while (parent) {
                        if (parent->xlator->init_succeeded)
                                xlator_notify (parent->xlator, event,
                                               this, NULL);
                        parent = parent->next;
                }
        }
        }

        return 0;
}

int32_t
default_mem_acct_init (xlator_t *this)
{
        int     ret = -1;

        ret = xlator_mem_acct_init (this, gf_common_mt_end);

        return ret;
}
