#ifndef TUPLE_DIM
#warning "TUPLE_DIM was undefined, assuming default value of 2"
#define TUPLE_DIM 2
#endif

#ifdef MAKE_NAME
#error "Name conflict: MAKE_NAME"
#endif

#include "str_concat.h"

#define MAKE_NAME(p, s) STR_CONCAT3(p, TUPLE_DIM, s)

typedef struct MAKE_NAME(scored_tuple_d, _s)
{
    uint32_t var[TUPLE_DIM];
    double score;
} __attribute__ ((packed))
MAKE_NAME(scored_tuple_d, _t);

#undef MAKE_NAME
#undef TUPLE_DIM
