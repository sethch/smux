#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _win_border_struct {
	chtype 	ls, rs, ts, bs, 
	 	tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {
	int windownum;
	int startx, starty;
	int height, width;
	int currx, curry;
	WIN_BORDER border;
}WIN;

WIN win[5];
//WINDOW* window[5];
size_t numterms;
//SCREEN* terms[5];

/*
 * Catches window change signal (SIGWNCH)
 * Updates terminal dimensions
 * (should try to do updates in main section)
 * copied from stackoverflow http://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
 */ 
void sig_wnch_handler();

/*
 * Master function for drawing windows
 * Will be able to draw less or more windows than current
 */
void drawWindow();

/*
 * Creates box with WIN struct params
 */
void create_box(WIN* window, bool flag);

/*
 * Initializes WIN struct parameters
 */
void init_win_params();

#endif
