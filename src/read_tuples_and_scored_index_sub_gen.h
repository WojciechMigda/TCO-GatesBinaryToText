#ifndef TUPLE_DIM
#warning "TUPLE_DIM was undefined, assuming default value of 2"
#define TUPLE_DIM 2
#endif

#ifdef MAKE_FUN_NAME
#error "Name conflict: MAKE_FUN_NAME"
#endif
#ifdef MAKE_TUPLE_NAME
#error "Name conflict: MAKE_TUPLE_NAME"
#endif

#include "str_concat.h"

#include <string.h>

#define MAKE_FUN_NAME(x) STR_CONCAT2(x, TUPLE_DIM)
#define MAKE_TUPLE_NAME(p, s) STR_CONCAT3(p, TUPLE_DIM, s)

static
void MAKE_FUN_NAME(read_tuples_and_scored_index_sub_d)(
    indexed_score_t * __restrict__ score_p,
    var_t * __restrict__ tup_p,
    FILE * __restrict__ ifile,
    const size_t begin,
    const size_t end
    )
{
    enum { CHUNK = 1000 };

    typedef MAKE_TUPLE_NAME(scored_tuple_d, _t) scored_tuple_t;

    size_t cix = 0; /* chunk index */

    for (cix = begin; (cix + CHUNK) < end; cix += CHUNK)
    {
        const size_t offset = cix * sizeof (scored_tuple_t);
        fseek(ifile, offset, SEEK_SET);


        scored_tuple_t buf[CHUNK];
        const size_t nread = fread(buf, sizeof (scored_tuple_t), CHUNK, ifile);
        if (nread != CHUNK)
        {
            fprintf(stderr, "[%s] Could not read entire chunk from file\n", __FILE__);
        }

        size_t bix = 0;
        for (bix = 0; bix < CHUNK; ++bix)
        {
            const double score = buf[bix].score;
            score_p[cix + bix - begin] = (indexed_score_t){cix + bix, score};
        }
        for (bix = 0; bix < CHUNK; ++bix)
        {
            /* SEGFAULT ALERT:
             * There's a bug in my compiler (5.2.1) which generates assembler
             * which for TUPLE_DIM == 4 reads xmm register from address not
             * aligned on 16 bytes */
            if (TUPLE_DIM < 4)
            {
                size_t vix = 0;
                for (vix = 0; vix < TUPLE_DIM; ++vix)
                {
                    tup_p[TUPLE_DIM * (cix + bix - begin) + vix] = buf[bix].var[vix];
                }
            }
            else
            {
                memcpy(&tup_p[TUPLE_DIM * (cix + bix - begin)], buf[bix].var, sizeof (buf[bix].var));
            }
        }
    }

    if (cix < end)
    {
        const size_t offset = cix * sizeof (scored_tuple_t);
        fseek(ifile, offset, SEEK_SET);

        scored_tuple_t buf[end - cix];
        const size_t nread = fread(buf, sizeof (scored_tuple_t), end - cix, ifile);
        if (nread != (end - cix))
        {
            fprintf(stderr, "[%s] Could not read entire chunk from file\n", __FILE__);
        }

        size_t bix = 0;
        for (bix = 0; bix < (end - cix); ++bix)
        {
            const double score = buf[bix].score;
            score_p[cix + bix - begin] = (indexed_score_t){cix + bix, score};

            size_t vix = 0;
            for (vix = 0; vix < TUPLE_DIM; ++vix)
            {
                tup_p[TUPLE_DIM * (cix + bix - begin) + vix] = buf[bix].var[vix];
            }
        }
    }
}

#undef MAKE_FUN_NAME
#undef MAKE_TUPLE_NAME
#undef TUPLE_DIM