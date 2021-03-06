/*
 * === fba.c ===
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

#include <string.h>

#include <dalek/fba.h>

void 
dalek_fba_init(struct dalek_fba *fba, uint8_t *buf, size_t size) {
    fba->buf = fba->top = buf;
    fba->last = fba->buf + size; 
}

void 
dalek_fba_deinit(struct dalek_fba *fba) {
    fba->buf = fba->last = fba->top = NULL;
}

uint8_t *
dalek_fba_alloc(struct dalek_fba *fba, size_t amt) {
#ifdef DALEK_CAREFUL
    if (fba->buf == NULL) {
        return NULL
    }
#endif /* DALEK_CAREFUL */
    if ((fba->top += amt) >= fba->last) {
        return NULL;
    }
    return fba->top - amt;
}

void
dalek_fba_reset(struct dalek_fba *fba) {
    fba->top = fba->buf;
#ifdef DALEK_CAREFUL
    memset(fba->buf, 0, fba->last - fba->buf);
#endif /* DALEK_CAREFUL */
}