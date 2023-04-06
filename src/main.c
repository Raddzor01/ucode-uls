#include "../inc/uls.h"

int main(int argc, char *argv[])
{
    t_flags *flags = malloc(sizeof(t_flags));
    int count = get_flags(argv, &flags);
    bool error = uls(argc, argv, flags, count);

    free(flags);
    flags = NULL;

    return error;
}
