/* 
 * Copyright 2001,2002 Sun Microsystems, Inc. All Rights Reserved
 *
 * common.h -- 
 *	Common headers, prototypes and so forth to be included in all files.
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>

#include <limits.h>                          /* USHRT_MAX, LONG_MAX          */
#include <sys/types.h>                       /* time_t, ushort_t, size_t     */

typedef   ushort_t   item_type;              /* type of item stored in array */
#define   ITEM_MAX   USHRT_MAX               /* max value                    */
#define   ITEM_SIZE  sizeof(item_type)       /* size of item                 */

extern    long      MAX_ELEMENTS;            /* Max # items we'll generate   */
extern    long      array_len;               /* Max # of items stored in mem */


/* min of 2 entities that can be compared */
#define MIN_OF(a, b) (a) < (b) ?  (a) : (b)

extern void          io_open(char *);
extern void          io_creat(char *);
extern void          io_close(void);
extern void          io_read(item_type *, size_t);
extern void          io_write(item_type *, size_t);
extern item_type*    io_map_file(char *);
extern void          io_unmap(void *, size_t);
extern size_t        io_size(void);
extern void          error(char *);

extern void          gen_data(long);
extern void          show_data(item_type *, long);
extern void          sort_data(item_type *, size_t);
#if defined(VALID) || defined(ERROR)
#undef VALID
#undef ERROR
#endif
#define VALID  1
#define ERROR  0

#endif /* COMMON_H */

