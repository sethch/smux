#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <ncurses.h>

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

#endif
