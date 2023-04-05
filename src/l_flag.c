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

static void print_links(nlink_t links, int links_length)
{
    char *links_str = mx_ltoa(links);
    print_aligned_str(links_str, links_length, true);
    mx_printchar(' ');
    mx_strdel(&links_str);
}

static void print_time(struct stat st, t_flags *flags)
{
    time_t current_time = time(NULL);

    time_t time;
    if (flags->c)
        time = st.st_ctime;
    else if (flags->u)
        time = st.st_atime;
    else
        time = st.st_mtime;

    char *time_str = ctime(&time);
    char **full_date = mx_strsplit(time_str, ' ');
    full_date[4][4] = '\0';

    mx_printstr(full_date[1]);
    mx_printchar(' ');
    print_aligned_str(full_date[2], 2, true);
    mx_printchar(' ');

    if (flags->T)
        write(1, &time_str[11], 13);
    else if ((current_time - time) > 15552000 || ((current_time - time) < 0 && (current_time - time) > -15552000))
    {
        mx_printchar(' ');
        write(1, full_date[4], 4);
    }
    else
        write(1, full_date[3], 5);
    mx_printchar(' ');

    mx_del_strarr(&full_date);
}

static void print_row(const t_directory *dir, t_flags *flags, t_col_width columns_width)
{
    char *acl_str = NULL;
    print_permissions(dir->stat.st_mode);
    // get additional permisions(macos only)
    print_acl_permission(dir->path, &acl_str, flags->e, S_ISLNK(dir->stat.st_mode));

    print_links(dir->stat.st_nlink, columns_width.links_length);
    print_pwd_grp(dir->stat, columns_width.user_length, columns_width.group_length, flags);
    print_size(dir->stat, flags->h ? true : false, columns_width.size_length);

    print_time(dir->stat, flags);

    check_name_printtype(dir, flags);

    print_linked_file(dir->path);

    mx_printchar('\n');

    // -@e flags, macos only
    if (flags->extended_attr && listxattr(dir->path, NULL, 0, XATTR_NOFOLLOW) > 0)
        print_file_xattrs(dir->path, flags->h);

    if (acl_str)
        print_acl_info(acl_str);
}

void print_l_flag(t_directory **dir, t_flags *flags, bool is_file)
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
        print_row(head, flags, columns_width(dir, flags));
        head = head->next;
    }
}
