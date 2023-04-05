#include "../inc/uls.h"

bool uls(int argc, char **argv, t_flags *flags, int i)
{
    char **arg_files = NULL;
    t_directory *head;
    bool not_single = false;
    int file_count = argc - i;
    bool error = false;

    arg_files = get_arg_files(argc, argv, i);

    if (flags->r)
        mx_bubble_sort(arg_files, file_count, true);
    else
        mx_bubble_sort(arg_files, file_count, false);

    head = get_dir_files(arg_files, &i, &error);
    if (head != NULL)
    {
        handle_print_type(true, &head, flags);
        not_single = true;

        for (int j = 0; arg_files[j] != NULL; ++j)
        {
            struct stat st;
            if (stat(arg_files[j], &st) == 0)
            {
                if (S_ISDIR(st.st_mode))
                {
                    mx_printstr("\n");
                    break;
                }
            }
        }
    }

    list_free(&head);

    if (flags->r)
        mx_bubble_sort(arg_files, file_count, true);

    head = get_dirs(arg_files);
    sort_list_by_flag(&head, flags);

    int dir_count = argc - i;

    if(print_directories(&head, flags, not_single, dir_count) == 1)
        error = true;

    mx_del_strarr(&arg_files);
    return error;
}
