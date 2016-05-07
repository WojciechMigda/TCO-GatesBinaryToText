/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
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

#include <stddef.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>


SPAN(void) read_scored_tuples(const char * fname)
{
    /*
     * http://www.devshed.com/c/a/BrainDump/Using-mmap-for-Advanced-File-IO/
     */

    const int fd = open(fname, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return MAKE_SPAN(void, NULL, 0);
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1)
    {
        close(fd);
        perror("fstat");
        return MAKE_SPAN(void, NULL, 0);
    }

    if (!S_ISREG(sb.st_mode))
    {
        close(fd);
        fprintf(stderr, "%s is not a file\n", fname);
        return MAKE_SPAN(void, NULL, 0);
    }

    void * p = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED)
    {
        close(fd);
        perror("mmap");
        return MAKE_SPAN(void, NULL, 0);
    }

    if (close(fd) == -1)
    {
        munmap(p, sb.st_size);
        perror("close");
        return MAKE_SPAN(void, NULL, 0);
    }

    return MAKE_SPAN(void, p, sb.st_size);
}


int release_scored_tuples(SPAN(void) span)
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
