#include "../inc/uls.h"

// #define XATTR_SIZE_MAX 10000

off_t mx_get_total_blocks(t_directory **files)
{
    off_t total = 0;
    t_directory *file = *files;

    while (file)
    {
        total += file->stat.st_blocks;
        file = file->next;
    }

    return total;
}

void print_acl_params(char **acl_pr, int i)
{
    mx_printchar(' ');
    mx_printint(i);
    mx_printstr(": ");
    mx_printstr(acl_pr[0]);
    mx_printchar(':');
    mx_printstr(acl_pr[2]);
    mx_printchar(' ');
    mx_printstr(acl_pr[4]);
    mx_printchar(' ');
    mx_printstr(acl_pr[5]);
    mx_printchar('\n');
}

// // @ flag, macos only
// void print_file_xattr(char *path, ssize_t buffer_len, char *attr_name, char *value)
// {
//      int value_len = 0;
//      for (int i = 0; i < buffer_len; i += mx_strlen(&attr_name[i]) + 1)
//      {
//         mx_printstr("\t");
//         mx_printstr(&attr_name[i]);
//         value_len = getxattr(path, &attr_name[i], value, XATTR_SIZE_MAX, 0, 0);
//         mx_printstr("\t   ");
//         if (value_len != -1)
//             mx_printint(value_len);
//          else
//             mx_printint(0);

//         mx_printstr(" \n");
//      }
//  }

// // -e flag, macos only
//  void print_acl_info(char *acl_str)
//  {
//      char **acl_strarr = mx_strsplit(acl_str, '\n');
//      for (int i = 1; acl_strarr[i] != NULL; i++)
//      {
//          char **acl_pr = mx_strsplit(acl_strarr[i], ':');
//          print_acl_params(acl_pr, i - 1);
//          mx_del_strarr(&acl_pr);
//      }
//      mx_del_strarr(&acl_strarr);
//  }

void print_row(const t_directory *dir, t_flags *flags)
{
    char filetype = '?';
    if (S_ISDIR(dir->stat.st_mode))
        filetype = 'd';
    if((dir->stat.st_mode & S_IFMT) == S_IFLNK)
	    filetype = 'l';
    if (S_ISCHR(dir->stat.st_mode))
        filetype = 'c';
    if (S_ISBLK(dir->stat.st_mode))
        filetype = 'b';
    if (S_ISFIFO(dir->stat.st_mode))
        filetype = 'p';
    if (S_ISSOCK(dir->stat.st_mode))
        filetype = 's';
    if (S_ISREG(dir->stat.st_mode))
        filetype = '-';

    char mode[] = "--------- ";
    mode_t st_mode = dir->stat.st_mode;
    if (st_mode & S_IRUSR)
        mode[0] = 'r';
    if (st_mode & S_IWUSR)
        mode[1] = 'w';
    if (st_mode & S_IXUSR)
        mode[2] = 'x';
    if (st_mode & S_IRGRP)
        mode[3] = 'r';
    if (st_mode & S_IWGRP)
        mode[4] = 'w';
    if (st_mode & S_IXGRP)
        mode[5] = 'x';
    if (st_mode & S_IROTH)
        mode[6] = 'r';
    if (st_mode & S_IWOTH)
        mode[7] = 'w';
    if (st_mode & S_IXOTH)
        mode[8] = 'x';

    // get additional permisions(macos only)
    //  char attribute_name[XATTR_SIZE_MAX];
    //  char value[XATTR_SIZE_MAX];
    //  ssize_t buffer_len = listxattr(dir->path, attribute_name, XATTR_SIZE_MAX, XATTR_NOFOLLOW);
    //  acl_t acl_info = acl_get_file(dir->path, ACL_TYPE_EXTENDED);

    //  if (buffer_len > 0)
    //      mode[9] = '@';
    //  else if (acl_info != NULL)
    //      mode[9] = '+';

    //  char *acl_str = NULL;
    //  if (flags->e)
    //      acl_str = acl_to_text(acl_info, NULL);

    int nlinks = dir->stat.st_nlink;

    struct passwd *pwd = getpwuid(dir->stat.st_uid);
    char *username = pwd ? pwd->pw_name : "unknown";
    struct group *grp = getgrgid(dir->stat.st_gid);
    char *groupname = grp ? grp->gr_name : "unknown";

    // Определение размера файла
    off_t size = dir->stat.st_size;

    // Определение даты и времени последней модификации
    time_t current_time;
    time(&current_time);

    time_t time;
    if (flags->c)
        time = dir->stat.st_ctime;
    else if (flags->u)
        time = dir->stat.st_atime;
    else
        time = dir->stat.st_mtime;

    char *time_str = ctime(&time);
    char **full_date =
 mx_strsplit(time_str, ' ');

    char *linked_file = mx_strnew(dir->stat.st_size);
    int bytes;
    if ((bytes = readlink(dir->path, linked_file, dir->stat.st_size + 1)) == -1)
        mx_strdel(&linked_file);
    else
        linked_file[bytes] = '\0';

    mx_printchar(filetype);
    mx_printstr(mode);
    mx_printchar(' ');
    mx_printint(nlinks);
    mx_printchar(' ');
    mx_printstr(username);
    mx_printchar(' ');
    mx_printchar(' ');
    mx_printstr(groupname);
    mx_printchar(' ');
    mx_printchar(' ');
    mx_printint(size);
    mx_printchar(' ');
    mx_printstr(full_date[1]);
    mx_printchar(' ');
    mx_printstr(full_date[2]);
    mx_printchar(' ');

    if (flags->T)
        write(1, &time_str[11], 13);
    else if ((current_time - time) > 15552000 
    || ((current_time - time) < 0 && (current_time - time) > -15552000))
        write(1, full_date[4], 4);
    else
        write(1, full_date[3], 5);
    mx_printchar(' ');

    if (flags->G && isatty(1))
        print_G_flag(dir->name, dir->stat.st_mode);
    else
        mx_printstr(dir->name);

    if (linked_file)
    {
        mx_printstr(" -> ");
        mx_printstr(linked_file);
        mx_strdel(&linked_file);
    }

    mx_printchar('\n');

    // -@e flags, macos only
    //  if (flags->extended_attr && flags->file_per_line && buffer_len > 0)
    //      print_file_xattr(dir->path, buffer_len, attribute_name, value);

    //  if (acl_str)
    //      print_acl_info(acl_str);

    mx_del_strarr(&full_date);
}

void print_l_flag(t_directory **dir, t_flags *flags, bool is_file)
{
    if (!is_file)
    {
        off_t total_blocks = mx_get_total_blocks(dir);
        mx_printstr("total ");
        mx_printint((int)total_blocks);
        mx_printstr("\n");
    }

    t_directory *head = *dir;
    while (head)
    {
        print_row(head, flags);
        head = head->next;
    }
}
