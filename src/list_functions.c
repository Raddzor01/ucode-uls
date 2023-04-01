#include "../inc/uls.h"

void list_push_back(t_directory **list, char *dir_name, char *file_name)
{
    t_directory *new_node = malloc(sizeof(t_directory));
    new_node->name = mx_strdup(file_name);
    char *file_path;

    if (dir_name)
    {
        file_path = mx_strnew(mx_strlen(dir_name) + mx_strlen(file_name) + 1);
        mx_strcpy(file_path, dir_name);
        mx_strcat(file_path, "/");
        mx_strcat(file_path, file_name);
        new_node->path = mx_strdup(file_path);
        mx_strdel(&file_path);
    }
    else
        new_node->path = mx_strdup(file_name);

    if (stat(new_node->path, &new_node->stat) == -1)
    {
        mx_printerr("uls: ");
        mx_printerr(new_node->name);
        mx_printerr(": ");
        mx_printerr(strerror(errno));
        mx_printerr("\n");
    }
    new_node->next = NULL;

    t_directory *head = *list;

    if (*list == NULL)
    {
        *list = new_node;
        return;
    }

    while (head->next != NULL)
        head = head->next;

    head->next = new_node;
}

int list_size(t_directory *list)
{
    t_directory *node = list;
    int size = 0;

    while (node != NULL)
    {
        node = node->next;
        size++;
    }

    return size;
}

void list_free(t_directory **head)
{
    t_directory *current = *head;
    t_directory *next;

    while (current)
    {
        next = current->next;
        mx_strdel(&current->name);
        mx_strdel(&current->path);
        free(current);
        current = next;
    }

    *head = NULL;
}
