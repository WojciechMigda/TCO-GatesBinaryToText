// Paul Draghicescu
// pdraghicescu@pnri.org
//

#ifndef RUN_H
#define RUN_H

enum { TUP_BUF_SIZE = 10000 };

typedef struct option
{
    int n;
    int k;
    double b;
    double s_std;
    int s_option;
    char in_file1[50];
    char in_file2[50];
} option_t;

int get_header(FILE* fbin,  int *d, int *n_vars, unsigned long *n_tuples, double *average);
int run(const option_t *opt);
double calculate_std_bin(FILE* fbin, double average, int d, unsigned long n_tuples);

#endif
