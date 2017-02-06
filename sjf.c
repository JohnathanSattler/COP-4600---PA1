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

void startSjf(process * head, int runFor, FILE * ofp) {

	process * temp;

	temp = head;
	runTime = runFor;
	currentTime = 0;

	copyQueue(temp);

	while (temp != NULL)
		temp = selectNext(temp);

	printQueue(readyQueue);

	runSjf(ofp);

	return;
}

void runSjf(FILE * ofp) {

	process * temp, * node;
	int i;

	temp = processQueue;

	while (currentTime <= runTime) {
		while (temp != NULL && temp -> arrival == currentTime) {
			fprintf(ofp, "Time %d: %s arrived\n", currentTime, temp -> name);

			if (readyQueue == NULL)
				fprintf(ofp, "Time %d: %s selected (burst %d)\n", currentTime, temp -> name, temp -> burst);

			readyQueue = enqueue(readyQueue, temp -> name, temp -> arrival, temp -> burst, temp -> wait, temp -> turnaround);

			node = lowestBurst(readyQueue);
			i = indexOf(readyQueue, node);

			if (i != 0) {
				readyQueue = removeNode(readyQueue, node);
				readyQueue = insertAt(readyQueue, node, 0);
				fprintf(ofp, "Time %d: %s selected (burst %d)\n", currentTime, temp -> name, temp -> burst);
			}

			temp = dequeue(temp);
		}

		if (readyQueue != NULL) {
			if (readyQueue -> burst == 0) {
				fprintf(ofp, "Time %d: %s finished\n", currentTime, readyQueue -> name);

				endQueue = edit(endQueue, readyQueue, currentTime - readyQueue -> timeRun - readyQueue -> arrival, currentTime - readyQueue -> arrival);

				readyQueue = dequeue(readyQueue);

				if (readyQueue != NULL) {
					node = lowestBurst(readyQueue);
					i = indexOf(readyQueue, node);

					if (i != 0) {
						readyQueue = removeNode(readyQueue, node);
						readyQueue = insertAt(readyQueue, node, 0);
					}

					fprintf(ofp, "Time %d: %s selected (burst %d)\n", currentTime, readyQueue -> name, readyQueue -> burst);
					readyQueue = edit(readyQueue, readyQueue, currentTime - readyQueue -> arrival, currentTime - readyQueue -> arrival);
				}
			}

			if (readyQueue != NULL && readyQueue -> burst > 0) {
				readyQueue -> burst--;
				readyQueue -> timeRun++;
			}
		}

		if (readyQueue == NULL && currentTime < runTime)
			fprintf(ofp, "Time %d: IDLE\n", currentTime);

		currentTime++;
	}

	fprintf(ofp, "Finished at time %d\n\n", currentTime - 1);

	printData(endQueue, ofp);

	return;
}
