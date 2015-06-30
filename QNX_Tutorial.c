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
//Methods:
void *sense(void* arg);

/* --------------------------------------------------------------------------
 * ---------------------------------- MAIN ----------------------------------
 * -------------------------------------------------------------------------- */

int main(int argc, char *argv[]) {

	printf("Hello World!\n");

	//Initialize thread ID's:
	pthread_t sensorThread;

	//Start threads:
	pthread_create(&sensorThread, NULL, sense, NULL);

	printf("Goodbye World!\n");

	return EXIT_SUCCESS;
}

/* --------------------------------------------------------------------------
 * --------------------------------- THREADS --------------------------------
 * -------------------------------------------------------------------------- */

/*
 * Thread to sense if there has been a change in state.
 */
void *sense(void* arg) {
	return NULL;
}
