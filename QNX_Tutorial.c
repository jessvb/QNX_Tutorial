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
void *stateOutput(void* arg);
void *userInterface(void* arg);

/* --------------------------------------------------------------------------
 * ---------------------------------- MAIN ----------------------------------
 * -------------------------------------------------------------------------- */

int main(int argc, char *argv[]) {

	printf("Hello World!\n");

	//Initialize thread ID's:
	pthread_t sensorThread;
	pthread_t stateOutputThread;
	pthread_t userThread;

	//Start threads:
	pthread_create(&sensorThread, NULL, sense, NULL);
	pthread_create(&stateOutputThread, NULL, stateOutput, NULL);
	pthread_create(&userThread, NULL, userInterface, NULL);

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

/*
 * Thread to output a change in state.
 */
void *stateOutput(void* arg){
	return NULL;
}

/*
 * Thread to output a user interface.
 */
void *userInterface(void* arg){
	return NULL;
}
