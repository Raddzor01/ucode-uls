#include "../inc/uls.h"

static blkcnt_t get_total_blocks(t_directory *files)
{
    blkcnt_t total = 0;
    t_directory *file = files;

    while (file)
    {
        total += file->stat.st_blocks;
        file = file->next;
    }

    return total;
}

static void print_row(const t_directory *dir, const t_flags *flags, t_col_width columns_width)
{
    char *acl_str = NULL;
    print_permissions(dir->stat.st_mode);
    print_acl_permission(dir->path, &acl_str, flags->e, S_ISLNK(dir->stat.st_mode));
    print_links(dir->stat.st_nlink, columns_width.links_length);
    print_pwd_grp(dir->stat, columns_width.user_length, columns_width.group_length, flags);
    print_size(dir->stat, flags->h, columns_width.size_length);
    print_time(dir->stat, flags);

    check_name_printtype(dir, flags);

    print_linked_file(dir->path);

    mx_printchar('\n');

    if (flags->extended_attr && listxattr(dir->path, NULL, 0, XATTR_NOFOLLOW) > 0)
        print_file_xattrs(dir->path, flags->h);

    if (acl_str)
        print_acl_info(acl_str);
}

void print_l_flag(t_directory **dir, const t_flags *flags, bool is_file)
{
    if (!is_file && *dir)
    {
        blkcnt_t total_blocks = get_total_blocks(*dir);
        char *block_str = mx_ltoa(total_blocks);
        mx_printstr("total ");
        mx_printstr(block_str);
        mx_printchar('\n');
        mx_strdel(&block_str);
    }

    t_directory *head = *dir;
    while (head)
    {
        print_row(head, flags, columns_width(dir, flags->n, flags->h));
        head = head->next;
    }
}
