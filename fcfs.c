#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "fcfs.h"
#include "queue.h"
#include "helper.h"

process * readyQueue;
int runTime;
int currentTime;

void startFcfs(process * head, int runFor) {

	process * temp;

	temp = head;
	runTime = runFor;
	currentTime = 0;

	copyQueue(temp);

	while (temp != NULL)
		temp = selectNext(temp);

	printQueue(readyQueue);

	runFcfs(head);

	return;
}

void runFcfs() {

	process * temp;

	temp = processQueue;

	while (currentTime < runTime) {
		while (temp != NULL && temp -> arrival == currentTime) {
			printf("Time %d: %s arrived\n", currentTime, temp -> name);

			if (readyQueue == NULL)
				printf("Time %d: %s selected (burst %d)\n", currentTime, temp -> name, temp -> burst);

			readyQueue = enqueue(readyQueue, temp -> name, temp -> arrival, temp -> burst);
			temp = dequeue(temp);
		}

		if (readyQueue == NULL) {
			printf("Time %d: Idle\n", currentTime);
		} else {
			if (readyQueue -> burst <= 1) {
				printf("Time %d: %s finished\n", currentTime, readyQueue -> name);

				endQueue = edit(endQueue, readyQueue, currentTime, readyQueue -> wait, currentTime - readyQueue -> arrival);

				readyQueue = dequeue(readyQueue);

				if (readyQueue != NULL) {
					printf("Time %d: %s selected (burst %d)\n", currentTime, readyQueue -> name, readyQueue -> burst);
					readyQueue = edit(readyQueue, readyQueue, currentTime, currentTime - readyQueue -> arrival, currentTime - readyQueue -> arrival);
				}
			} else if (readyQueue -> burst > 1) {
				readyQueue -> burst--;
			}
		}

		currentTime++;
	}

	printf("Finished at time %d\n\n", currentTime);

	printData(endQueue);

	return;
}
