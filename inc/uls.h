#pragma once

#include "../libmx/inc/libmx.h"
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

#define TAB_SIZE 8
#define CAT_SIZE 80

#define XATTR_LEN 10000
typedef struct s_flags {
    bool a;
    bool A;
    bool G;
    bool l;
    bool r;
    bool t;
    bool c;
    bool u;
    bool S;
    bool T;
    bool h;
    bool extended_attr;
    bool e;
    bool R;
    bool C;
    bool file_per_line;
    bool f;
    bool m;
    bool F;
    bool p;
    bool n;
    bool o;
    bool g;
}   t_flags;

typedef struct s_directory {

    char *name;
    char *path;
    
    struct stat stat;

    struct s_directory *next;
    
}   t_directory;

// for -l flag tabulation
typedef struct s_col_width {
    int links_length;
    int user_length;
    int group_length;
    int size_length;
}   t_col_width;

bool uls(int argc, char **argv, const t_flags *flags, int i);

int get_flags(char *argv[], t_flags **flags);
char **get_arg_files(int argc, char **argv, int i);
t_directory *get_dir_files(char **files, int *i, bool *error);
t_directory *get_dirs(char **files);

void list_push_back(t_directory **list, char *dir_name, char *file_name);
int list_size(t_directory *list);
void list_free(t_directory **list);
void sort_list_by_flag(t_directory **head, const t_flags *flags);
void list_sort(t_directory **list, bool (*cmp)(t_directory *f1, t_directory *f2));
void list_sort_reverse(t_directory **list);

void handle_print_type(bool is_file, t_directory **files, const t_flags *flags);
void print_files(char **files, const t_flags *flags, int *i);
bool print_directories(t_directory **head, const t_flags *flags, bool not_single, int dir_count);
void print_default(t_directory **files, const t_flags *flags);
void print_l_flag(t_directory **dir, const t_flags *flags, bool is_file);
void print_G_flag(char* file_name, mode_t st_mode);
void print_m_flag(t_directory **files, const t_flags *flags);

void check_name_printtype(const t_directory *file, const t_flags *flags);
void print_aligned_str(const char *str, int width, bool from_right);
void print_classificator(mode_t mode);
void print_dir_classificator(mode_t mode);

bool impiled_dir_check(const char *dir_name);
bool uls_file_check(const char *file, const char *dir);
void print_errors(t_directory *dir, bool l_flag);

t_col_width columns_width(t_directory **files, bool n_flag, bool h_flag);
void print_permissions(mode_t mode);
void print_acl_permission(char *file_path, char **acl_str, bool e_flag, bool is_link);
void print_links(nlink_t links, int links_length);
void print_pwd_grp(struct stat st, int username_width, int group_width, const t_flags *flags);
void print_size(struct stat st, bool h_flag, int size_width);
void print_human_size(off_t size, int size_width);
void print_time(struct stat st, const t_flags *flags);
void print_linked_file(const char *path);
void print_file_xattrs(const char *path, bool h_flag);
void print_acl_info(char *acl_str);
