/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: utoa_test.c
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
 * 2016-05-14   wm              Initial version
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define EAX ax.e
#define RAX ax.r

#define EDX dx.e
#define RDX dx.r

#define R8  r8.r
#define R8D r8.e

#define R9  r9.r
#define R9D r9.e

#define R10  r10.r
#define R10D r10.e

#define R11  r11.r
#define R11D r11.e

#define MOV(lhs, rhs) lhs = (rhs);
#define ADD(lhs, rhs) lhs += (rhs);
#define SUB(lhs, rhs) lhs -= (rhs);
#define IMULR(lhs, rhs) lhs = (int64_t)(lhs) * (int64_t)(rhs);
#define IMULE3(lhs, rhs, c) lhs = (int32_t)rhs * (c);
#define SHR(lhs, rhs) lhs >>= (rhs);
#define SHL(lhs, rhs) lhs <<= (rhs);
#define AND(lhs, rhs) lhs &= (rhs);
#define OR(lhs, rhs) lhs |= (rhs);

void utoa(uint32_t what, char * out_p)
{
    typedef union reg
    {
        uint32_t e;
        int32_t ei;
        uint64_t r;
        int64_t ri;
    } reg_t;
    reg_t ax;
    reg_t dx;
    reg_t r11;
    reg_t r8;
    reg_t r9;
    reg_t r10;

    char buf[12];
    char * p = buf;

    RDX = what;

    MOV     (EAX, 0xA7C5AC47)
    ADD     (RDX, 1)
    IMULR   (RAX, RDX)
    SHR     (RAX, 48)          // EAX = val / 100000

    IMULE3  (R11D, EAX, 100000)
    ADD     (EAX, 1)
    SUB     (EDX, R11D)        // EDX = (val % 100000) + 1

    IMULR   (RAX, 214748)      // RAX = (val / 100000) * 2^31 / 10000
    IMULR   (RDX, 214748)      // RDX = (val % 100000) * 2^31 / 10000

    // Extract buf[0] & buf[5]
    MOV     (R8, RAX)
    MOV     (R9, RDX)
    //LEA     EAX, [RAX+RAX]   ; RAX = (RAX * 2) & 0xFFFFFFFF
    //LEA     EDX, [RDX+RDX]   ; RDX = (RDX * 2) & 0xFFFFFFFF
    //LEA     RAX, [RAX+RAX*4] ; RAX *= 5
    //LEA     RDX, [RDX+RDX*4] ; RDX *= 5
    RAX = ((RAX * 2) & 0xFFFFFFFF) * 5;
    RDX = ((RDX * 2) & 0xFFFFFFFF) * 5;
    SHR     (R8, 31)           // R8 = buf[0]
    SHR     (R9, 31)           // R9 = buf[5]

    //; Extract buf[1] & buf[6]
    MOV     (R10, RAX)
    MOV     (R11, RDX)
//    LEA     EAX, [RAX+RAX]   ; RAX = (RAX * 2) & 0xFFFFFFFF
//    LEA     EDX, [RDX+RDX]   ; RDX = (RDX * 2) & 0xFFFFFFFF
//    LEA     RAX, [RAX+RAX*4] ; RAX *= 5
//    LEA     RDX, [RDX+RDX*4] ; RDX *= 5
    RAX = ((RAX * 2) & 0xFFFFFFFF) * 5;
    RDX = ((RDX * 2) & 0xFFFFFFFF) * 5;
    SHR     (R10, 31 - 8)
    SHR     (R11, 31 - 8)
    AND     (R10D, 0x0000FF00) //; R10 = buf[1] << 8
    AND     (R11D, 0x0000FF00) //; R11 = buf[6] << 8
    OR      (R10D, R8D)        //; R10 = buf[0] | (buf[1] << 8)
    OR      (R11D, R9D)        //; R11 = buf[5] | (buf[6] << 8)

    //; Extract buf[2] & buf[7]
    MOV     (R8, RAX)
    MOV     (R9, RDX)
//    LEA     EAX, [RAX+RAX]   ; RAX = (RAX * 2) & 0xFFFFFFFF
//    LEA     EDX, [RDX+RDX]   ; RDX = (RDX * 2) & 0xFFFFFFFF
//    LEA     RAX, [RAX+RAX*4] ; RAX *= 5
//    LEA     RDX, [RDX+RDX*4] ; RDX *= 5
    RAX = ((RAX * 2) & 0xFFFFFFFF) * 5;
    RDX = ((RDX * 2) & 0xFFFFFFFF) * 5;
    SHR     (R8, 31 - 16)
    SHR     (R9, 31 - 16)
    AND     (R8D, 0x00FF0000)  //; R8 = buf[2] << 16
    AND     (R9D, 0x00FF0000)  //; R9 = buf[7] << 16
    OR      (R8D, R10D)        //; R8 = buf[0] | (buf[1] << 8) | (buf[2] << 16)
    OR      (R9D, R11D)        //; R9 = buf[5] | (buf[6] << 8) | (buf[7] << 16)

    //; Extract buf[3], buf[4], buf[8], & buf[9]
    MOV     (R10, RAX)
    MOV     (R11, RDX)
//    LEA     EAX, [RAX+RAX]   ; RAX = (RAX * 2) & 0xFFFFFFFF
//    LEA     EDX, [RDX+RDX]   ; RDX = (RDX * 2) & 0xFFFFFFFF
//    LEA     RAX, [RAX+RAX*4] ; RAX *= 5
//    LEA     RDX, [RDX+RDX*4] ; RDX *= 5
    RAX = ((RAX * 2) & 0xFFFFFFFF) * 5;
    RDX = ((RDX * 2) & 0xFFFFFFFF) * 5;
    SHR     (R10, 31 - 24)
    SHR     (R11, 31 - 24)
    AND     (R10D, 0xFF000000) //; R10 = buf[3] << 24
    AND     (R11D, 0xFF000000) //; R11 = buf[7] << 24
    //AND     (RAX, 0x80000000)  //; RAX = buf[4] << 31
    //AND     (RDX, 0x80000000)  //; RDX = buf[9] << 31
    AND     (RAX, 0x7F80000000)  //; RAX = buf[4] << 31
    AND     (RDX, 0x7F80000000)  //; RDX = buf[9] << 31
    OR      (R10D, R8D)        //; R10 = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24)
    OR      (R11D, R9D)        //; R11 = buf[5] | (buf[6] << 8) | (buf[7] << 16) | (buf[8] << 24)
//    LEA     RAX, [R10+RAX*2] ; RAX = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24) | (buf[4] << 32)
//    LEA     RDX, [R11+RDX*2] ; RDX = buf[5] | (buf[6] << 8) | (buf[7] << 16) | (buf[8] << 24) | (buf[9] << 32)
    RAX = R10 + RAX * 2;
    RDX = R11 + RDX * 2;

    //; Compact the character strings
    SHL     (RAX, 24)          // RAX = (buf[0] << 24) | (buf[1] << 32) | (buf[2] << 40) | (buf[3] << 48) | (buf[4] << 56)
    MOV     (R8, 0x3030303030303030)
//    SHRD    RAX, RDX, 24     ; RAX = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24) | (buf[4] << 32) | (buf[5] << 40) | (buf[6] << 48) | (buf[7] << 56)
    RAX >>= 24;
    RAX |= ((RDX) << (64 - 24));
    SHR     (RDX, 24)          //; RDX = buf[8] | (buf[9] << 8)

    //; Store 12 characters. The last 2 will be null bytes.
    OR      (R8, RAX)
//    LEA     R9, [RDX+0x3030]
    R9 = RDX + 0x3030;
//    MOV     [RCX], R8
//    MOV     [RCX+8], R9D
    *(uint64_t *)p = R8;
    *(uint64_t *)(p + 8) = R9D;

}

int main()
{
    srand(time(NULL));

    char obuf[20];

    utoa(random(), obuf);

    return 0;
}
