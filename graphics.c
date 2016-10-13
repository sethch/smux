#include "graphics.h"

void sig_wnch_handler(){
	endwin();
	initscr();
	refresh();
	clear();
	
	init_win_params(win);	
	create_box(win, TRUE);
	refresh();
}


void init_win_params(WIN *window)
{
	window->height = LINES-1;
	window->width = COLS/2;
	window->starty = 0;	
	window->startx = 0;

	window->border.ls = ' ';
	window->border.rs = '|';
	window->border.ts = ' ';
	window->border.bs = ' ';
	window->border.tl = ' ';
	window->border.tr = '+';
	window->border.bl = ' ';
	window->border.br = '+';

}

void create_box(WIN *window, bool flag)
{	int i, j;
	int x, y, w, h;

	x = window->startx;
	y = window->starty;
	w = window->width;
	h = window->height;

	if(flag == TRUE)
	{	mvaddch(y, x, window->border.tl);
		mvaddch(y, x + w, window->border.tr);
		mvaddch(y + h, x, window->border.bl);
		mvaddch(y + h, x + w, window->border.br);
		mvhline(y, x + 1, window->border.ts, w - 1);
		mvhline(y + h, x + 1, window->border.bs, w - 1);
		mvvline(y + 1, x, window->border.ls, h - 1);
		mvvline(y + 1, x + w, window->border.rs, h - 1);

	}
	else{
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
	}			
	refresh();

}

void testfunc(){
	win = malloc(sizeof(WIN));	
	initscr();
	init_win_params(win);
	create_box(win, TRUE);	
	while(1){}
	free(win);
	endwin();
}
