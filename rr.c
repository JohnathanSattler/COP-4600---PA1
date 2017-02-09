#include "rr.h"

void startRr(process * head, int runFor, int quantum, FILE * ofp) {

	process * temp;

	temp = head;
	runTime = runFor;
	currentTime = 0;

	copyQueue(temp);

	while (temp != NULL)
		temp = selectNext(temp);

	runRr(quantum, ofp);

	return;
}

void runRr(int quantum, FILE * ofp) {

	process * temp;
	int currentQuantum = 0;

	temp = processQueue;

	while (currentTime <= runTime) {
		while (temp != NULL && temp -> arrival == currentTime) {
			fprintf(ofp, "Time %d: %s arrived\n", currentTime, temp -> name);

			if (readyQueue == NULL)
				fprintf(ofp, "Time %d: %s selected (burst %d)\n", currentTime, temp -> name, temp -> burst);

			readyQueue = enqueue(readyQueue, temp -> name, temp -> arrival, temp -> burst, temp -> wait + currentQuantum, temp -> turnaround);

			temp = dequeue(temp);
		}

		if (readyQueue != NULL) {
			if (currentQuantum == quantum && readyQueue -> burst > 0) {
				if (readyQueue -> next != NULL && readyQueue -> next -> arrival + readyQueue -> next -> wait != currentTime)
					readyQueue -> next -> wait += currentQuantum;

				readyQueue = moveToEnd(readyQueue);

				fprintf(ofp, "Time %d: %s selected (burst %d)\n", currentTime, readyQueue -> name, readyQueue -> burst);

				currentQuantum = 0;
			}
			
			if (readyQueue -> burst == 0) {
				fprintf(ofp, "Time %d: %s finished\n", currentTime, readyQueue -> name);

				endQueue = edit(endQueue, readyQueue, readyQueue -> wait, currentTime - readyQueue -> arrival);

				readyQueue = dequeue(readyQueue);

				currentQuantum = 0;

				if (readyQueue != NULL) {
					fprintf(ofp, "Time %d: %s selected (burst %d)\n", currentTime, readyQueue -> name, readyQueue -> burst);
					readyQueue = edit(readyQueue, readyQueue, readyQueue -> wait + currentQuantum, currentTime - readyQueue -> arrival);
				}
			}
			if (readyQueue != NULL && readyQueue -> burst > 0) {
				readyQueue -> burst--;
			}
		}

		if (readyQueue == NULL && currentTime < runTime)
			fprintf(ofp, "Time %d: IDLE\n", currentTime);

		currentTime++;
		currentQuantum++;
	}

	fprintf(ofp, "Finished at time %d\n\n", currentTime - 1);

	printData(endQueue, ofp);

	return;
}
