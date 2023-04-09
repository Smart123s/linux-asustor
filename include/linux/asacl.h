#ifndef _ASUSTOR_ACL_INC_
#define _ASUSTOR_ACL_INC_
#include <linux/slab.h>
#include <linux/xattr.h>

#define FLAG_ASACL_MODE_COMPATIBLE	0x00000001		///< Flag to indicate if this ACL is file-mode compatible.
#define FLAG_ASACL_INHERIT_PARENT	0x00000002		///< Flag to indicate if including the inheritable permissions from parent. (Correspond to the Samba 'SEC_DESC_DACL_PROTECTED' flag.)
#define FLAG_ASACL_OWNER_IS_GROUP	0x00000004		///< Flag to indicate if the owner of this file is a group object.
#define FLAG_ASACL_MS_READ_ONLY		0x00000008		///< Flag to indicate if the Windows file attribute "Read only" is enabled or not.
/// Mask for valid ASACL flags.
#define MASK_VALID_ASACL_FLAGS		(FLAG_ASACL_MODE_COMPATIBLE | FLAG_ASACL_INHERIT_PARENT | \
										FLAG_ASACL_OWNER_IS_GROUP | FLAG_ASACL_MS_READ_ONLY)

#define FLAG_ASACE_FILE_INHERIT		0x00000001		///< Flag to indicate if this ACE will inherit to the files under this folder.
#define FLAG_ASACE_FOLDER_INHERIT	0x00000002		///< Flag to indicate if this ACE will inherit to the subfolders.
#define FLAG_ASACE_INHERIT_ONLY		0x00000004		///< Flag to indicate if this ACE if for inherit only (and won't apply to itself).
#define FLAG_ASACE_DENY_ACE			0x00000008		///< Flag to indicate if this ACE is a deny ACE.
#define FLAG_ASACE_NO_PROPAGATE		0x00000010		///< Flag to indicate if this ACE will only be inherited by it child item, and will not be propagate to grant child.
//#define FLAG_ASACE_INHERITED		0x00000020		///< Flag to indicate if this ACE is inherited from ancestors.

// Mask for valid ASACE flags.
#define MASK_VALID_ASACE_FLAGS			(FLAG_ASACE_FILE_INHERIT | FLAG_ASACE_FOLDER_INHERIT | \
											FLAG_ASACE_INHERIT_ONLY | FLAG_ASACE_DENY_ACE | FLAG_ASACE_NO_PROPAGATE)
// Mask for valid ASACE file flags.
#define MASK_VALID_ASACE_FILE_FLAGS		FLAG_ASACE_DENY_ACE

#define ASACL_PERM_READ_DATA_OR_LIST_DIR	0x00000001	///< Permission to read data / list directory.
#define ASACL_PERM_WRITE_DATA_OR_ADD_FILE	0x00000002	///< Permission to write data / add file.
#define ASACL_PERM_APPEND_DATA_OR_ADD_DIR	0x00000004	///< Permission to append data / add dir.
#define ASACL_PERM_READ_EX_ATTRS			0x00000008	///< Permission to read extended attributes.
#define ASACL_PERM_WRITE_EX_ATTRS			0x00000010	///< Permission to write extended attributes.
#define ASACL_PERM_EXECUTE_OR_TRAVERSE		0x00000020	///< Permission to execute / traverse.
#define ASACL_PERM_DELETE_CHILD				0x00000040	///< Permission to delete child file.
#define ASACL_PERM_READ_ATTRS				0x00000080	///< Permission to read attribute.
#define ASACL_PERM_WRITE_ATTRS				0x00000100	///< Permission to write attribute.
#define ASACL_PERM_DELETE					0x00000200	///< Permission to delete.
#define ASACL_PERM_READ_PERM				0x00000400	///< Permission to read file permission.
#define ASACL_PERM_WRITE_PERM				0x00000800	///< Permission to write file permission.
#define ASACL_PERM_TAKE_OWNERSHIP			0x00001000	///< Permission to take ownership.

/// The full control permission for file.
#define ASACL_PERM_FILE_FULL_CTRL		(ASACL_PERM_READ_DATA_OR_LIST_DIR | ASACL_PERM_WRITE_DATA_OR_ADD_FILE | \
											ASACL_PERM_APPEND_DATA_OR_ADD_DIR | ASACL_PERM_READ_EX_ATTRS | \
											ASACL_PERM_WRITE_EX_ATTRS | ASACL_PERM_EXECUTE_OR_TRAVERSE | \
											ASACL_PERM_READ_ATTRS | ASACL_PERM_WRITE_ATTRS | ASACL_PERM_DELETE | \
											ASACL_PERM_READ_PERM | ASACL_PERM_WRITE_PERM | ASACL_PERM_TAKE_OWNERSHIP)
/// The full control permission for dir.
#define ASACL_PERM_DIR_FULL_CTRL		(ASACL_PERM_FILE_FULL_CTRL | ASACL_PERM_DELETE_CHILD)

//#define MASK_VALID_ASACL_FILE_PERM		ASACL_PERM_FILE_FULL_CTRL
#define MASK_VALID_ASACL_DIR_PERM		ASACL_PERM_DIR_FULL_CTRL


#define ID_ASACE_TYPE_OWNER			0		///< The owner entry. (We only use this entry type to map the 'CREATOR OWNER' entry of Windows.)
#define ID_ASACE_TYPE_USER			1		///< The user entry.
#define ID_ASACE_TYPE_GROUP			2		///< The group entry.
#define ID_ASACE_TYPE_EVERYONE		3		///< The everyone entry.

#define CNMAX_ASACL_ENTRY_NUMBER		250					///< The maximum allowable entry number. (The explicit limitation for user.)
#define CNMAX_ASACL_ENTRY_NUM_SYSTEM	300					///< The maximum allowable entry number. (The implicit limitation for system.)
#define ASACL_REVISION_1				1					///< The ASACL revision 1.
#define ASACL_CURRENT_REVISION			ASACL_REVISION_1	///< The current ASACL revision.
#define ASACL_XATTR_TAG					"system.ASACL"		///< The extended attribute identifier for ASACL.
#define ASMAX_UINT8						((1U << 8) - 1)

// The types of the admin-privilege mechanism.
#define IDTYPE_ADMIN_PRIV_INIT		(-1)	///< The initial admin-privilege stat.
#define IDTYPE_ADMIN_PRIV_NONE		0		///< No admin-privilege is applied.
#define IDTYPE_ADMIN_PRIV_USER		1		///< Only the 'admin' user has the admin-privilege.
#define IDTYPE_ADMIN_PRIV_GROUP		2		///< The members of 'administrators' group have the admin-privilege.
#define DEFAULT_ADMIN_PRIV_TYPE		IDTYPE_ADMIN_PRIV_GROUP		///< The default admin-privilege type.
#define ADMIN_PRIV_IDENTIFIER		999		///< The uid/gid of the admin user or administrators group.
#define MAX_UID_GENERAL_ACCOUNT		65534	///< The maximum uid for general user.

/** \brief The type set. */
typedef struct _t_ace_type_
{
	uint8_t		idType:4;			///< The type of this entry. Check 'ID_ASACE_TYPE_XXX' for more detail.
	uint8_t		mPreserve:4;		///< The preserved bits. It is meaningless in the present.
} T_ACE_TYPE;

/** \brief The number set. */
typedef struct _t_ace_num_
{
	uint32_t	cnInherit:8;		///< The generation number of inheritance. 0 means no inherit.
	uint32_t	iIdentifier:24;		///< The identifier of this entry. It may be a uid or gid.
} T_ACE_NUM;

/** \brief The ACE struct of ASACL. */
typedef struct _t_asace_
{
	union
	{
		uint8_t		iTypeAlias;	///< Just a alias for 'tatType', we use it to make the casting more easier.
		T_ACE_TYPE	tatType;
	};
	uint8_t		mFlags;			///< ASACE flags. Check 'FLAG_ASACE_XXX' for more detail.
	uint16_t	mPerm;			///< The permission mask.
	union
	{
		uint32_t	iNumAlias;	///< Just a alias for 'tanNum', we use it to make the casting more easier.
		T_ACE_NUM	tanNum;
	};
} T_ASACE, *PT_ASACE, **PPT_ASACE;

/** \brief The struct for a ASACL object. */
typedef struct _t_asacl_
{
	refcount_t			tRefCount;		///< The reference counter.
	struct rcu_head		tRcuHead;
	int8_t		iRevision;		///< Revision number.
	uint8_t		mPreserve1;		///< The preserved bits. It is meaningless in the present.
	uint16_t	cnEntry;		///< The number of entries.
	uint16_t	mFlags;			///< ASACL flags. Check 'FLAG_ASACL_XXX' for more detail.
	uint16_t	mPreserve2;		///< The preserved bits. It is meaningless in the present.
	T_ASACE		ryEntry[0];		///< The entry array.
} T_ASACL, *PT_ASACL, **PPT_ASACL;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// For debug messsage.

#include <linux/printk.h>

#define DEBUG_PRINTF(fmt, ...)  printk(KERN_DEBUG "## ASACL ## - %s(%d):" fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define ERROR_PRINTF(fmt, ...)  printk(KERN_ERR "## ASACL ## - %s(%d):" fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)


static inline PT_ASACL Asacl_Dup(PT_ASACL ptasAcl)
{
	return ptasAcl;
}

static inline void Asacl_Release(PT_ASACL ptasAcl)
{
}

#ifdef CONFIG_FS_ASACL

extern PT_ASACL Get_Cached_Asacl(struct inode *ptInode);

extern PT_ASACL Get_Cached_Asacl_RCU(struct inode *ptInode);

extern void Set_Cached_Asacl(struct inode *ptInode, PT_ASACL ptasAcl);

extern void Forget_Cached_Asacl(struct inode *ptInode);

#endif /* CONFIG_FS_ASACL */

extern int Alloc_Asacl_Obj(int cnEntry, PPT_ASACL pptaclBuf);

extern PT_ASACL Get_Asacl(struct inode *ptInode);

extern int Check_Asacl_Permission(struct user_namespace *ptMntUsrNs, struct inode *ptInode,
									const PT_ASACL ptasAcl, uint16_t mMask);

extern int Set_File_Mode_After_Updating_Asacl(const PT_ASACL ptasAcl, struct inode *ptInode);

extern int Create_Asacl_For_New_File(struct inode *ptParentInode, struct inode *ptInode, PPT_ASACL pptasAcl);

extern int Estimate_New_File_Asacl_Xattr_Size(umode_t mMode, PT_ASACL ptaclParent);

extern int Check_Asacl(struct user_namespace *ptMntUsrNs, struct inode *ptInode, int mWant);

extern int Check_Asacl_Without_RCU(struct user_namespace *ptMntUsrNs, struct inode *ptInode, int mAsaclMask);

extern int Asacl_Chown(struct inode *ptInode, int bOwnerIsGroup);

extern int Asacl_Chmod(struct inode *ptInode);

extern void Init_Admin_Priv_Procfs(void);

extern int If_Have_Admin_Privilege(void);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Xattr related APIs.

typedef struct _t_xattr_asace_
{
	unsigned char	iTypeAlias;		///< The alias for the member of "T_ACE_TYPE" type.
	unsigned char	mFlags;			///< ASACE flags. Check 'FLAG_ASACE_XXX' for more detail.
	__le16			mPerm;			///< The permission mask.
	__le32			iNumAlias;		///< The alias for the member of "T_ACE_NUM" type.
} T_XATTR_ASACE, *PT_XATTR_ASACE;

typedef struct _t_xattr_asacl_
{
	char			iRevision;		///< Revision number.
	unsigned char	mPreserve1;		///< The preserved bits. It is meaningless in the present.
	__le16			cnEntry;		///< The number of entries.
	__le16			mFlags;			///< ASACL flags. Check 'FLAG_ASACL_XXX' for more detail.
	__le16			mPreserve2;		///< The preserved bits. It is meaningless in the present.
} T_XATTR_ASACL, *PT_XATTR_ASACL;

extern const struct xattr_handler  Asacl_Xattr_Handler;

extern size_t Get_Asacl_Xattr_Size(int cnEntry);

extern int Xattr_To_Asacl(const void *pstXattr, size_t cbSizeXattr, PPT_ASACL pptaclBuf);

extern int Asacl_To_Xattr(const PT_ASACL ptasAcl, size_t *pcbXattrBuf, void *pstXattr);

#endif /* _ASUSTOR_ACL_INC_ */
