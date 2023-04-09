#ifndef _ASACL_EXT4_INC_
#define _ASACL_EXT4_INC_

#include <linux/asacl.h>

#ifdef CONFIG_EXT4_FS_ASACL

#define EXT4_IS_ASACL(inode) IS_ASACL(inode)

extern PT_ASACL Ext4_Get_Asacl(struct inode *ptInode);

extern int Ext4_Set_Asacl(struct inode *ptInode, PT_ASACL ptasAcl, int bUpdateMode);

extern int Ext4_Init_Asacl(handle_t *ptHandle, struct inode *ptInode, struct inode *ptParentInode);

extern void Ext4_Init_Admin_Priv_Procfs(void);

#else /* CONFIG_EXT4_FS_ASACL */

#define EXT4_IS_ASACL(inode) (0)
#define Ext4_Get_Asacl		NULL
#define Ext4_Set_Asacl		NULL

static inline int Ext4_Init_Asacl(handle_t *ptHandle, struct inode *ptInode, struct inode *ptParentInode)
{
	return 0;
}

#if 0
static inline int Ext4_Estimate_New_File_Asacl_Xattr_Size(umode_t mMode, struct inode *ptParentInode)
{
	return 0;
}
#endif

static inline void Ext4_Init_Admin_Priv_Procfs(void)
{
	return;
}

#endif /* CONFIG_EXT4_FS_ASACL */

#endif /* _ASACL_EXT4_INC_ */
