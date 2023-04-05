#include "../inc/uls.h"

static int term_width()
{
    struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);
    return ws.ws_col;
}

void print_m_flag(t_directory **files, t_flags *flags)
{
    int win_cols = isatty(1) ? term_width() : CAT_SIZE;
    t_directory *file = *files;
    for (int i = 0; file;)
    {
        i += file->next == NULL ? mx_strlen(file->name) : mx_strlen(file->name) + 2;
        if (i >= win_cols)
        {
            i = mx_strlen(file->name) + 2;
            mx_printchar('\n');
        }

        check_name_printtype(file, flags);

        if(file->next != NULL)
            mx_printstr(", ");
        else
            mx_printchar('\n');
        file = file->next;
    }
}
