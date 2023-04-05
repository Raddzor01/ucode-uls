#include "../inc/uls.h"

void print_aligned_str(const char *str, int width, bool from_right)
{
    int spaces = width - mx_strlen(str);

    if (!from_right)
        mx_printstr(str);

    for (int i = 0; i < spaces; i++)
        mx_printchar(' ');

    if (from_right)
        mx_printstr(str);
}
