#include "../inc/uls.h"

void print_linked_file(const char *path)
{
    char *linked_file = mx_strnew(PATH_MAX);
    int bytes = readlink(path, linked_file, PATH_MAX);
    if (bytes == -1)
    {
        mx_strdel(&linked_file);
        return;
    }
    linked_file[bytes] = '\0';
    mx_printstr(" -> ");
    mx_printstr(linked_file);
    mx_strdel(&linked_file);
}
