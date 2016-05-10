/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: read_scored_tuples.c
 *
 * Description:
 *      description
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2016-05-07   wm              Initial version
 *
 ******************************************************************************/

#include "read_scored_tuples.h"
#include "span.h"
#include "io.h"

#include <stddef.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


SPAN(void) read_scored_tuples_mmap(const char * fname)
{
    /*
     * http://www.devshed.com/c/a/BrainDump/Using-mmap-for-Advanced-File-IO/
     */

    const int fd = open(fname, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return NULL_SPAN(void);
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1)
    {
        close(fd);
        perror("fstat");
        return NULL_SPAN(void);
    }

    if (!S_ISREG(sb.st_mode))
    {
        close(fd);
        fprintf(stderr, "%s is not a file\n", fname);
        return NULL_SPAN(void);
    }

    void * p = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED)
    {
        close(fd);
        perror("mmap");
        return NULL_SPAN(void);
    }

    if (close(fd) == -1)
    {
        munmap(p, sb.st_size);
        perror("close");
        return NULL_SPAN(void);
    }

    return MAKE_SPAN(void, p, sb.st_size);
}


int release_scored_tuples_mmap(SPAN(void) span)
{
    if (munmap(span.ptr, span.sz) == -1)
    {
        perror("munmap");
        return -1;
    }
    else
    {
        return 0;
    }
}


SPAN(void) read_scored_tuples_malloc(const char * fname)
{
    FILE * ifile = NULL;
    void * data_p = NULL;

    SPAN(void) span = NULL_SPAN(void);

    do
    {
        ifile = fopen(fname, "rb");
        if (ifile == NULL)
        {
            fprintf(stderr, "Error: couldn't open tuples data file %s.\n", fname);
            break;
        }

        const size_t fsz = fsize(ifile);

        if (fsz == 0)
        {
            fprintf(stderr, "Error: empty tuples data file %s\n", fname);
            break;
        }

        data_p = malloc(fsz);
        if (NULL == data_p)
        {
            fprintf(stderr, "Error: couldn't allocate memory for tuples data, needed %zu bytes\n", fsz);
            break;
        }

        const size_t nread = fread(data_p, 1, fsz, ifile);
        if (nread != fsz)
        {
            fprintf(stderr, "Error: couldn't read tuples data from file, got %zu bytes\n", nread);
            break;
        }

        span = MAKE_SPAN(void, data_p, fsz);
        data_p = NULL;

    } while (0);

    if (ifile != NULL)
    {
        fclose(ifile);
        ifile = NULL;
    }

    if (data_p != NULL)
    {
        free(data_p);
        data_p = NULL;
    }

    return span;
}


int release_scored_tuples_malloc(SPAN(void) span)
{
    if (span.ptr)
    {
        free(span.ptr);
    }

    return 0;
}