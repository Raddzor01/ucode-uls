#include "../inc/uls.h"

void print_links(nlink_t links, int links_length)
{
    char *links_str = mx_ltoa(links);
    print_aligned_str(links_str, links_length, true);
    mx_printchar(' ');
    mx_strdel(&links_str);
}
