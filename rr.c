#include "rr.h"

void runRr(process * head, int runFor, int quantum, FILE * ofp) {

	process * temp;
	int currentQuantum = 0;

	init(head, runFor);

	temp = processQueue;

	while (currentTime <= runTime) {
		temp = checkForArrivals(temp, ofp, 0);

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

		checkForIdle(ofp);

		currentTime++;
		currentQuantum++;
	}

	fprintf(ofp, "Finished at time %d\n\n", currentTime - 1);

	printData(endQueue, ofp);

	return;
}
