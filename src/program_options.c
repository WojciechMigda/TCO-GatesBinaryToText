#include "program_options.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int parse_args(
    int argc,
    const char * argv[],
    option_t * opt)
{
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        int c;

        while ((c = *++argv[0]))
        {
            switch (c)
            {
                case 'n':
                {
                    if (--argc > 0)
                    {
                        opt->n = (atoi(argv[1]));
                        argv++;
                        *argv += strlen(*argv) - 1;
                    }
                    break;
                }
                case 'k':
                {
                    if (--argc > 0)
                    {
                        opt->k = (atoi(argv[1]));
                        argv++;
                        *argv += strlen(*argv) - 1;
                    }
                    break;
                }
                case 'b':
                {
                    if (--argc > 0)
                    {
                        opt->b = (atof(argv[1]));
                        argv++;
                        *argv += strlen(*argv) - 1;
                    }
                    break;
                }
                case 's':
                {
                    if (--argc > 0)
                    {
                        opt->s_option = 1;
                        opt->s_std = (atof(argv[1]));
                        argv++;
                        *argv += strlen(*argv) - 1;
                    }
                    break;
                }
                default:
                {
                    fprintf(stderr, "Illegal option\n");
                    argc = 0;
                    break;
                }
            }
        }
    }

    if (argc != 2)
    {
        fprintf(stderr, "\n");
        fprintf(stderr, "Usage:   run [options] <input1> <input2>\n\n");
        fprintf(stderr, "Options:                                                 \n");
        fprintf(stderr, "         -n INT    number of sorted tuples for out1.txt and out2.txt [%d]\n", opt->n);
        fprintf(stderr, "         -k INT    number of sorted tuples for out3.txt [%d]\n", opt->k);
        fprintf(stderr, "         -b FLOAT  bin width for out4.txt [%.2f]\n", opt->b);
        fprintf(stderr, "         -s FLOAT  number of standard deviations for out5.txt[%.2f]\n", opt->s_std);

        return -1;
    }

    strcpy(opt->in_file1, argv[0]);
    strcpy(opt->in_file2, argv[1]);

    return 0;
}
