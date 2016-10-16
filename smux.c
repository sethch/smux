#include "format.h"
#include "smux.h"
#include "graphics.h"
#define CLEAR "\033[H\033[J"
#define CLEAR2 "\033[47m\033[0m"

void sig_chld_handler(){
	int status = 40;
	wait(&status);
}

void startup(int argc, char* argv[]){
	numterms = 1;
	updateWindow();
	int ch;
	cbreak();
	keypad(stdscr, TRUE);
	while((ch = getch()) != KEY_F(1)){
		switch ( ch ){
			case KEY_LEFT:
				numterms--;
				updateWindow();
			case KEY_RIGHT:
				numterms++;
				updateWindow();
		}
	}
}

void updateWindow(){
	clear();
	initscr();
	init_win_params();	
	for(int i = 0; i < numterms; i++){
		create_box(&win[i], TRUE);
	}
	refresh();
}

int main(int argc, char* argv[]){
	signal(SIGCHLD, sig_chld_handler);
	signal(SIGWINCH, sig_wnch_handler);
	startup(argc, argv);
	endwin();
	return 0;
}
