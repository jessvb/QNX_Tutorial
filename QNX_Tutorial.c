/*
 * QNX Tutorial
 *
 * Author: Jessica Van Brummelen
 */

//Includes:
#include <stdlib.h>		//for EXIT_SUCCESS constant etc. (standard)
#include <stdio.h>		//for standard i/o (printf, perror)
#include <pthread.h>	//for using threads
#include <sched.h>		//for adding priorities to threads

/* --------------------------------------------------------------------------
 * ---------------------------------- MAIN ----------------------------------
 * -------------------------------------------------------------------------- */

int main(int argc, char *argv[]) {

	printf("Hello World!");

	return EXIT_SUCCESS;
}
