#include "../inc/uls.h"

void print_G_flag(char* file_name, mode_t st_mode)
{
    mode_t mode = st_mode & S_IFMT;

    if (mode == S_IFDIR)
        if (S_ISVTX & mode && mode & S_IWOTH)
            mx_printstr("\033[42;30m");
        else if (!(S_ISVTX & mode) && mode & S_IWOTH)
            mx_printstr("\033[43;30m");
        else
            mx_printstr("\033[0;34m");
    else if (mode == S_IFLNK)
        mx_printstr("\033[0;35m");
    else if (mode == S_IFSOCK)
        mx_printstr("\033[0;32m");
    else if (mode == S_IFIFO)
        mx_printstr("\033[0;33m");
    else if (IS_X(mode) && IS_R(mode))
        if (S_ISUID & mode)
            mx_printstr("\033[41;30m");
        else if (S_ISGID & mode)
            mx_printstr("\033[46;30m");
        else 
            mx_printstr("\033[0;31m");
    else if (mode == S_IFBLK)
        mx_printstr("\033[46;34m");
    else if (mode == S_IFCHR)
        mx_printstr("\033[43;34m");
    mx_printstr(file_name);
    mx_printstr("\033[0m");
}
