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
short isRealState(char s);
//Shared Variables:
char state;
short changed;
pthread_cond_t stateCond;
pthread_mutex_t stateMutex;
//Constants and Defines:
#define TRUE 1
#define FALSE 0

/* --------------------------------------------------------------------------
 * ---------------------------------- MAIN ----------------------------------
 * -------------------------------------------------------------------------- */

int main(int argc, char *argv[]) {

	printf("Hello World!\n");

	//Initialize variables:
	state = 'N';
	pthread_cond_init(&stateCond, NULL);
	pthread_mutex_init(&stateMutex, NULL);

	//Declare thread ID's:
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
 * "sense" thread senses if there has been a change in state.
 *
 * In terms of condition variables, this is a "signaling" thread.
 */
void *sense(void* arg) {
	char prevState = ' ';
	while (TRUE) {
		//Scan for a character, but don't change the global variable
		//'state' until we know the character scanned is a "real" state
		char tempState;
		scanf("%c", &tempState);
		delay(10);

		//Lock the 'state' mutex before modifying it
		pthread_mutex_lock(&stateMutex);

		if(isRealState(tempState))
			state = tempState;

		//If the state has changed, notify the stateOutput thread
		//(Note: state ^ ' ' inverts the case of the character ie: x -> X)
		if (prevState != state && prevState != (state ^ ' ')) {
			//Change the variable the waiting thread is waiting on
			changed = TRUE;
			//Signal the waiting thread (stateOutput thread)
			pthread_cond_signal(&stateCond);
		}

		//Store the current state in temp
		prevState = state;

		//Unlock the mutex
		pthread_mutex_unlock(&stateMutex);
	}
	return NULL;
}

/*
 * "isRealState" helper method checks if the state is an actual state.
 */
short isRealState(char s) {
	short real = FALSE;

	if (s == 'R' || s == 'r')//Ready
		real = TRUE;
	else if (s == 'N' || s == 'n')//Not Ready
		real = TRUE;
	else if (s == 'D' || s == 'd')//Dance mode
		real = TRUE;

	return real;
}

/*
 * "stateOutput" thread outputs a change in state.
 *
 * In terms of condition variables, this is a "waiting" thread.
 */
void *stateOutput(void* arg) {
	changed = FALSE;
	while (TRUE) {
		//Lock the mutex before waiting
		pthread_mutex_lock(&stateMutex);

		//"If" the state hasn't changed, wait. (We use a "while" statement
		//for safety, but it works the same as an if statement here.)
		while (!changed) {
			//Wait until signaled
			pthread_cond_wait(&stateCond, &stateMutex);
		}

		//Output the new state!
		printf("The state has changed! It is now: %c\n", state);

		//Update the 'changed' variable to FALSE so that we wait for the
		//next change
		changed = FALSE;

		//Unlock the mutex
		pthread_mutex_unlock(&stateMutex);
	}
	return NULL;
}

/*
 * "userInterface" thread outputs a user interface.
 */
void *userInterface(void* arg) {
	return NULL;
}
