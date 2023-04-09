#ifndef _ASACL_BTRFS_INC_
#define _ASACL_BTRFS_INC_

#include <linux/asacl.h>

#ifdef CONFIG_BTRFS_FS_ASACL

#define BTRFS_IS_ASACL(inode) IS_ASACL(inode)

extern PT_ASACL Btrfs_Get_Asacl(struct inode *ptInode);

extern int Btrfs_Set_Asacl(struct inode *ptInode, PT_ASACL ptasAcl, int bUpdateMode);

extern int Btrfs_Init_Asacl(struct btrfs_trans_handle *ptHandle, struct inode *ptInode, struct inode *ptParentInode);

extern void Btrfs_Init_Admin_Priv_Procfs(void);

#else /* CONFIG_BTRFS_FS_ASACL */

#define BTRFS_IS_ASACL(inode) (0)
#define Btrfs_Get_Asacl   NULL
#define Btrfs_Set_Asacl   NULL

static inline int Btrfs_Init_Asacl(struct btrfs_trans_handle *ptHandle, struct inode *ptInode, struct inode *ptParentInode)
{
	return 0;
}

static inline void Btrfs_Init_Admin_Priv_Procfs(void)
{
	return;
}

#endif /* CONFIG_BTRFS_FS_ASACL */

#endif /* _ASACL_BTRFS_INC_ */
