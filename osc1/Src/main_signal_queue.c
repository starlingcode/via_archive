#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"

/**
 *
 * Signal Queue
 *
 */

// relic of a more ambitious main state machine, modified to call simplified state machine
// dispatch task at front of queue to state machine and pop it off the queue
void mainDispatch(void) {

//	// call the state machine with that signal
//	(*main_State)(firstTask->signal);
//
//	// store the first signal
//	Task* temp = firstTask;
//
//	// shift the head pointer to the next signal
//	firstTask = temp->next;

	(*main_State)(0);

}

// signal queue linked list relics

//Task* mainCreateTask(int signal, Task* nextTask) {
//
//	queuePosition = (queuePosition + 1);
//
//	if (queuePosition >> 7 != 0) {
//		queuePosition = 0;
//	}
//
//	Task* newTask = &taskQueue[queuePosition];
//
//	// define the data and next members
//	newTask->signal  = signal;
//	newTask->next = (nextTask);
//
//	return newTask;
//
//}

//// push a signal to the front of the queue
//void mainPush(int signal) {
//
//	Task* newTask = mainCreateTask(signal, firstTask);
//
//	// shift the head pointer to the new signal
//	firstTask = newTask;
//}
//
//// add a signal to the end of the queue
//void mainRequest(int signal) {
//
//	Task* newTask = mainCreateTask(signal, &nullTask);
//
//	// point from the former last signal to the new signal
//	lastTask->next = newTask;
//
//	// shift the tail pointer to the new signal
//	lastTask = newTask;
//}
