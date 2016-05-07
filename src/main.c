// main.c
//
// Paul Draghicescu
// pdraghicescu@pnri.org
// 4/6/2015
//

#include "parse_program_options.h"
#include "program_options.h"
#include "pair.h"
#include "work.h"

#include "run.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int init_options(option_t *opt)
{
    opt->n = 0;
    opt->k = 0;
    opt->b = 0;
    opt->s_std = 0.0;
    opt->s_option = 0;

    return 0;
}

int main(int argc, char const * argv[])
{
    PAIR(int, program_options_t) program_options_ret = parse_program_options(argc, argv);

    if (program_options_ret.first < 0)
    {
        return 1;
    }

    const time_t ltime = time(NULL);
    fprintf(stderr, "%s", asctime(localtime(&ltime)));


    const int work_ret = work(&program_options_ret.second);
    if (work_ret < 0)
    {
        fprintf(stderr, "Error running.\n");
        return 1;
    }

    fprintf(stderr, "Finished Succesfully.\n");

    return 0;

    ////////////////////////////////////////////////////////////////////////////

    int err;
    option_t opt;

    err = init_options(&opt);

    if (err < 0)
    {
        fprintf(stderr, "Error initializing arguments.\n");
        return 1;
    }

    err = parse_args(argc, argv, &opt);
    if (err < 0)
    {
        return 1;
    }

//    const time_t ltime = time(NULL);
//    fprintf(stderr, "%s", asctime(localtime(&ltime)));

    err = run(&opt);
    if (err < 0)
    {
        fprintf(stderr, "Error running.\n");
        return 1;
    }

    fprintf(stderr, "Finished Succesfully.\n");

    return 0;
}
