#include "../inc/uls.h"

static void set_col_width(int *dest, int src)
{
    if (*dest < src)
        *dest = src;
}

static t_col_width cols_width_init()
{
    t_col_width cols_width;
    cols_width.group_length = 0;
    cols_width.links_length = 0;
    cols_width.size_length = 0;
    cols_width.user_length = 0;
    return cols_width;
}

t_col_width columns_width(t_directory **files, bool n_flag, bool h_flag)
{
    t_col_width cols_width = cols_width_init();
    struct passwd *pwd;
    struct group *grp;
    char *pdw_str = NULL;
    char *grp_str = NULL;
    char *links = NULL;
    char *wsize = NULL;

    t_directory *file = *files;
    while (file)
    {
        links = mx_ltoa(file->stat.st_nlink);
        set_col_width(&cols_width.links_length, mx_strlen(links));
        mx_strdel(&links);

        pwd = getpwuid(file->stat.st_uid);
        grp = getgrgid(file->stat.st_gid);

        if (n_flag)
        {
            pdw_str = mx_itoa(pwd->pw_uid);
            grp_str = mx_itoa(grp->gr_gid);
        }
        else
        {
            pdw_str = pwd ? mx_strdup(pwd->pw_name) : mx_ltoa(file->stat.st_uid);
            grp_str = grp ? mx_strdup(grp->gr_name) : mx_ltoa(file->stat.st_gid);
        }

        set_col_width(&cols_width.user_length, mx_strlen(pdw_str));
        set_col_width(&cols_width.group_length, mx_strlen(grp_str));

        mx_strdel(&pdw_str);
        mx_strdel(&grp_str);
        
        int size_len = 5;
        if (S_ISCHR(file->stat.st_mode) || S_ISBLK(file->stat.st_mode))
        {
            wsize = mx_nbr_to_hex(file->stat.st_rdev);
            size_len = mx_strlen(wsize) + 2;
        }
        else if (!h_flag)
        {
            wsize = mx_ltoa(file->stat.st_size);
            size_len = mx_strlen(wsize);
        }
        set_col_width(&cols_width.size_length, size_len);
        mx_strdel(&wsize);

        file = file->next;
    }
    return cols_width;
}

