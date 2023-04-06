#include "../inc/uls.h"

void list_sort(t_directory **list, bool (*cmp)(t_directory *f1, t_directory *f2))
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
