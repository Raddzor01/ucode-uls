#include "../inc/uls.h"

char **get_arg_files(int argc, char **argv, int i)
{
    char **files;
    int j;

    if ((argc - i) == 0)
    {
        char **files = malloc(sizeof(char *) * 2);

        files[0] = mx_strdup(".");
        files[1] = NULL;

        return files;
    }

    files = malloc((argc - i + 1) * sizeof(char *));
    for (j = 0; i < argc; j++, i++)
    {
        files[j] = mx_strdup(argv[i]);
    }
    files[j] = NULL;

    return files;
}

t_directory *get_dir_files(char **files, int *i)
{
    t_directory *head = NULL;

    for (int j = 0; files[j] != NULL; ++j)
    {
        struct stat st;
        if (stat(files[j], &st) != 0)
        {
            mx_printerr(strerror(errno));
            continue;
        }

        // check arg file for not directory type
        if (!S_ISDIR(st.st_mode))
        {
            ++(*i);
            list_push_back(&head, ".", files[j]);
        }
    }

    return head;
}

t_directory *get_dirs(char **files)
{
    t_directory *head = NULL;

    for (int i = 0; files[i] != NULL; ++i)
    {
        struct stat st;
        if (stat(files[i], &st) != 0)
        {
            mx_printerr(strerror(errno));
            continue;
        }

        // check arg file for directory type
        if (S_ISDIR(st.st_mode))
        {
            list_push_back(&head, NULL, files[i]);
        }
    }
    
    return head;
}
