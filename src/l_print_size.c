#include "../inc/uls.h"

void print_size(struct stat st, bool h_flag, int size_width)
{
    if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode))
    {
        char *hex = mx_nbr_to_hex(st.st_rdev);
        char *hex_str = NULL;
        if (st.st_rdev == 0)
            hex_str = mx_strdup("0");
        else
            hex_str = mx_strjoin("0x", hex);
        print_aligned_str(hex_str, size_width, true);
        mx_strdel(&hex_str);
        mx_strdel(&hex);
    }
    else if (h_flag)
        print_human_size(st.st_size, size_width);
    else
    {
        char *size_str = mx_ltoa(st.st_size);
        print_aligned_str(size_str, size_width, true);
        mx_strdel(&size_str);
    }
    mx_printchar(' ');
}
