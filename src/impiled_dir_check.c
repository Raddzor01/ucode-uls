#include "../inc/uls.h"

bool impiled_dir_check(const char *dir_name)
{
    return (!mx_strcmp(dir_name, ".") || !mx_strcmp(dir_name, ".."));
}
