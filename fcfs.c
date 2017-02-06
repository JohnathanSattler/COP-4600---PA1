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

	runFcfs();

	return;
}

void runFcfs() {

	process * temp;

	temp = processQueue;

	while (currentTime <= runTime) {
		while (temp != NULL && temp -> arrival == currentTime) {
			printf("Time %d: %s arrived\n", currentTime, temp -> name);

			if (readyQueue == NULL)
				printf("Time %d: %s selected (burst %d)\n", currentTime, temp -> name, temp -> burst);

			readyQueue = enqueue(readyQueue, temp -> name, temp -> arrival, temp -> burst, temp -> wait, temp -> turnaround);
			temp = dequeue(temp);
		}

		if (readyQueue == NULL) {
			printf("Time %d: IDLE\n", currentTime);
		} else {
			if (readyQueue -> burst == 0) {
				printf("Time %d: %s finished\n", currentTime, readyQueue -> name);

				endQueue = edit(endQueue, readyQueue, readyQueue -> wait, currentTime - readyQueue -> arrival);

				readyQueue = dequeue(readyQueue);

				if (readyQueue != NULL) {
					printf("Time %d: %s selected (burst %d)\n", currentTime, readyQueue -> name, readyQueue -> burst);
					readyQueue = edit(readyQueue, readyQueue, currentTime - readyQueue -> arrival, currentTime - readyQueue -> arrival);
				}
			}
			
			if (readyQueue != NULL && readyQueue -> burst > 0)
				readyQueue -> burst--;
		}

		currentTime++;
	}

	printf("Finished at time %d\n\n", currentTime - 1);

	printData(endQueue);

	return;
}
