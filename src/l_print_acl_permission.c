#include "../inc/uls.h"

// get additional permisions(macos only)
void print_acl_permission(char *file_path, char **acl_str, bool e_flag, bool is_link)
{
    char add_perm = ' ';
    char attribute_name[XATTR_LEN];
    ssize_t buffer_len = listxattr(file_path, attribute_name, XATTR_LEN, XATTR_NOFOLLOW);
    acl_t acl_info = acl_get_file(file_path, ACL_TYPE_EXTENDED);

    if (buffer_len > 0)
        add_perm = '@';
    else if (acl_info != NULL && !is_link)
    {
        acl_free(acl_info);
        add_perm = '+';
    }
    if (e_flag)
        *acl_str = acl_to_text(acl_info, NULL);

    mx_printchar(add_perm);
    mx_printchar(' ');
}

