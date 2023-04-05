#include "../inc/uls.h"

bool impiled_dir_check(const char *dir_name)
{
    return (!mx_strcmp(dir_name, ".") || !mx_strcmp(dir_name, ".."));
}

bool uls_file_check(const char *file, const char *dir)
{
    struct stat uls_st;
    struct stat st;
    bool check = false;

    char *file_path = mx_strnew(mx_strlen(dir) + mx_strlen(file) + 1);
    mx_strcpy(file_path, dir);
    mx_strcat(file_path, "/");
    mx_strcat(file_path, file);

    lstat("uls", &uls_st);
    lstat(file_path, &st);
    
    mx_strdel(&file_path);
    if (st.st_ino == uls_st.st_ino)
        check = true;
    return check;
}

void errors_check(bool not_single, t_directory *dir, bool l_flag)
{
    if (not_single)
    {
        mx_printstr(dir->path);
        mx_printstr(":\n");
    }
    if (l_flag)
    {
        mx_printstr("total ");
        mx_printint(0);
        mx_printchar('\n');
    }
    if (errno == EACCES)
    {
        mx_printerr("uls: ");
        if (dir->name)
            mx_printerr(dir->name);
        else
            mx_printerr(dir->path);
        mx_printerr(": ");
        mx_printerr(strerror(errno));
        mx_printerr("\n");
        return;
    }
    mx_printerr("uls: ");
    mx_printerr(dir->path);
    mx_printerr(": ");
    mx_printerr(strerror(errno));
    mx_printerr("\n");
}
