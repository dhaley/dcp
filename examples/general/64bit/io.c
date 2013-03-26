/*
 * Copyright 2001,2002 Sun Microsystems, Inc. All Rights Reserved
 *
 * io.c --
 *      Handles all file operations including open, close, read and write.
 */

#include "common.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
/* mmap */
#include <sys/mman.h>

#define PERMS 0644

char*          fname = NULL;
static   int   fd    = -1;
extern   char* prog_name;

void error(char *);

/* Open file for reading and writing */
void
io_open(char *filename)
{
  fname = filename;
  if ( (fd = open(fname, O_RDWR, 0)) < 0) 
      error("Error opening the file" );
}
/* Create file for storing the data */
void
io_creat(char *filename)
{
    fname = filename;
    if ( (fd = creat(fname, PERMS)) < 0) 
      error("Error creating the data file");
}
/* Read "data" from file into an array */
void
io_read(item_type *data, size_t size)
{
  if (  size != read(fd, data, size) ) 
    error("Problem reading data from file");
}

/* Write "data" in array to file */
void
io_write(item_type *data, size_t size)
{
  if (size != write(fd, (item_type *)data, size))
    error("Problem writing data to file");
}

/* Close the fd */
void 
io_close(void)
{
  if ( 0 != close(fd) )
    error("Problem closing file");
}

/* Get file size in bytes using stat */
size_t
io_size(void)
{
  static struct stat stbuf;
  if ( 0 != fstat(fd, &stbuf) )
    error("fstat() failed");

  return stbuf.st_size;
}


/* Map data in file as specified by the arguments to memory */
void *
io_map(void* addr, size_t len, off_t offset)
{
  caddr_t paddr = NULL;
  int     prot  = PROT_READ | PROT_WRITE;
  int     flags = MAP_SHARED;

  if ((paddr = mmap(addr, len, prot, flags, fd, offset)) == MAP_FAILED) 
    error("Problem mapping file");
  return paddr;
}

/* Unmap the memory object in process address space */
void
io_unmap(void* addr, size_t len)
{
  if ( 0 != munmap(addr, len) )
    error("Problem unmmaping data");
}

/* map an entire file to a memory object.  */
item_type *
io_map_file(char *filename)
{
  off_t        file_size;
  long         nitems;
  item_type*   my_data = NULL;
  off_t        offset = 0L;

  fname      = filename;
  io_open(fname);
  file_size  = io_size();
  nitems     = file_size/ITEM_SIZE;
  
  my_data    = (item_type *)io_map((caddr_t)0, file_size, offset);

  return my_data;
}


void
error(char *s) 
{
  static char msg[100];
  sprintf(msg, "%s: %s", prog_name, s);
  perror(msg);
  exit(1);
}
