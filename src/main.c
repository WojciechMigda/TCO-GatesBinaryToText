// main.c
//
// Paul Draghicescu
// pdraghicescu@pnri.org
// 4/6/2015
//

#include "program_options.h"
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

    //TODO: remove this, implement these options
    if ((opt.n != 0) || (opt.k != 0) || (opt.b != 0))
    {
        fprintf(stderr, "WARNING: -n, -k, -b not yet implemented!\n");
        //return 1;
    }

    const time_t ltime = time(NULL);
    fprintf(stderr, "%s", asctime(localtime(&ltime)));

    err = run(&opt);
    if (err < 0)
    {
        fprintf(stderr, "Error running.\n");
        return 1;
    }

    fprintf(stderr, "Finished Succesfully.\n");

    return 0;
}
