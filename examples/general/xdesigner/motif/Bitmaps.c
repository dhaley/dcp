/*
** Bitmaps and Pixmaps used in a Motif program are generally
** referenced by a name (e.g. 50_foreground) which is used as a key to
** fetch a bitmap from a bitmap file. To avoid separating the
** application from its bitmaps, it is often a good idea to compile
** the bitmaps in to the apllication, thus simplifying installation
** and preventing bitmaps from going missing. This code demonstrates
** one way of doing this.
** The bitmaps are compiled into the code, and then installed in the
** Motif image cache. Motif installs a resource converter which
** converts names from the image cache into pixmaps. Thus you can
** reference your bitmaps by name, e.g. in your resource file, but
** still have them compiled into the application.
*/

/* Include the bitmaps you are using: */
#include "grey.bm"
#include "stripe.bm"


/* Define an array listing all the pixmaps: */
typedef struct Bitmap_s 
{
	char  *ic_name ;
	char  *ic_bits ;
	int    ic_width ;
	int    ic_height ;
	XImage ic_image ;
} Bitmap_t, *Bitmap_p ;

static Bitmap_t bitmaps[] = 
{
	{ "grey",      grey_bits,    grey_width,   grey_height   },
	{ "stripe",    stripe_bits,  stripe_width, stripe_height },
	{ (char *) 0,  (char *) 0,   0,            (XImage) 0    }
} ;


/*
** At application startup (before creating widgets which may use the
** pixmaps), call this routine to register all the pixmaps in the
** array above. They can then be referred to by name when setting
** resources.
*/

#ifndef   _NO_PROTO
void register_pixmaps(void)
#else  /* _NO_PROTO */
void register_pixmaps()
#endif /* _NO_PROTO */
{
	int i ;

	for (i = 0 ; bitmaps[i].ic_name != (char *) 0 ; i++) {
		Bitmap_p ic = &bitmaps[i] ;

		ic->ic_image.width            = ic->ic_width ;
		ic->ic_image.height           = ic->ic_height ;
		ic->ic_image.xoffset          = 0 ;
		ic->ic_image.format           = XYBitmap ;
		ic->ic_image.byte_order       = MSBFirst ;
		ic->ic_image.bitmap_pad       = 8 ;
		ic->ic_image.bitmap_bit_order = LSBFirst ;
		ic->ic_image.bitmap_unit      = 8 ;
		ic->ic_image.depth            = 1 ;
		ic->ic_image.bytes_per_line   = (ic->ic_width + 7) / 8 ;
		ic->ic_image.obdata           = 0 ;
		ic->ic_image.data             = ic->ic_bits ;

		XmInstallImage(&(ic->ic_image), ic->ic_name) ;
	}
}
