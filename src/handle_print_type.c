#include "../inc/uls.h"

void handle_print_type(bool is_file, t_directory **files, const t_flags *flags)
{
    if (!flags->f)
        sort_list_by_flag(files, flags);

    if (flags->l)
        print_l_flag(files, flags, is_file);
    else if (flags->m)
        print_m_flag(files, flags);
    else
        print_default(files, flags);
}
