#define _XOPEN_SOURCE 600
#include "format.h"
#include "smux.h"
#include "graphics.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <pty.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#define __USE_BSD 
#include <termios.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <string.h>

pthread_t pts[8];
int turn = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c;

void sig_chld_handler(){
	int status = 40;
	wait(&status);
}

void* addPseudo(void* arg){
	char* buffer = NULL;
	size_t *n = malloc(sizeof(size_t));
	int ptnum = *(int*)arg;
	int ch;
	char Name[400];
	int fdm = posix_openpt(O_RDWR);
	grantpt(fdm);
	unlockpt(fdm);
	int fds = open(ptsname(fdm), O_RDWR);
	pid_t child = fork();
	if(child == 0){
		close(fdm);
		struct termios slave_orig_term_settings; // Saved terminal settings
		struct termios new_term_settings; // Current terminal settings
		tcgetattr(fds, &slave_orig_term_settings);
		new_term_settings = slave_orig_term_settings;
		cfmakeraw(&new_term_settings);
		tcsetattr(fds, TCSANOW, &new_term_settings);
		dup2(fds, 0);
		dup2(fds, 1);
		dup2(fds, 2);
		close(fds);
		setsid();
		ioctl(0, TIOCSCTTY, 1);
		execv("/bin/bash", NULL);
	}
	else{
		newterm(NULL, stdout, stdin);
		close(fds);
		char Output[500];
		fd_set FDCopy;
		/* Setup select(). */
		char buffer[500];
		char buffer2[500];	
		/*move(win[turn].curry + 1, win[turn].currx);  	
		win[turn].curry++;
		*/
		/*if(system("stty erase '^\?'") <= 0){
			printw("system failed!");
		}*/
		while(1)
		{       /* This loop continually looks for input on the descriptors. */
			pthread_mutex_lock(&m);
			if(turn == 10){
				pthread_mutex_unlock(&m);
				break;
			}
			while(turn != ptnum){
				pthread_cond_wait(&c, &m);
			}
			pthread_mutex_unlock(&m);
			FD_ZERO(&FDCopy);
			FD_SET(0, &FDCopy);
			FD_SET(fdm, &FDCopy);
			select(fdm+1, &FDCopy, NULL, NULL, NULL);
			/* Check for output from the child. */
			if(FD_ISSET(fdm, &FDCopy)){
				memset(Output, 0, sizeof(Output));
				read(fdm, Output, sizeof(Output));
				write(1, Output, sizeof(Output));
				//printw(Output);
			}	
			/* Check if the user has entered commands. */
			if(FD_ISSET(0, &FDCopy)){
		    /* Read from keyboard. */
				memset(buffer2, 0, 500);
				fgets(buffer2, 500, stdin);
				write(fdm, buffer2, strlen(buffer2));
			}
			int i = 0;	
			//timeout(-1);
			/*memset(buffer, 0, 500);
			int x, y;
			while((ch = getch()) != 10 && i < 499){
					//buffer[i] = (char)ch;
					i++;
			}*/
			//buffer[i] = '\0';
			// termios can help set up line editing (eg.. turn backspace into deleting character)
			/*move(win[turn].curry + 1, win[turn].currx);  	
			win[turn].curry++;	
			refresh();
			*/
		}
		/*while(1){
				ch = getch();
				switch(ch){
					case KEY_ENTER:
						printw("\n");
						refresh();	
					case 269: //f5 (to remove a window)
						action(1);
					case 270: //f6 (to add a window)
						action(2);
					case 271: //f7 (switch windows) 
						action(3);
						goto threadstart;
					case 272: //f8 (end program)
						action(4);
						goto threadstart;
				}
			}*/
		}	
	return NULL; 
}

void action(int actionnum){
	int ptnum[1];
	switch(actionnum){
		case 1: // remove a window
			pthread_cancel(pts[numterms-1]);
			numterms--;
			updateWindow();
		case 2: // add a window
			ptnum[0] = numterms - 1;
			pthread_create(&pts[numterms], NULL, addPseudo, (void*)ptnum);
			numterms++;
			updateWindow();
		case 3: // switch windows
			turn = (turn + 1) % (numterms - 1);
			pthread_cond_broadcast(&c);
		case 4: // end program
			turn = 10;
			pthread_cond_broadcast(&c);
	}
}


void startup(int argc, char* argv[]){
	numterms = 1;
	//SCREEN * newterm(char *type, FILE *outfd, FILE *infd);	
	//clear();
	//initscr();
	//newterm(NULL, stdout, 
	//cbreak();
	//noecho();
	updateWindow();	
	int ptnum[1];
	ptnum[0] = 0;
	pthread_cond_init(&c, NULL);
	pthread_create(&pts[numterms-1], NULL, addPseudo, (void*)ptnum);

	for(int i = 0; i < numterms; i++){
		pthread_join(pts[i], NULL);
	}
	//endwin();
}

void updateWindow(){
	//clear();
	//initscr();
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
