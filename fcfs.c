/*
 * COP 4600
 * Group 1
 * Johnathan Sattler
 * Michael Slater
 * Christian Theriot
 */

#include "fcfs.h"

void runFcfs(process * head, int runFor, FILE * ofp) {

	process * temp;

	init(head, runFor);

	temp = processQueue;

	for (currentTime = 0; currentTime <= runTime; currentTime++) {
		temp = checkForArrivals(temp, ofp, 0);

		if (readyQueue != NULL) {
			if (readyQueue -> burst == 0) {
				fprintf(ofp, "Time %d: %s finished\n", currentTime, readyQueue -> name);

				endQueue = edit(endQueue, readyQueue, readyQueue -> wait, currentTime - readyQueue -> arrival);

				readyQueue = dequeue(readyQueue);

				if (readyQueue != NULL) {
					fprintf(ofp, "Time %d: %s selected (burst %d)\n", currentTime, readyQueue -> name, readyQueue -> burst);
					readyQueue = edit(readyQueue, readyQueue, currentTime - readyQueue -> arrival, currentTime - readyQueue -> arrival);
				}
			}
			
			if (readyQueue != NULL && readyQueue -> burst > 0)
				readyQueue -> burst--;
		}

		checkForIdle(ofp);
	}

	fprintf(ofp, "Finished at time %d\n\n", currentTime - 1);

	printData(endQueue, ofp);

	return;
}
