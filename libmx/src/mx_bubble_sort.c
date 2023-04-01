#include "libmx.h"

int mx_bubble_sort(char **arr, int size, bool reverse)
{
    int count = 0;
    char *temp_str;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (reverse) {
                if (mx_strcmp(arr[j], arr[j + 1]) < 0)
                {
                    temp_str = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp_str;
                    count++;
                }
            } else {
                if (mx_strcmp(arr[j], arr[j + 1]) > 0)
                {
                    temp_str = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp_str;
                    count++;
                }                
            }
        }
    }
    return count;
}
