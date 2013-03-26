/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

static int count = 1;
#define PROGRESSTIME 1

static void pretty_time(char *buf)
{
	static time_t start_time = 0;
	time_t curr_time = 0;
	int hr,minute,sec;
	if(start_time == 0)
		start_time = time(0);
	curr_time = time(0) - start_time;
	hr  = curr_time/3600;
	minute = (curr_time - hr*3600)/60;
	sec = curr_time - hr*3600 - minute*60;
	sprintf(buf, "%.2d:%.2d:%.2d", hr, minute, sec);
}

void draw_progress_bar(int percent)
{
	char a = 0x08;
	int ii, wid;
	int term_width = 80;
	int bar_width = 60;
	char buffer[80];
	static time_t start_time = 0;
	if(start_time == 0)
		start_time = time(0);
	memset(buffer, a, 80);
	write(fileno(stdout), buffer, term_width);
	if(percent > 100)
		percent = 100;
	wid = bar_width * percent/100;
	memset(buffer, ' ', term_width);
	sprintf(buffer,"%c", '|');
	memset(&buffer[1], '=', wid);
	memset(&buffer[1 + wid], ' ', bar_width - wid);
	sprintf(&buffer[59], "%c ", '|');
	sprintf(&buffer[61], "%3d%% Done", percent);
	pretty_time(&buffer[66]);
	write(fileno(stdout), buffer, term_width);
}

