#include "../inc/uls.h"

void list_sort_reverse(t_directory **list)
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
