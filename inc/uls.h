#pragma once

#include "../libmx/inc/libmx.h"
#include <dirent.h>
#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <unistd.h>
#include <time.h>
#include <getopt.h>
#include <stdio.h>

#define IS_R(m) (m & S_IRUSR && m & S_IRGRP && m & S_IROTH)
#define IS_X(m) (m & S_IXUSR && m & S_IXGRP && m & S_IXOTH)

#define TAB_SIZE 8
typedef struct s_flags {
    int a;
    int A;
    int G;
    int l;
    int r;
    int t;
    int c;
    int u;
    int S;
    int T;
    int h;
    int extended_attr;
    int e;
    int R;
    int C;
    int file_per_line;
    int f;
}   t_flags;

typedef struct s_directory {

    char *name;
    char *path;
    
    struct stat stat;

    struct s_directory *next;
    
}   t_directory;

int get_flags(char *argv[], t_flags **flags);
bool uls(int argc, char **argv, t_flags *flags, int i);
void print_l_flag(t_directory **dir, t_flags *flags, bool is_file);

char **get_arg_files(int argc, char **argv, int i);
t_directory *get_dir_files(char **files, int *i);
t_directory *get_dirs(char **files);

void list_push_back(t_directory **list, char *dir_name, char *file_name);
int list_size(t_directory *list);
void list_free(t_directory **list);

void print_files(char **files, t_flags *flags, int *i);
void mx_output_default(t_directory **files, t_flags *flags);

bool print_directories(t_directory **head, t_flags *flags, bool not_single, int dir_count);
void sort_list_by_flag(t_directory **head, t_flags *flags);
void print_G_flag(char* file_name, mode_t st_mode);
