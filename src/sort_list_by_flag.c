#include "../inc/uls.h"

static bool cmp_name(t_directory *f1, t_directory *f2)
{
    return (mx_strcmp(f1->name, f2->name) > 0);
}

static bool cmp_size(t_directory *f1, t_directory *f2)
{
    if (f1->stat.st_size == f2->stat.st_size)
        return cmp_name(f1, f2);
    return (f1->stat.st_size < f2->stat.st_size);
}

static bool cmp_mtime(t_directory *f1, t_directory *f2)
{
    if (f1->stat.st_mtime == f2->stat.st_mtime)
        return cmp_name(f1, f2);
    return (f1->stat.st_mtime < f2->stat.st_mtime);
}

static bool cmp_atime(t_directory *f1, t_directory *f2)
{
    if (f1->stat.st_atime == f2->stat.st_atime)
        return cmp_name(f1, f2);
    return (f1->stat.st_atime < f2->stat.st_atime);
}

static bool cmp_ctime(t_directory *f1, t_directory *f2)
{
    if (f1->stat.st_ctime == f2->stat.st_ctime)
        return cmp_name(f1, f2);
    return (f1->stat.st_ctime < f2->stat.st_ctime);
}

void sort_list_by_flag(t_directory **head, const t_flags *flags)
{

    if (flags->S) list_sort(head, cmp_size);
    else if (flags->t && !flags->u && !flags->c) list_sort(head, cmp_mtime);
    else if (flags->u && flags->t && !flags->S) list_sort(head, cmp_atime);
    else if (flags->c && flags->t && !flags->S) list_sort(head, cmp_ctime);
    else if (!flags->t && !flags->S) list_sort(head, cmp_name);

    if (flags->r) list_sort_reverse(head);
}
