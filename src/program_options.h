#ifndef PROGRAM_OPTIONS_H_
#define PROGRAM_OPTIONS_H_


typedef struct option_s
{
    int n;
    int k;
    double b;
    double s_std;
    int s_option;
    char in_file1[50];
    char in_file2[50];
} option_t;

#include "option_type.h"
#include "pair.h"
#include "span.h"

#include <stdint.h>

DEFINE_OPTION_TYPE(double);

typedef struct program_options_s
{
    uint32_t n; /* [0, 1e6] number of sorted tuples in out1 and out2 */
    uint32_t k; /* [0, 1e5] number of sorted tuples in out3 */
    double b;   /* [0., 1.] bin width */
    OPTION_TYPE(double) maybe_s; /* number of standard deviations */
    const char * in_file1;
    const char * in_file2;

    SPAN(void) (*scored_tuples_reader)(const char * fname);
    int (*scored_tuples_deleter)(SPAN(void) span);
} program_options_t;


int parse_args(
    int argc,
    char const * argv[],
    option_t * opt);


#endif /* PROGRAM_OPTIONS_H_ */
