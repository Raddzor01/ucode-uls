#include "../inc/uls.h"

t_directory *get_file_at_index(t_directory *file, int index)
{
    int i = 0;
    while (file != NULL)
    {
        if (i == index)
            return file;
        file = file->next;
        ++i;
    }
    return NULL;
}

int get_max_name_length(t_directory **files)
{
    int max_len = 0;
    t_directory *file = *files;
    while (file != NULL)
    {
        int len = mx_strlen(file->name);
        if (len > max_len)
            max_len = len;
        file = file->next;
    }
    return max_len;
}

int calc_col_width(t_directory **files)
{
    int col_width = get_max_name_length(files);
    return (col_width % TAB_SIZE == 0) ? col_width + TAB_SIZE : col_width + TAB_SIZE - (col_width % TAB_SIZE);
}

int calc_num_tabs(int col_width, int name_len)
{
    int difference = col_width - name_len;
    return (difference % TAB_SIZE != 0) ? difference / TAB_SIZE + 1 : difference / TAB_SIZE;
}

void print_tabs(int num_tabs)
{
    int i;
    for (i = 0; i < num_tabs; i++)
        mx_printchar('\t');
}

int calc_cols(int win_cols, int col_width)
{
    int cols = (win_cols / col_width == 0) ? 1 : win_cols / col_width;
    return (col_width * cols > win_cols && cols != 1) ? cols - 1 : cols;
}

int calc_rows(int cols, int num_names)
{
    return (num_names % cols != 0) ? num_names / cols + 1 : num_names / cols;
}

void print_rows(t_directory **files, int col_width, int rows, int num_names, t_flags *flags)
{
    int i, j;
    t_directory *file;
    for (i = 0; i < rows; i++)
    {
        for (j = i; j < num_names; j += rows)
        {
            file = get_file_at_index(*files, j);
            if (flags->G && isatty(1))
                print_G_flag(file->name, file->stat.st_mode);
            else
                mx_printstr(file->name);
            if (file->next && (j + rows < num_names))
                print_tabs(calc_num_tabs(col_width, mx_strlen(file->name)));
        }
        mx_printchar('\n');
    }
}

void print_single_row(t_directory **files, int col_width, t_flags *flags)
{
    t_directory *file = *files;
    while (file != NULL)
    {
        if (flags->G && isatty(1))
            print_G_flag(file->name, file->stat.st_mode);
        else
            mx_printstr(file->name);
        if (file->next)
            print_tabs(calc_num_tabs(col_width, mx_strlen(file->name)));
        file = file->next;
    }
    mx_printchar('\n');
}

void print_file_names(t_directory **files, int col_width, int win_cols, t_flags *flags)
{
    int num_names = list_size(*files);
    if (num_names == 0)
        return;
    int cols = calc_cols(win_cols, col_width);
    int rows = calc_rows(cols, num_names);
    if (rows == 1)
        print_single_row(files, col_width, flags);
    else
        print_rows(files, col_width, rows, num_names, flags);
}

void mx_output_default(t_directory **files, t_flags *flags)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int win_cols = w.ws_col;

    int col_width = calc_col_width(files);
    if ((!isatty(1) || flags->file_per_line) && !flags->C)
        print_file_names(files, col_width, get_max_name_length(files), flags);
    else if (isatty(1) && !flags->file_per_line && !flags->C)
        print_file_names(files, col_width, win_cols, flags);
    else
        print_file_names(files, col_width, 80, flags);
}
