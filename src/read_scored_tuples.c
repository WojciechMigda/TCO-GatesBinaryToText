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
    FILE * f_data = fopen(fname, "rb");

    if (f_data == NULL)
    {
        perror("fopen");
        return NULL_SPAN(void);
    }

    const size_t sz = fsize(f_data);

    rewind(f_data);

    void * data_p = malloc(sz);
    if (NULL == data_p)
    {
        fclose(f_data);
        //fprintf(stderr, "Error: couldn't allocate memory for data read from file, needed %zu bytes\n", sz);
        perror("malloc");
        return NULL_SPAN(void);
    }

    const size_t nread = fread(data_p, 1, sz, f_data);
    if (nread != sz)
    {
        fprintf(stderr, "Error: couldn't read context from file, got %zu bytes\n", nread);
        fclose(f_data);
        free(data_p);
        return NULL_SPAN(void);
    }

    if (fclose(f_data) != 0)
    {
        perror("fclose");
        free(data_p);
        return NULL_SPAN(void);
    }

    return MAKE_SPAN(void, data_p, sz);
}


int release_scored_tuples_malloc(SPAN(void) span)
{
    if (span.ptr)
    {
        free(span.ptr);
    }

    return 0;
}