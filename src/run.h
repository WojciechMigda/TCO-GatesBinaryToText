// Paul Draghicescu
// pdraghicescu@pnri.org
//

#ifndef RUN_H
#define RUN_H

#include "program_options.h"
#include <stdio.h>

enum { TUP_BUF_SIZE = 10000 };

int get_header(FILE* fbin,  int *d, int *n_vars, unsigned long *n_tuples, double *average);
int run(const option_t *opt);
double calculate_std_bin(FILE* fbin, double average, int d, unsigned long n_tuples);

#endif
