#include "../inc/uls.h"

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
