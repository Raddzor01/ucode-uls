#include "../inc/uls.h"

int list_size(t_directory *list)
{
    t_directory *node = list;
    int size = 0;

    while (node != NULL)
    {
        node = node->next;
        size++;
    }

    return size;
}
