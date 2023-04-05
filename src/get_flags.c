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
    (*flags)->m = false;
    (*flags)->F = false;
    (*flags)->p = false;
    (*flags)->m = false;
    (*flags)->n = false;
    (*flags)->g = false;
    (*flags)->o = false;
}

void add_flag(t_flags **flags, char flag)
{
    switch (flag)
    {
    case '1':
        (*flags)->file_per_line = true;
        (*flags)->l = false;
        (*flags)->C = false;
        (*flags)->m = false;
        break;
    case 'l':
        (*flags)->l = true;
        (*flags)->C = false;
        (*flags)->file_per_line = false;
        (*flags)->m = false;
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
    case 'h':
        (*flags)->h = true;
        break;
    case '@':
        (*flags)->extended_attr = true;
        break;
    case 'e':
        (*flags)->e = true;
        break;
    case 'm':
        (*flags)->m = true;
        (*flags)->file_per_line = false;
        (*flags)->l = false;
        break;
    case 'F':
        (*flags)->F = true;
        (*flags)->p = false;
        break;
    case 'p':
        (*flags)->p = true;
        (*flags)->F =false;
        break;
    case 'n':
        (*flags)->n = true;
        break;
    case 'g':
        (*flags)->g = true;
        break;
    case 'o':
        (*flags)->o = true;
        break;
    default:

        mx_printerr("uls: illegal option -- ");
        write(2, &flag, 1);
        mx_printerr("\n");
        mx_printerr("usage: uls [--Aal1cTGcSutrfmRpnFe@] [file ...]\n");

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
