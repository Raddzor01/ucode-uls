#include "../inc/uls.h"

static void print_acl_params(char **acl_pr, int i)
{
    mx_printchar(' ');
    mx_printint(i - 1);
    mx_printstr(": ");
    mx_printstr(acl_pr[0]);
    mx_printchar(':');
    mx_printstr(acl_pr[2]);
    mx_printchar(' ');
    mx_printstr(acl_pr[4]);
    mx_printchar(' ');
    mx_printstr(acl_pr[5]);
    mx_printchar('\n');
}

// -e flag, macos only
void print_acl_info(char *acl_str)
{
    char **acl_strarr = mx_strsplit(acl_str, '\n');
    for (int i = 1; acl_strarr[i] != NULL; i++)
    {
        char **acl_pr = mx_strsplit(acl_strarr[i], ':');
        print_acl_params(acl_pr, i);
        mx_del_strarr(&acl_pr);
    }
    mx_del_strarr(&acl_strarr);
}
