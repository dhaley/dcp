/* Copyright 03/13/06 Sun Microsystems, Inc. All Rights Reserved */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "stopwatch.h"

/* parameters defining various tasks */
#define	BUFSIZE		16384
#define	NBLKS		1024

/*=======================================================*/
/*	iofile - do some file io operations */
int
iofile()
{
	FILE	*fp;	/* FILE pointer for stdio */
	int	k;	/* temp value for loop */
	int	i;
	char	*buf;
	hrtime_t	start;
	hrtime_t	vstart;
	char *fname = "/usr/tmp/synprogXXXXXX";
	int	ret;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of iofile -- stdio", NULL);

	ret = mkstemp(fname);
	if(ret == -1) {
		fprintf(stderr, "Unable to make a temporary name\n");
		exit(1);
	}
	fprintf(stderr, "\tUsing %s as scratch file\n", fname);

	/* allocate a buffer for the reading */
	/* note that this buffer is leaked! */
	buf = (char *) malloc(BUFSIZE);

	/* open the file */
	fp = fdopen(ret, "w");
	if(fp == NULL) {
		fprintf(stderr, "++ERROR opening %s, error %d\n",
			fname, errno );
		exit(1);
	}

	/* loop, writing the buffer to the file... */
	for(i = 0; i < NBLKS; i ++) {
		k = fwrite(buf, sizeof(char), BUFSIZE, fp);
		if (k != BUFSIZE) {
			fprintf(stderr, "++ERROR writing %s, error %d\n",
				fname, errno );
			exit(1);
		}
	}
	fclose (fp);

	sprintf(buf, "fwrite: %d blocks of %d", i, BUFSIZE);
	whrvlog(gethrtime()-start, gethrvtime()-vstart,
		buf, NULL);

	/* now reopen the file, and read it */
	start = gethrtime();
	vstart = gethrvtime();

	fp = fopen(fname, "r");
	if(fp == NULL) {
		fprintf(stderr, "++ERROR opening %s, error %d\n",
			fname, errno );
		exit(1);
	}
	i = 0;
	for(;;) {
		k = fread(buf, sizeof(char), BUFSIZE, fp);
		if (k < 0) {
			fprintf(stderr, "++ERROR reading %s, error %d\n",
				fname, errno );
		}
		if (k == 0) {
			/* close the file */
			fclose(fp);
			break;

		} else if (k != BUFSIZE) {
			/* short read */
			sprintf(buf,
		"\tunexpecter short read %d on %s\n",
				k, fname);
			fprintf(stderr, buf);
			break;
		} else {
			/* bump the block counter */
			i ++;
		}
	}
	sprintf(buf, "fread: %d blocks of %d", i, BUFSIZE);
	whrvlog(gethrtime()-start, gethrvtime()-vstart,
		buf, NULL);

	unlink(fname);

	return 0;
}

/*=======================================================*/
/*	iotest - do various io syscalls */
int
iotest()
{
	char	*fname = "/usr/tmp/foobar";
	int	fd;	/* file descriptor for raw IO */
	int	fd2;	/* file descriptor for raw IO */
	int	k;	/* temp value for loop */
	char	buf[BUFSIZE];
	unsigned long	size = 0;

	/* Log the regular read */
	wlog("start of iotest", NULL);

	/* create an empty file */
	fd = creat(fname, 0666);

	/* dup the file descriptor */
	fd2 = dup(fd);
	close(fd2);
	close(fd);

	/* now open the empty file */
	fd = open(fname, O_RDONLY);

	/* loop, reading into the buffer */
	size = 0;
	for(;;) {
		k = read(fd, buf, BUFSIZE);
		if (k < 0) {
			fprintf(stderr, "++ERROR reading %s, error %d\n",
				fname, errno );
		} else {
			size = size + k;
		}
		if (k != BUFSIZE) {
			/* close the file */
			close(fd);

			/* short eread = EOF */
			break;
		}
	}

	/* remove the file */
	unlink(fname);

	return 0;
}
