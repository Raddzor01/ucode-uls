#include "../inc/uls.h"

void print_time(struct stat st, const t_flags *flags)
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
