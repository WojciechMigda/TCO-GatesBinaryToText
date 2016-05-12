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

#define MAKE_FUN_NAME(x) STR_CONCAT2(x, TUPLE_DIM)
#define MAKE_TUPLE_NAME(p, s) STR_CONCAT3(p, TUPLE_DIM, s)

static
void MAKE_FUN_NAME(read_scored_index_sub_d)(
    indexed_score_t * dst_p,
    FILE * ifile,
    size_t begin,
    size_t end
    )
{
    enum { CHUNK = 100 };

    typedef MAKE_TUPLE_NAME(scored_tuple_d, _t) scored_tuple_t;

    size_t cix = 0;

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
            dst_p[cix + bix - begin] = (indexed_score_t){cix + bix, score};
        }
    }

    if (cix < end)
    {
        const size_t offset = cix * sizeof (scored_tuple_t);
        fseek(ifile, offset, SEEK_SET);

        scored_tuple_t buf[end - cix];
        const size_t nread = fread(buf, sizeof (scored_tuple_t), end - cix, ifile);
        (void)nread;

        size_t bix = 0;
        for (bix = 0; bix < (end - cix); ++bix)
        {
            const double score = buf[bix].score;
            dst_p[cix + bix - begin] = (indexed_score_t){cix + bix, score};
        }
    }
}

#undef MAKE_FUN_NAME
#undef MAKE_TUPLE_NAME
#undef TUPLE_DIM
