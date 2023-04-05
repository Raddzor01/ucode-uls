#include "../inc/uls.h"

t_col_width columns_width(t_directory **files, t_flags *flags)
{
    t_col_width cols_width;
    cols_width.group_length = 0;
    cols_width.links_length = 0;
    cols_width.size_length = 0;
    cols_width.user_length = 0;

    t_directory *file = *files;
    while (file)
    {
        char *links = mx_ltoa(file->stat.st_nlink);
        if (cols_width.links_length < mx_strlen(links))
            cols_width.links_length = mx_strlen(links);
        mx_strdel(&links);

        struct passwd *pwd = getpwuid(file->stat.st_uid);
        char *pdw_str = NULL;
        if (flags->n)
            pdw_str = mx_itoa(pwd->pw_uid);
        else
            pdw_str = pwd ? mx_strdup(pwd->pw_name) : mx_strdup("unknown");
        if (cols_width.user_length < mx_strlen(pdw_str))
            cols_width.user_length = mx_strlen(pdw_str);
        mx_strdel(&pdw_str);

        struct group *grp = getgrgid(file->stat.st_gid);
        char *grp_str = NULL;
        if (flags->n)
            grp_str = mx_itoa(grp->gr_gid);
        else
            grp_str = grp ? mx_strdup(grp->gr_name) : mx_strdup("unknown");
        if (cols_width.group_length < mx_strlen(grp_str))
            cols_width.group_length = mx_strlen(grp_str);
        mx_strdel(&grp_str);

        int size_len = 5;
        if (S_ISCHR(file->stat.st_mode) || S_ISBLK(file->stat.st_mode))
        {
            char *wsize = mx_nbr_to_hex(file->stat.st_rdev);
            size_len = mx_strlen(wsize) + 2;
            mx_strdel(&wsize);
        }
        else if (!flags->h)
        {
            char *wsize = mx_ltoa(file->stat.st_size);
            size_len = mx_strlen(wsize);
            mx_strdel(&wsize);
        }
        if (cols_width.size_length < size_len)
            cols_width.size_length = size_len;

        file = file->next;
    }
    return cols_width;
}

