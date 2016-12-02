#ifndef SMUX_H
#define SMUX_H
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>

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
 * Refreshes screen windows with updated numterms.
 */
void updateWindow();

/*
 * Deals with key presses when the "smux" key is pressed (TBD)
 */
void action(int actionnum);

/*
 * Will add a bidirectional channel for a new smux window
 */
void* addPseudo(void* arg);

/*
 * Will remove a the specified pty (parameters need to be added)
 */
void removePseudo();
#endif
