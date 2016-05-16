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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char const * argv[])
{
    PAIR(int, program_options_t) program_options_ret = parse_program_options(argc, argv);

    /* check status code */
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
}
