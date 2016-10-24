#include "graphics.h"

void sig_wnch_handler(){
	endwin();
	initscr();
	refresh();
	clear();
	
	init_win_params();	
	for(int i = 0; i < numterms; i++){
		create_box(&win[i], TRUE);
	}
	refresh();
}


void init_win_params()
{
	assert(numterms > 0);
	for(int i = 0; i < numterms; i++){
		win[i].height = LINES;
		win[i].width = COLS/numterms;
		win[i].border.ts = ' ';
		win[i].border.bs = ' ';		
		win[i].startx = i*(COLS/numterms);
		win[i].starty = 0; 
		switch ( numterms ){
			case 1:
				win[i].border.ls = ' ';
				win[i].border.rs = ' ';
				win[i].border.tl = ' ';
				win[i].border.tr = ' ';
				win[i].border.bl = ' ';
				win[i].border.br = ' ';
				break;
			default:
				if(i == 0){
					win[i].border.ls = ' ';
					win[i].border.rs = '|';
					win[i].border.tl = ' ';
					win[i].border.tr = '|';
					win[i].border.bl = ' ';
					win[i].border.br = '|';	
				}
				else if(numterms > 2 && i < numterms - 1){
					win[i].border.ls = '|';
					win[i].border.rs = '|';
					win[i].border.tl = '|';
					win[i].border.tr = '|';
					win[i].border.bl = '|';
					win[i].border.br = '|';	
				}
				else{
					win[i].border.ls = '|';
					win[i].border.rs = ' ';
					win[i].border.tl = '|';
					win[i].border.tr = ' ';
					win[i].border.bl = '|';
					win[i].border.br = ' ';	
				}
				break;
		}
	}
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
}


