/*@ cc -c -D_NO_PROTO @I @F -o @R.o
*/

/* Text Widget File Front End */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/fcntl.h>
#include <Xm/Xm.h>


#ifndef   _NO_PROTO
static int safer_read(int fid, char *buffer, int to_read)
#else  /* _NO_PROTO */
static int safer_read(fid, buffer, to_read)
	int      fid ;
	char    *buffer ;
	int      to_read ;
#endif /* _NO_PROTO */
{
	register int i ;

		 int have_read = 0 ;
		 int read_left = to_read ;
		 int this_read ;

	while (have_read < to_read) {
		this_read = read(fid,buffer + have_read,read_left) ;

		if (this_read <= 0) {
			break ;
		}

		have_read += this_read ;
		read_left -= this_read ;
	}

	buffer[have_read] = '\0' ;

	return have_read ;
}


#ifndef   _NO_PROTO
static int safer_write(int fid, char *buffer, int to_write)
#else  /* _NO_PROTO */
static int safer_write(fid,buffer,to_write)
	int   fid ;
	char *buffer ;
	int   to_write ;
#endif /* _NO_PROTO */
{
	int have_written = 0 ;
	int write_left   = to_write ;
	int this_write ;

	while (have_written < to_write) {
		this_write = write(fid,buffer + have_written,write_left) ;

		if (this_write <= 0) {
			break ;
		}

		have_written += this_write ;
		write_left   -= this_write ;
	}

	return have_written ;
}


#ifndef   _NO_PROTO
Boolean text_insert_file(Widget w, XmTextPosition position, char *file)
#else  /* _NO_PROTO */
Boolean text_insert_file(w,position,file)
	Widget         w ;
	XmTextPosition position ;
	char          *file ;
#endif /* _NO_PROTO */
{
	int  fid ;
	int  count ;

	char buffer[BUFSIZ + 1] ;

	if ((fid = open(file,O_RDONLY)) >= 0) {
		while ((count =	safer_read(fid,
					  buffer,
					  BUFSIZ)) > 0) {
			XmTextInsert(w,position,buffer) ;

			position = position + (XmTextPosition) count ;
		}

		(void) close(fid) ;

		return True ;
	}

	return False ;
}


#ifndef   _NO_PROTO
Boolean text_read_file(Widget w, char *file)
#else  /* _NO_PROTO */
Boolean text_read_file(w,file)
	Widget  w ;
	char   *file ;
#endif /* _NO_PROTO */
{
	struct stat    sbuf ;
	       char   *buffer ;
	       int     retcode ;
	       int     fid ;

	if ((fid = open(file,O_RDONLY)) < 0) {
		return False ;
	}

	if (fstat(fid,&sbuf) < 0) {
		(void) close(fid) ;

		return False ;
	}

	if ((buffer = (char *) XtMalloc(sbuf.st_size + 1)) == (char *) 0) {
		(void) close(fid) ;

		return False ;
	}

	retcode = safer_read(fid, buffer, (int) sbuf.st_size) ;

	XmTextSetString(w,buffer) ;

	XtFree(buffer) ;

	(void) close(fid) ;

	return ((retcode < 0) ? False : True) ;
}


#ifndef   _NO_PROTO
Boolean text_write_file(Widget w, char *file)
#else  /* _NO_PROTO */
Boolean text_write_file(w,file)
	Widget w ;
	char  *file ;
#endif /* _NO_PROTO */
{
	extern char   *XmTextGetString() ;

	char          *buffer ;
	XmTextPosition last ;
	int            fid ;
	Boolean        retcode = False ;

	if ((fid = open(file,O_WRONLY)) < 0) {
		return False ;
	}

	/* You would need to modify _XmStringSourceGetValue        */
	/* If you want to Access Data WITHOUT TAKING A COPY        */
	/* Since the XtGetValue() routine ALSO RETURNS A COPY      */
	/* IN OTHER WORDS AS THINGS STAND, DIRECT TEXT DATA ACCESS */
	/* CANNOT BE DONE WITHOUT POKING INTO THE TEXT WIDGET      */
	
	buffer = XmTextGetString(w) ;

	if (buffer != (char *) 0) {
		last = XmTextGetLastPosition(w) ;

		if (safer_write(fid, buffer, (int) last) >= 0) {
			retcode = True ;
		}

		XtFree(buffer) ;
	}

	(void) close(fid) ;

	return retcode ;
}
