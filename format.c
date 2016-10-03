#include "format.h"

void print_smux_prompt(){
	printf("\tWelcome to Seth's Multiplexor!\n");
	printf("To use an smux instruction, preface instructions with ctrl-b.\n");
	printf("For help with hotkeys, type ctrl-b and then enter.\n");
}

void print_fork_failed(){
	printf("Fork failure, try again some other time.\n");
}

void print_exec_failed(){
	printf("Exec failed.\n");
}
