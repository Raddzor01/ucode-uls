#include "../inc/uls.h"

void flags_init(t_flags **flags)
{
    (*flags)->a = false;
    (*flags)->A = false;
    (*flags)->G = false;
    (*flags)->l = false;
    (*flags)->r = false;
    (*flags)->t = false;
    (*flags)->c = false;
    (*flags)->u = false;
    (*flags)->S = false;
    (*flags)->T = false;
    (*flags)->h = false;
    (*flags)->extended_attr = false;
    (*flags)->e = false;
    (*flags)->R = false;
    (*flags)->C = false;
    (*flags)->file_per_line = false;
    (*flags)->f = false;
}

void add_flag(t_flags **flags, char flag)
{
    switch (flag)
    {
    case '1':
        (*flags)->file_per_line = true;
        (*flags)->l = false;
        (*flags)->C = false;
        break;
    case 'l':
        (*flags)->l = true;
        (*flags)->C = false;
        (*flags)->file_per_line = false;
        break;
    case 'R':
        (*flags)->R = true;
        break;
    case 'r':
        (*flags)->r = true;
        break;
    case 'a':
        (*flags)->a = true;
        (*flags)->A = false;
        break;
    case 'A':
        (*flags)->A = true;
        (*flags)->a = false;
        break;
    case 't':
        (*flags)->t = true;
        break;
    case 'u':
        (*flags)->u = true;
        (*flags)->c = false;
        break;
    case 'S':
        (*flags)->S = true;
        break;
    case 'c':
        (*flags)->c = true;
        (*flags)->u = false;
        break;
    case 'G':
        (*flags)->G = true;
        break;
    case 'T':
        (*flags)->T = true;
        break;
    case 'f':
        (*flags)->f = true;
        (*flags)->a = true;
        (*flags)->A = false;
        break;
    case 'C':
        (*flags)->C = true;
        (*flags)->l = false;
        (*flags)->file_per_line = false;
        break;
    default:

        mx_printerr("uls: illegal option -- ");
        write(2, &flag, 1);
        mx_printerr("\n");
        mx_printerr("usage: uls [--Aal1cTGcSutrfR] [file ...]\n");

        free(*flags);
        flags = NULL;

        exit(EXIT_FAILURE);
        break;
    }
}


int get_flags(char *argv[], t_flags **flags)
{
    flags_init(flags);
    int i;

    for (i = 1; argv[i]; i++)
    {
        if (argv[i][0] == '-')
        {

            if (argv[i][1] == '-')
            {
                i++;
                break;
            }

            if (argv[i][1] == '\0')
                break;

            for (int j = 1; argv[i][j]; j++)
                add_flag(flags, argv[i][j]);
        }
        else
        {
            break;
        }
    }
    return i;
}
