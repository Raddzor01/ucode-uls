#include "../inc/uls.h"

static void print_filetype(mode_t permissions)
{
    switch (permissions & S_IFMT)
    {
    case S_IFDIR:
        mx_printchar('d');
        break;
    case S_IFLNK:
        mx_printchar('l');
        break;
    case S_IFIFO:
        mx_printchar('p');
        break;
    case S_IFSOCK:
        mx_printchar('s');
        break;
    case S_IFBLK:
        mx_printchar('b');
        break;
    case S_IFCHR:
        mx_printchar('c');
        break;
    case S_IFREG:
        mx_printchar('-');
        break;
    default:
        mx_printchar('?');
        break;
    }
}

void print_permissions(mode_t mode)
{
    print_filetype(mode);
    char permissions[] = "---------";
    if (mode & S_IRUSR) permissions[0] = 'r';
    if (mode & S_IWUSR) permissions[1] = 'w';
    if (mode & S_IXUSR)
    {
        if (mode & S_ISUID) permissions[2] = 's';
        else permissions[2] = 'x';
    }
    else if (mode & S_ISUID) permissions[2] = 'S';
    if (mode & S_IRGRP) permissions[3] = 'r';
    if (mode & S_IWGRP) permissions[4] = 'w';
    if (mode & S_IXGRP)
    {
        if (mode & S_ISGID) permissions[5] = 's';
        else permissions[5] = 'x';
    }
    else if (mode & S_ISGID) permissions[5] = 'S';
    if (mode & S_IROTH) permissions[6] = 'r';
    if (mode & S_IWOTH) permissions[7] = 'w';
    if (mode & S_IXOTH)
    {
        if (mode & S_ISTXT) permissions[8] = 't';
        else 
            permissions[8] = 'x';
    }
    else if (mode & S_ISTXT) permissions[8] = 'T';
    mx_printstr(permissions);
}
