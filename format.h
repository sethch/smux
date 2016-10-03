#ifndef FORMAT_H
#define FORMAT_H
#include <stdio.h>

/*
 * Displays welcome prompt upon entering.
 */
void print_smux_prompt();

/*
 * Error message when fork does not work.
 */
void print_fork_failed(); 	

/*
 * Error message when exec does not work.
 */
void print_exec_failed();

#endif
