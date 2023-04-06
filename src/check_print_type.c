#include "../inc/uls.h"

void check_name_printtype(const t_directory *file, const t_flags *flags)
{
    if (flags->G && isatty(1))
        print_G_flag(file->name, file->stat.st_mode);
    else
        mx_printstr(file->name);

    if (flags->F)
        print_classificator(file->stat.st_mode);
    else if (flags->p)
        print_dir_classificator(file->stat.st_mode);
}


