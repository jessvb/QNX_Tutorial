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
#include <unistd.h>		//for pause(), delay(), etc.
//Methods:
void *sense(void* arg);
void *stateOutput(void* arg);
void *userInterface(void* arg);
//Shared Variables:
char state;
//Constants and Defines:
#define TRUE 1
#define FALSE 0

/* --------------------------------------------------------------------------
 * ---------------------------------- MAIN ----------------------------------
 * -------------------------------------------------------------------------- */

int main(int argc, char *argv[]) {

	printf("Hello World!\n");

	//Initialize state:
	state = 'N';

	//Initialize thread ID's:
	pthread_t sensorThread;
	pthread_t stateOutputThread;
	pthread_t userThread;

	//Start threads:
	pthread_create(&sensorThread, NULL, sense, NULL);
	pthread_create(&stateOutputThread, NULL, stateOutput, NULL);
	pthread_create(&userThread, NULL, userInterface, NULL);

	//Wait for CTRL + c (all of the other threads will run until they
	//finish or until CTRL + c is hit)
	pause();

	//The CPU will never get here, as the other threads are in infinite
	//loops, and once CTRL + c is hit, all threads will terminate including
	//this one. To prevent this, uses boolean variables in your loops
	//(instead of constant "TRUE's"!)
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
	char temp = 'x';
	while (TRUE) {
		//Store the previous state in temp
		temp = state;

		//Scan a character into the global variable, state
		scanf("%c", &state);

		//If the state has changed, notify the stateOutput thread
		if (temp != state) {
			//notify stateOutput
		}
		delay(10);
	}
	return NULL;
}

/*
 * Thread to output a change in state.
 */
void *stateOutput(void* arg) {
	return NULL;
}

/*
 * Thread to output a user interface.
 */
void *userInterface(void* arg) {
	return NULL;
}
