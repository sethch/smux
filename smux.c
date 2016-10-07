#include "format.h"
#include "smux.h"
#define CLEAR "\033[H\033[J"
#define CLEAR2 "\033[47m\033[0m"
#define CURSOR1 "\033[H
#define CURSOR2 "\033[

void sig_chld_handler(){
	int status = 40;
	wait(&status);
}

void startup(int argc, char* argv[]){
	createShell(argc, argv);
	print_smux_prompt();		
}

void createShell(int argc, char* argv[]){
	pid_t child = fork();
	if(child < 0){
		print_fork_failed();
		exit(50);
	}
	else if(child == 0){
		//execvp("/bin/bash", argv+1);
		print_exec_failed();
		exit(50);
	}
}

int main(int argc, char* argv[]){
	signal(SIGCHLD, sig_chld_handler);
	startup(argc, argv);	
	return 0;
}
