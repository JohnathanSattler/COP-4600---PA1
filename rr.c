/*
 * COP 4600
 * Group 1
 * Johnathan Sattler
 * Michael Slater
 * Christian Theriot
 */

#include "rr.h"

void runRr(process * head, int runFor, int quantum, FILE * ofp) {

	process * temp;

	init(head, runFor);

	temp = processQueue;

	for (currentTime = 0; currentTime <= runTime; currentTime++) {
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

				if (readyQueue != NULL) {
					fprintf(ofp, "Time %d: %s selected (burst %d)\n", currentTime, readyQueue -> name, readyQueue -> burst);
					readyQueue = edit(readyQueue, readyQueue, readyQueue -> wait + currentQuantum, currentTime - readyQueue -> arrival);
				}

				currentQuantum = 0;
			}
			if (readyQueue != NULL && readyQueue -> burst > 0) {
				readyQueue -> burst--;
			}
		}

		checkForIdle(ofp);

		currentQuantum++;
	}

	fprintf(ofp, "Finished at time %d\n\n", currentTime - 1);

	printData(endQueue, ofp);

	return;
}
