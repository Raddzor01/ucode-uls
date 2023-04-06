#include "../inc/uls.h"

static void print_pwd_id(uid_t uid, int username_width)
{
    char *pwd_id = mx_itoa(uid);
    print_aligned_str(pwd_id, username_width, false);
    mx_printchar(' ');
    mx_printchar(' ');
    mx_strdel(&pwd_id);
}

static void print_grp_id(gid_t gid, int group_width)
{
    char *grp_id = mx_itoa(gid);
    print_aligned_str(grp_id, group_width, false);
    mx_strdel(&grp_id);
}

static void print_pwd_name(char *username, int username_width)
{
    print_aligned_str(username, username_width, false);
    mx_printchar(' ');
    mx_printchar(' ');
}

static void print_grp_name(char *groupname, int group_width)
{
    print_aligned_str(groupname, group_width, false);
}

void print_pwd_grp(struct stat st, int username_width, int group_width, const t_flags *flags)
{
    struct passwd *pwd = getpwuid(st.st_uid);
    struct group *grp = getgrgid(st.st_gid);

    if (flags->n)
    {
        if (!flags->o)
            print_pwd_id(pwd ? pwd->pw_uid : st.st_uid, username_width);
        if (!flags->g)
            print_grp_id(grp ? grp->gr_gid : st.st_gid, group_width);
        mx_printchar(' ');
        mx_printchar(' ');
        return;
    }

    if (!flags->o)
        print_pwd_name(pwd ? pwd->pw_name : mx_itoa(st.st_uid), username_width);
    if (!flags->g)
        print_grp_name(grp ? grp->gr_name : mx_itoa(st.st_gid), group_width);
    mx_printchar(' ');
    mx_printchar(' ');
}
