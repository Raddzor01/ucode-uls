#include "../inc/uls.h"

void print_G_flag(char* file_name, mode_t st_mode)
{
    mode_t mode = st_mode & S_IFMT;
    switch (mode)
    {
    case S_IFCHR:
        mx_printstr("\033[34;43m");
        break;
    case S_IFDIR:
        if (S_ISVTX & mode && mode & S_IWOTH)
            mx_printstr("\033[30;42m");
        else if (!(S_ISVTX & mode) && mode & S_IWOTH)
            mx_printstr("\033[30;43m");
        else
            mx_printstr("\033[34m");
        break;
    case S_IFBLK:
        mx_printstr("\033[34;46m");
        break;
    case S_IFIFO:
        mx_printstr("\033[33m");
        break;
    case S_IFLNK:
        mx_printstr("\033[35m");
        break;
    case S_IFSOCK:
        mx_printstr("\033[32m");
        break;
#define IS_R(m) (m & S_IRUSR && m & S_IRGRP && m & S_IROTH)
    default:
        if(mode & S_IXUSR
        && mode & S_IXGRP
        && mode & S_IXOTH)
        {
            if (mode & S_ISUID)
                mx_printstr("\033[30;41m");
            else if (mode & S_ISGID)
                mx_printstr("\033[30;46m");
            else 
                mx_printstr("\033[31m");
        }
        break;
    }
    mx_printstr(file_name);
    mx_printstr("\033[0m");
}
