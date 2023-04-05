#include "../inc/uls.h"

void print_human_size(off_t size, int size_width)
{
    const char *suffixes[] = {"B", "K", "M", "G", "T", "P"};
    double size_f = size;
    int suffix = 0;
    while (size_f >= 1000)
    {
        size_f /= 1024;
        suffix++;
    }

    double size_r = mx_round(size_f * 10) / 10;
    char buff[5] = {'\0'};
    if (size_r >= 10 || suffix == 0)
    {
        char *str = mx_ltoa(mx_round(size_f));
        mx_strcat(buff, str);
        mx_strdel(&str);
    }
    else
    {
        char *str = mx_ltoa(size_r);
        mx_strcat(buff, str);
        mx_strdel(&str);
        mx_strcat(buff, ".");
        str = mx_ltoa((long long)(size_r * 10) % 10);
        mx_strcat(buff, str);
        mx_strdel(&str);
    }
    mx_strcat(buff, suffixes[suffix]);
    print_aligned_str(buff, size_width, true);
}

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
