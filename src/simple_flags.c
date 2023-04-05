#include "../inc/uls.h"

void print_classificator(mode_t mode)
{
    switch (mode & S_IFMT)
    {
    case S_IFDIR:
        mx_printchar('/');
        break;
    case S_IFIFO:
        mx_printchar('|');
        break;
    case S_IFLNK:
        mx_printchar('@');
        break;
    case S_IFSOCK:
        mx_printchar('=');
        break;
    case S_IFREG:
        if (mode & (S_IXUSR | S_IXGRP | S_IXOTH))
            mx_printchar('*');
        break;
    case S_IFWHT:
        mx_printchar('%');
        break;
    }
}

void print_dir_classificator(mode_t mode)
{
    if((mode & S_IFMT) == S_IFDIR)
        mx_printchar('/');
}
