#include "parse_program_options.h"
#include "program_options.h"
#include "bool.h"
#include "pair.h"
#include "read_scored_tuples.h"
#include "num_procs.h"
#include "min_max.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


program_options_t new_program_options(void)
{
    return (program_options_t){0, 0, 0., OPTION_TYPE_NONE(double),
        NULL, NULL,
        read_scored_tuples_malloc, release_scored_tuples_malloc,
        num_procs()
    };
}


PAIR(int, program_options_t) parse_program_options(
    int argc,
    char const * argv[])
{
    program_options_t prog_opts = new_program_options();

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
                        prog_opts.n = atoi(argv[1]);
                        argv++;
                        *argv += strlen(*argv) - 1;
                    }
                    break;
                }
                case 'k':
                {
                    if (--argc > 0)
                    {
                        prog_opts.k = atoi(argv[1]);
                        argv++;
                        *argv += strlen(*argv) - 1;
                    }
                    break;
                }
                case 'b':
                {
                    if (--argc > 0)
                    {
                        prog_opts.b = atof(argv[1]);
                        argv++;
                        *argv += strlen(*argv) - 1;
                    }
                    break;
                }
                case 't':
                {
                    if (--argc > 0)
                    {
                        const int iparam = atoi(argv[1]);

                        prog_opts.nthreads = MAX(iparam, 1);
                        argv++;
                        *argv += strlen(*argv) - 1;
                    }
                    break;
                }
                case 'M':
                {
                    prog_opts.scored_tuples_reader = read_scored_tuples_mmap;
                    prog_opts.scored_tuples_deleter = release_scored_tuples_mmap;
                    break;
                }
                case 's':
                {
                    if (--argc > 0)
                    {
                        prog_opts.maybe_s = OPTION_TYPE_SOME(double, atof(argv[1]));
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
        fprintf(stderr, "         -n INT    number of sorted tuples for out1.txt and out2.txt [%d]\n", prog_opts.n);
        fprintf(stderr, "         -k INT    number of sorted tuples for out3.txt [%d]\n", prog_opts.k);
        fprintf(stderr, "         -b FLOAT  bin width for out4.txt [%.2f]\n", prog_opts.b);
        fprintf(stderr, "         -s FLOAT  number of standard deviations for out5.txt [%.2f]\n", OPTION_TYPE_VALUE(prog_opts.maybe_s));
        fprintf(stderr, "         -t INT    number of threads to use [%d]\n", prog_opts.nthreads);
        //fprintf(stderr, "         -M        mmap-based file access\n");

        return MAKE_PAIR(int, program_options_t, -1, prog_opts);
    }

    prog_opts.in_file1 = argv[0];
    prog_opts.in_file2 = argv[1];

    return MAKE_PAIR(int, program_options_t, 0, prog_opts);
}
