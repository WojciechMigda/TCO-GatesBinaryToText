/* based on https://github.com/swenson/sort
 * MIT License */

#ifndef QUICKSORT_MIXIN_H_
#define QUICKSORT_MIXIN_H_

#include "pair.h"
#include "indexed_score.h"

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif


typedef indexed_score_t index_entry_t;
typedef index_entry_t SORT_TYPE;


//static __attribute__((always_inline))
//int quicksort_index_cmp(const index_entry_t a, const index_entry_t b);

static inline
int quicksort_index_cmp(const index_entry_t a, const index_entry_t b)
{
    return a.second < b.second ?
        1 : (a.second > b.second ? -1 :
            a.first < b.first ?
                1 : (a.first > b.first ? - 1 : 0)
            );
} __attribute__((always_inline))


#define SORT_SWAP(x,y) {SORT_TYPE __SORT_SWAP_t = (x); (x) = (y); (y) = __SORT_SWAP_t;}
#define SORT_CMP(x, y) quicksort_index_cmp(x, y)


/* Function used to do a binary search for binary insertion sort */
static inline
int64_t BINARY_INSERTION_FIND(
    SORT_TYPE * dst,
    const SORT_TYPE x,
    const size_t size)
{
    int64_t l, c, r;
    SORT_TYPE cx;
    l = 0;
    r = size - 1;
    c = r >> 1;

    /* check for out of bounds at the beginning. */
    if (SORT_CMP(x, dst[0]) < 0)
    {
        return 0;
    }
    else if (SORT_CMP(x, dst[r]) > 0)
    {
        return r;
    }

    cx = dst[c];

    while (1)
    {
        const int val = SORT_CMP(x, cx);

        if (val < 0)
        {
            if (c - l <= 1)
            {
                return c;
            }

            r = c;
        }
        else
        { /* allow = for stability. The binary search favors the right. */
            if (r - c <= 1)
            {
                return c + 1;
            }

            l = c;
        }

        c = l + ((r - l) >> 1);
        cx = dst[c];
    }
}


/* Binary insertion sort, but knowing that the first "start" entries are sorted.  Used in timsort. */
static inline
void BINARY_INSERTION_SORT_START(
    SORT_TYPE * dst,
    const size_t start,
    const size_t size)
{
    uint64_t i;

    for (i = start; i < size; i++)
    {
        int64_t j;
        SORT_TYPE x;
        int64_t location;

        /* If this entry is already correct, just move along */
        if (SORT_CMP(dst[i - 1], dst[i]) <= 0)
        {
            continue;
        }

        /* Else we need to find the right place, shift everything over, and squeeze in */
        x = dst[i];
        location = BINARY_INSERTION_FIND(dst, x, i);

        for (j = i - 1; j >= location; j--)
        {
            dst[j + 1] = dst[j];
        }

        dst[location] = x;
    }
}


static inline
void BINARY_INSERTION_SORT(SORT_TYPE * dst, const size_t size)
{
    /* don't bother sorting an array of size <= 1 */
    if (size <= 1)
    {
        return;
    }

    BINARY_INSERTION_SORT_START(dst, 1, size);
}


static inline
size_t QUICK_SORT_PARTITION(
    SORT_TYPE * dst,
    const size_t left,
    const size_t right,
    const size_t pivot)
{
    SORT_TYPE value = dst[pivot];
    size_t index = left;
    size_t i;
    int not_all_same = 0;
    /* move the pivot to the right */
    SORT_SWAP(dst[pivot], dst[right]);

    for (i = left; i < right; i++)
    {
        int cmp = SORT_CMP(dst[i], value);
        /* check if everything is all the same */
        not_all_same |= cmp;

        if (cmp < 0)
        {
            SORT_SWAP(dst[i], dst[index]);
            index++;
        }
    }

    SORT_SWAP(dst[right], dst[index]);

    /* avoid degenerate case */
    if (not_all_same == 0)
    {
        return SIZE_MAX;
    }

    return index;
}


static inline
void QUICK_SORT_RECURSIVE(
    SORT_TYPE * dst,
    const size_t left,
    const size_t right)
{
    size_t pivot;
    size_t new_pivot;

    if (right <= left)
    {
        return;
    }

    if ((right - left + 1U) < 16U)
    {
        BINARY_INSERTION_SORT(&dst[left], right - left + 1U);
        return;
    }

    pivot = left + ((right - left) >> 1);
    /* this seems to perform worse by a small amount... ? */
    /* pivot = MEDIAN(dst, left, pivot, right); */
    new_pivot = QUICK_SORT_PARTITION(dst, left, right, pivot);

    /* check for partition all equal */
    if (new_pivot == SIZE_MAX)
    {
        return;
    }

    QUICK_SORT_RECURSIVE(dst, left, new_pivot - 1U);
    QUICK_SORT_RECURSIVE(dst, new_pivot + 1U, right);
}


static inline
void QUICK_SORT(SORT_TYPE * dst, const size_t size)
{
    /* don't bother sorting an array of size 1 */
    if (size <= 1)
    {
        return;
    }

    QUICK_SORT_RECURSIVE(dst, 0U, size - 1U);
}



#ifdef __cplusplus
}
#endif

#endif /* QUICKSORT_MIXIN_H_ */
