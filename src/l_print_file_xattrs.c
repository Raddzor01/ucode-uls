#include "../inc/uls.h"

// @ flag, macos only
void print_file_xattrs(const char *path, bool h_flag)
{
    char attr_name[XATTR_LEN];
    char value[XATTR_LEN];
    int list_len = listxattr(path, attr_name, XATTR_LEN, XATTR_NOFOLLOW);
    int value_len = 0;
    for (int i = 0; i < list_len; i += mx_strlen(&attr_name[i]) + 1)
    {
        mx_printchar('\t');
        mx_printstr(&attr_name[i]);
        value_len = getxattr(path, &attr_name[i], value, XATTR_LEN, 0, 0);
        mx_printstr("\t   ");
        if (h_flag)
            print_human_size(value_len, 2);
        else if (value_len != -1)
            mx_printint(value_len);
        else
            mx_printint(0);

        mx_printstr(" \n");
    }
}
