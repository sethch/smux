#ifndef SMUX_H
#define SMUX_H
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * Catches the signal SIGCHLD.
 * Waits on one child process.
 */
void sig_chld_handler();

/*
 * Called by main when smux is executed.
 * Starts smux and prints welcome prompt.
 */
void startup(int argc, char* argv[]);

/*
 * Uses fork-exec to start a new instance of shell.
 * Ran as a background process (no waitpid).
 */ 
void createShell(int argc, char* argv[]);

#endif
