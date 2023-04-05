#include "../inc/uls.h"

bool print_directory(t_directory *dir_entity, t_flags *flags, bool not_single)
{
    DIR *dir;
    struct dirent *entry;
    t_directory *inner_files = NULL;

    dir = opendir(dir_entity->path);
    if (dir == NULL)
    {
        errors_check(not_single, dir_entity, flags->l);
        return true;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if ((!flags->a && !flags->A && ((entry->d_name[0] == '.') || impiled_dir_check(entry->d_name))) // without -aA flags check
            || (flags->A && impiled_dir_check(entry->d_name))                                           // -A flag check
            || uls_file_check(entry->d_name, dir_entity->name))                                         // check if uls file in dir
            continue;
        list_push_back(&inner_files, dir_entity->path, entry->d_name);
    }
    closedir(dir);

    if (not_single)
    {
        mx_printstr(dir_entity->path);
        mx_printstr(":\n");
    }

    handle_print_type(false, &inner_files, flags);

    if (flags->R)
    {
        t_directory *current_file = inner_files;
        while (current_file)
        {
            if ((S_ISDIR(current_file->stat.st_mode))
            && !impiled_dir_check(current_file->name))
            {
                mx_printchar('\n');
                print_directory(current_file, flags, true);
            }
            current_file = current_file->next;
        }
    }

    list_free(&inner_files);

    return false;
}

bool print_directories(t_directory **head, t_flags *flags, bool not_single, int dir_count)
{
    bool error = false;
    int dir_idx = 0;
    t_directory *dir = *head;

    while (dir)
    {
        if (dir_idx && dir_count > 1)
            mx_printstr("\n");
        bool is_single = dir_count <= 1 && !not_single;
        error = print_directory(dir, flags, !is_single);

        dir = dir->next;
        dir_idx++;
    }

    list_free(head);
    return error;
}
