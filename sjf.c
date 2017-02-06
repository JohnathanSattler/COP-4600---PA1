#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "sjf.h"
#include "queue.h"
#include "helper.h"

process * readyQueue;
int runTime;
int currentTime;

void startSjf(process * head, int runFor) {

	process * temp;

	temp = head;
	runTime = runFor;
	currentTime = 0;

	copyQueue(temp);

	while (temp != NULL)
		temp = selectNext(temp);

	printQueue(readyQueue);

	runSjf(head);

	return;
}

void runSjf() {

	process * temp, * node;
	int i;

	temp = processQueue;

	while (currentTime < runTime) {
		while (temp != NULL && temp -> arrival == currentTime) {
			printf("Time %d: %s arrived\n", currentTime, temp -> name);

			readyQueue = enqueue(readyQueue, temp -> name, temp -> arrival, temp -> burst);

			if (temp -> arrival == readyQueue -> arrival && temp -> burst < readyQueue -> burst) {
				printf("Time %d: %s selected (burst %d)\n", currentTime, temp -> name, temp -> burst);
				while (strcmp(temp -> name, readyQueue -> name) != 0) {
					readyQueue = enqueue(readyQueue, readyQueue -> name, readyQueue -> arrival, readyQueue -> burst);
					readyQueue = dequeue(readyQueue);
				}
			}

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
					node = lowestBurst(readyQueue);
					i = indexOf(readyQueue, node);

					if (i != 0) {
						readyQueue = removeNode(readyQueue, node);
						readyQueue = insertAt(readyQueue, node, 0);
					}

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
