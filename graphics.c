#include "graphics.h"

void sig_wnch_handler(){
	endwin();
	initscr();
	refresh();
	clear();
  
	char tmp[128];
	sprintf(tmp, "%dx%d", COLS, LINES);
	// Approximate the center
	int x = COLS / 2 - strlen(tmp) / 2;
	int y = LINES / 2 - 1;
	mvaddstr(y, x, tmp);
	refresh();
}
