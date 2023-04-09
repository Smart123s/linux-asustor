/* Copyright (c) 2011-2020  Asustor Systems, Inc.  All Rights Reserved. */
/** \file asacl.c
 * \brief The implementation of the functions of ASACL management.
 *
 * - History
 *  - 2014/04/23		clko	File created.
 *  - 2019/01/27		clko	Modified to adapt to kernel 4.14.x.
 */
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/asacl.h>

#define INIT_MODE_EQUIV_PERM  (ASACL_PERM_READ_DATA_OR_LIST_DIR | ASACL_PERM_WRITE_DATA_OR_ADD_FILE | \
								ASACL_PERM_APPEND_DATA_OR_ADD_DIR | ASACL_PERM_EXECUTE_OR_TRAVERSE)

#define DEFAULT_PERM_EVERYONE	(ASACL_PERM_READ_DATA_OR_LIST_DIR | ASACL_PERM_WRITE_DATA_OR_ADD_FILE | \
									ASACL_PERM_APPEND_DATA_OR_ADD_DIR | ASACL_PERM_READ_EX_ATTRS | \
									ASACL_PERM_WRITE_EX_ATTRS | ASACL_PERM_EXECUTE_OR_TRAVERSE | \
									ASACL_PERM_READ_ATTRS | ASACL_PERM_WRITE_ATTRS | ASACL_PERM_DELETE | \
									ASACL_PERM_READ_PERM | ASACL_PERM_DELETE_CHILD)

#define SZ_ADMIN_PRIV_PROCFS		"as_admpriv"
#define CN_DEFAULT_ACL_ENTRY		2		///< The number of entries of the default ACL.
static int g_iAdmPrivType = IDTYPE_ADMIN_PRIV_INIT;
static int g_ryidAdmPriv[3] = { ADMIN_PRIV_IDENTIFIER, -1, -1 };


PT_ASACL Get_Cached_Asacl(struct inode *ptInode)
{
	PT_ASACL  *pptaclTmp = &(ptInode->i_asacl), ptasAcl;
	return ptasAcl;
}

PT_ASACL Get_Cached_Asacl_RCU(struct inode *ptInode)
{
	return rcu_dereference(ptInode->i_asacl);
}

void Set_Cached_Asacl(struct inode *ptInode, PT_ASACL ptasAcl)
{
}

void Forget_Cached_Asacl(struct inode *ptInode)
{
}

int Alloc_Asacl_Obj(int cnEntry, PPT_ASACL pptaclBuf)
{
	return 0;
}

PT_ASACL Get_Asacl(struct inode *ptInode)
{
	PT_ASACL  ptasAcl;

	return ptasAcl;
}

int Check_Asacl_Permission(struct user_namespace *ptMntUsrNs, struct inode *ptInode,
							const PT_ASACL ptasAcl, uint16_t mMask)
{
	return 0;
}

int Set_File_Mode_After_Updating_Asacl(const PT_ASACL ptasAcl, struct inode *ptInode)
{
	return 0;
}

int Create_Asacl_For_New_File(struct inode *ptParentInode, struct inode *ptInode, PPT_ASACL pptasAcl)
{
	return 0;
}

int Estimate_New_File_Asacl_Xattr_Size(umode_t mMode, PT_ASACL ptaclParent)
{
	return 0;
}

int Check_Asacl(struct user_namespace *ptMntUsrNs, struct inode *ptInode, int mWant)
{
	return 0;
}

int Check_Asacl_Without_RCU(struct user_namespace *ptMntUsrNs, struct inode *ptInode, int mAsaclMask)
{
	return 0;
}

int Asacl_Chown(struct inode *ptInode, int bOwnerIsGroup)
{
	return 0;
}

int Asacl_Chmod(struct inode *ptInode)
{
	return 0;
}

void Init_Admin_Priv_Procfs(void)
{
	return;
}

int If_Have_Admin_Privilege(void)
{
	return 0;
}

size_t Get_Asacl_Xattr_Size(int cnEntry)
{
	return 0;
}

int Xattr_To_Asacl(const void *pstXattr, size_t cbSizeXattr, PPT_ASACL pptaclBuf)
{
	return 0;
}

int Asacl_To_Xattr(const PT_ASACL ptasAcl, size_t *pcbXattrBuf, void *pstXattr)
{
	return 0;
}

static bool Asacl_Xattr_List(struct dentry *dentry)
{
	return 0;
}

static int Asacl_Xattr_Get(const struct xattr_handler *handler, struct dentry *unused,
							struct inode *inode, const char *name, void *buffer, size_t buffer_size)
{
	return 0;
}

static int Asacl_Xattr_Set(const struct xattr_handler *handler, struct user_namespace *ptMntUsrNs,
							struct dentry *unused, struct inode *inode, const char *name,
							const void *value, size_t size, int flags)
{
	return 0;
}

/// The handler for process ASACL extended attribute (system.asacl).
const struct xattr_handler  Asacl_Xattr_Handler =
{
	.name	= ASACL_XATTR_TAG,
	.list	= Asacl_Xattr_List,
	.get	= Asacl_Xattr_Get,
	.set	= Asacl_Xattr_Set,
};
