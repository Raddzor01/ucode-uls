#include "../inc/uls.h"

bool compare_by_name(t_directory *f1, t_directory *f2)
{
    return (mx_strcmp(f1->name, f2->name) > 0);
}

bool compare_by_mtime(t_directory *f1, t_directory *f2)
{
    if (f1->stat.st_mtime == f2->stat.st_mtime)
        return compare_by_name(f1, f2);
    return (f1->stat.st_mtime < f2->stat.st_mtime);
}

bool compare_by_atime(t_directory *f1, t_directory *f2)
{
    if (f1->stat.st_atime == f2->stat.st_atime)
        return compare_by_name(f1, f2);
    return (f1->stat.st_atime < f2->stat.st_atime);
}

bool compare_by_ctime(t_directory *f1, t_directory *f2)
{
    if (f1->stat.st_ctime == f2->stat.st_ctime)
        return compare_by_name(f1, f2);
    return (f1->stat.st_ctime < f2->stat.st_ctime);
}

bool compare_by_size(t_directory *f1, t_directory *f2)
{
    if (f1->stat.st_size == f2->stat.st_size)
        return compare_by_name(f1, f2);
    return (f1->stat.st_size < f2->stat.st_size);
}

void mx_reverse_list(t_directory **list)
{
    t_directory *previous = NULL;
    t_directory *current = *list;
    while (current)
    {
        t_directory *next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    *list = previous;
}

void mx_sort_list(t_directory **list, bool (*cmp)(t_directory *a, t_directory *b))
{
    int count = list_size(*list);
    t_directory **curr = list;
    bool is_swapped;

    for (int i = 0; i < count; i++)
    {
        t_directory **prev = curr;
        t_directory *temp;
        is_swapped = false;

        while ((*prev)->next != NULL)
        {
            if (cmp(*prev, (*prev)->next))
            {
                temp = (*prev)->next;
                (*prev)->next = temp->next;
                temp->next = *prev;
                *prev = temp;
                is_swapped = true;
            }
            prev = &(*prev)->next;
        }

        if (!is_swapped)
            break;
    }
}

void sort_list_by_flag(t_directory **head, t_flags *flags)
{
    if (flags->f) return;

    if (flags->S)
        mx_sort_list(head, compare_by_size);
    else if (flags->t && !flags->u && !flags->c)
        mx_sort_list(head, compare_by_mtime);
    else if (flags->u && flags->t && !flags->S)
        mx_sort_list(head, compare_by_atime);
    else if (flags->c && flags->t && !flags->S)
        mx_sort_list(head, compare_by_ctime);
    else if (!flags->t && !flags->S)
        mx_sort_list(head, compare_by_name);

    if (flags->r)
        mx_reverse_list(head);
}
