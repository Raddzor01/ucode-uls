#include "../inc/uls.h"

void print_errors(t_directory *dir, const bool l_flag)
{
    if (l_flag)
    {
        mx_printstr("total ");
        mx_printint(0);
        mx_printchar('\n');
    }
    if (errno == EACCES)
    {
        mx_printerr("uls: ");
        if (dir->name)
            mx_printerr(dir->name);
        else
            mx_printerr(dir->path);
        mx_printerr(": ");
        mx_printerr(strerror(errno));
        mx_printerr("\n");
        return;
    }
    mx_printerr("uls: ");
    mx_printerr(dir->path);
    mx_printerr(": ");
    mx_printerr(strerror(errno));
    mx_printerr("\n");
}
