#include "../inc/uls.h"

bool mx_is_implied_dir(const char *dir_name)
{
    return (!mx_strcmp(dir_name, ".") || !mx_strcmp(dir_name, ".."));
}

bool mx_is_hidden_file(const char *name)
{
    return (name[0] == '.');
}

bool mx_a_flags_applied(t_flags *flags, char *file_name)
{
    if (!flags->a && !flags->A && (mx_is_hidden_file(file_name) || mx_is_implied_dir(file_name)))
        return false;

    if (flags->A && (mx_is_implied_dir(file_name)))
        return false;
    return true;
}

void mx_print_names(t_directory *list)
{
    while (list)
    {
        mx_printstr(list->name);
        mx_printchar('\n');
        list = list->next;
    }
}

bool print_directory(t_directory *dir_entity, t_flags *flags, bool not_single)
{
    DIR *dir;
    struct dirent *entery;
    t_directory *inner_files = NULL;

    dir = opendir(dir_entity->path);
    if (dir == NULL)
    {
        if (errno == EACCES)
        {
            if (not_single)
            {
                mx_printstr(dir_entity->name);
                mx_printstr(":\n");
            }
            mx_printerr("uls: ");
            mx_printerr(dir_entity->name);
            mx_printerr(strerror(errno));
            mx_printerr("\n");
            return true;
        }
        mx_printerr("uls: ");
        mx_printerr(dir_entity->name);
        mx_printerr(": ");
        mx_printerr(strerror(errno));
        mx_printerr("\n");
        return true;

    }
    while ((entery = readdir(dir)) != NULL)
    {
        if (!mx_a_flags_applied(flags, entery->d_name))
            continue;
        list_push_back(&inner_files, dir_entity->path, entery->d_name);
    }
    closedir(dir);

    if (not_single || (flags->R))
    {
        mx_printstr(dir_entity->path);
        mx_printstr(":");
        mx_printstr("\n");
    }

    sort_list_by_flag(&inner_files, flags);

    if (flags->l)
        print_l_flag(&inner_files, flags, false);
    else
        mx_output_default(&inner_files, flags);

    if (flags->R)
    {
        t_directory *current_file = inner_files;
        while (current_file)
        {
            if ((S_ISDIR(current_file->stat.st_mode)) && !mx_is_implied_dir(current_file->name))
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
