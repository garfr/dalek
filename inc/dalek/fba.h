/*
 * === fba.h ===
 *
 * Fixed buffer allocators.
 *
 * Copyright 2021 Gavin Ratcliff
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef DALEK_FBA_H
#define DALEK_FBA_H

#include <dalek/defs.h>

/*
 * Stores a fixed chunk of bytes and allocates off pieces. 
 * The fixed buffer cannot be resized and memory must be released all at one time
 */
struct dalek_fba {
    uint8_t *buf, *top, *last;
};

#ifdef DALEK_CAREFUL
#define DALEK_FBA_ALLOC(fba, amt) ((fba)->buf == NULL ||                      \
                                  ((fba)->top += amt) >= (fba)->last ? NULL : \
                                   (fba)->top - amt)
#define DALEK_FBA_RESET(fba) (((fba)->top = memset((fba)->buf, 0,             \
                                                   (fba)->last - (fba)->buf)))
#else
#define DALEK_FBA_ALLOC(fba, amt) (((fba)->top += ((size_t)amt)) >=           \
                                    (fba)->last ? NULL :                      \
                                    (fba)->top - ((size_t)amt))
#define DALEK_FBA_RESET(fba) ((fba)->top = (fba)->buf)

#endif /* DALEK_FBA_ALLOC */

/*
 * Initializes the fixed buffer allocator pointed to by [fba].
 * The allocator takes ownership of the buffer for as long as needed.
 * If the buffer is invalidated, all allocations made with the buffer are invalid.
 */
void dalek_fba_init(struct dalek_fba *fba, uint8_t *buf, size_t size);

/*
 * Removes all link between the allocator and its underlying buffer, making all
 * future allocations dereference NULL pointers or return NULL (on DALEK_CAREFUL).
 */
void dalek_fba_deinit(struct dalek_fba *fba);

/* 
 * Returns a pointer to the start of a buffer [amt] bytes long.
 * Returns NULL on OOM.
 */
uint8_t *dalek_fba_alloc(struct dalek_fba *fba, size_t amt);

/*
 * All blocks allocated from [fba] are invalidated and the container begins 
 * allocating memory from the start of the buffer again.
 *
 * If DALEK_CAREFUL is defined, it zeroes all memory.
 */
void dalek_fba_reset(struct dalek_fba *fba);

#endif /* DALEK_FBA_H */