/* Copyright 2001,2002 Sun Microsystems, Inc. All Rights Reserved 
 * 
 * Cdlib.c - Sample C program
 *
 */

#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

struct cd_track {
  char *name; 
  int start, time;
  struct cd_track *next; };
typedef struct cd_track cd_track;

struct cd_title {
  char *name, *artist;
  int time, count;
  struct cd_track *track; 
  struct cd_title *next; 
};
typedef struct cd_title cd_title;

struct cd_library {
  int count;
  struct cd_title *first; };
typedef struct cd_library cd_library;

char *match_keyword (char keyword[], char line[])
{
  if (strncmp (keyword, line, strlen(keyword)) == 0 &&
      line[strlen(keyword)] == ' ')
    return line + strlen(keyword) + 1;
  else
    return NULL;
}

int parse_int (char **buf_pp)
{
  int value;
  sscanf (*buf_pp, "%d", &value);
  *buf_pp = strchr (*buf_pp, ' ') + 1;
  return value;
}

char *format_time (int time)
{
  static char str[12];
  sprintf (str, "%3d:%02d:%02d", time / 3600, time % 3600 / 60, time % 60);
  return str;
}

void main (int argc, char **argv)
{ char line[2048];
  cd_library my_cds;

  FILE *cd_file;
  cd_title *cd_p, *prev_cd_p, *cd_p_2;
  char cd_info_path[PATH_MAX], *lp;
  int tr;

  if (argc == 1)
    sprintf (cd_info_path, "%s/.workmandb", getenv ("HOME"));
  else
    strcpy (cd_info_path, argv[1]);

  cd_file = fopen (cd_info_path, "r");
  if (cd_file == NULL) {
    printf ("Error opening file %s\n", cd_info_path);
    exit (1); }

  my_cds.count = 0;
  my_cds.first = NULL;

  while (fgets (line, sizeof(line), cd_file) != NULL) {
    line[strlen(line) - 1] = '\0';
    if (lp = match_keyword ("tracks", line)) {
      cd_p = (cd_title *) malloc (sizeof (cd_title));

      cd_p->name = NULL;
      cd_p->artist = NULL;
      cd_p->count = parse_int (&lp);
      cd_p->track = (cd_track *)malloc (sizeof(cd_track) * cd_p->count);
      for (tr = 0; tr < cd_p->count; tr++) {
	cd_p->track[tr].start = parse_int(&lp) / 75;
	cd_p->track[tr].name = NULL; 
      }
      cd_p->time = parse_int(&lp); 
      cd_p->next = NULL;

      if (my_cds.first == NULL)
	my_cds.first = cd_p;
      else
	prev_cd_p->next = cd_p;

      prev_cd_p = cd_p;
      my_cds.count++;
      tr = 0; 
    }
    else
    if (lp = match_keyword ("cdname", line))
      cd_p->name = strdup (lp);
    else
    if (lp = match_keyword ("artist", line))
      cd_p->artist = strdup (lp);
    else
    if (lp = match_keyword ("track", line)) {
      if (tr < cd_p->count - 1) {
	cd_p->track[tr].time = 
	  cd_p->track[tr + 1].start - cd_p->track[tr].start;
	cd_p->track[tr].next = &cd_p->track[tr + 1];
      }
      else
	cd_p->track[tr].time = cd_p->time - cd_p->track[tr].start;
      cd_p->track[tr++].name = strdup (lp);
    }
  }
  
  {
    int total_time = 0, longest = 0, shortest = 0;
    char *long_title, *short_title;

    printf ("\nCD Library Statistics:\n\n");
    printf (" Titles:         %d\n\n", my_cds.count);
    for (cd_p = my_cds.first; cd_p != NULL; cd_p = cd_p->next) {
      total_time += cd_p->time;
      if (cd_p->time > longest) {
	longest = cd_p->time;
	long_title = cd_p->name;
      }
      if (cd_p->time < shortest || shortest == 0) {
	shortest = cd_p->time;
	short_title = cd_p->name;
      }
    }
    printf (" Total time:   %s\n", format_time (total_time));
    printf (" Average time: %s\n\n", format_time (total_time / my_cds.count));
    printf (" Longest CD:   %s  %s\n", format_time (longest), long_title);
    printf (" Shortest CD:  %s  %s\n", format_time (shortest), short_title);
  }
  for (cd_p = my_cds.first; cd_p != NULL; ) {
    cd_title *temp = cd_p;
    my_cds.first = temp->next;
    my_cds.count--;
    for (tr = 0; tr < temp->count; tr++)
      free (temp->track[tr].name);
    free (temp->name);
    free (temp->artist);
    free (temp->track);
    cd_p = cd_p->next;
    free (temp);
  }
}
