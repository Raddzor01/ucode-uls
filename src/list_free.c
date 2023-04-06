#include "../inc/uls.h"

void list_free(t_directory **head)
{
    t_directory *current = *head;
    t_directory *next;

    while (current)
    {
        next = current->next;
        mx_strdel(&current->name);
        mx_strdel(&current->path);
        free(current);
        current = next;
    }

    *head = NULL;
}
