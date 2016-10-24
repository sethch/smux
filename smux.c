#include "format.h"
#include "smux.h"
#include "graphics.h"
#include <fcntl.h>
#define _XOPEN_SOURCE 600
#include <stdlib.h>
#define __USE_BSD 
#include <termios.h>

void sig_chld_handler(){
	int status = 40;
	wait(&status);
}

void startup(int argc, char* argv[]){
	numterms = 1;
//	updateWindow();
	int ch, rc;
	char input[150];
//	cbreak();
//	keypad(stdscr, TRUE);
	int masterfildes = posix_openpt(O_RDWR);	
	grantpt(masterfildes);
	unlockpt(masterfildes);
	char* slavename = ptsname(masterfildes);
	int fildes = open(slavename, O_RDWR);

	pid_t child = fork();

	if(child > 0){
		close(fildes);
		while (1) { 
        	// Operator's entry (standard input = terminal) 
    		write(1, "Input : ", sizeof("Input : ")); 
    		rc = read(0, input, sizeof(input)); 
    		if (rc > 0) {
        		// Send the input to the child process through the PTY 
     			write(masterfildes, input, rc); 

      			// Get the child's answer through the PTY 
      			rc = read(masterfildes, input, sizeof(input) - 1); 
      			if (rc > 0) { 
        		// Make the answer NUL terminated to display it as a string
        			input[rc] = '\0'; 
	
    	   			fprintf(stderr, "%s", input); 
      			} 
      			else { break; } 
    		} 
    		else { break; } 
  		} // End while 	
	}
	else{
		struct termios slave_orig_term_settings;
		struct termios new_term_settings;
		close(masterfildes);
		rc = tcgetattr(fildes, /*TCSANOW,*/ &new_term_settings);

		close(0);
		close(1);
		close(2);
		dup(fildes);
		dup(fildes);
		dup(fildes);

		while(1){
			rc = read(fildes, input, sizeof(input)-1);
			if(rc > 0){
				input[rc-1] = '\0';
				printf("Child received : '%s'\n", input);
			}
			else{ break; }
		}
	}
/*	
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
*/
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
