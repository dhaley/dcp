/*
** X-Designer,
** Imperial Software Technology (IST),
** Kings Court,
** 185 Kings Road,
** Reading, 
** Berkshire,
** United Kingdom RG1 4EX.
**
** Telephone: +44 189 587055
** Fax:       +44 189 589005
** Email:     support@ist.co.uk
** Web:       http://www.ist.co.uk
*/

/*
** sccsid[] = {"@(#)dist/release/examples/demos/greptool/greptool.h	1.3"} -- 01/08/24
*/

#ifndef   _GREPTOOL_H
#define   _GREPTOOL_H

typedef struct create_command_client_data
{
	Widget  *searchfiles_widget;    /* Text widget which holds names
					   of files to be searched */
	Widget  *pattern_widget;        /* Text widget which holds
					   search pattern */
	Widget  *ignore_case_widget;    /* Option button widget */
	Widget  *show_lines_widget;     /* Option button widget */
	Widget  *show_files_widget;     /* Option button widget */
	Widget  *invert_widget;         /* Option button widget */
	Widget  *count_lines_widget;    /* Option button widget */
	Widget  *show_block_widget;     /* Option button widget */
	Widget  *command_widget;        /* Command widget */
} ccdata_t, *ccdata_p;

typedef struct run_command_client_data 
{
	Widget  *hitstring_widget;      /* Text widget to
					   display search hits */
	Widget  *errorshell_widget;     /* Root widget of
					   error dialog */
	Widget  *errorform_widget;      /* First child of root
					   of error dialog */
	Widget  *errortext_widget;      /* Text widget to
					   display errors in
					   error dialog*/
	Widget  *mainshell_widget;      /* Main shell - parent
					   of error dialog */
} rcdata_t, *rcdata_p;

#endif /* _GREPTOOL_H */
