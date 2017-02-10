/*
 * COP 4600
 * Group 1
 * Johnathan Sattler
 * Michael Slater
 * Christian Theriot
 */

#include "sjf.h"

void runSjf(process * head, int runFor, FILE * ofp) {

	process * temp, * node;
	int i;

	init(head, runFor);

	temp = processQueue;

	while (currentTime <= runTime) {
		temp = checkForArrivals(temp, ofp, 1);

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

		checkForIdle(ofp);

		currentTime++;
	}

	fprintf(ofp, "Finished at time %d\n\n", currentTime - 1);

	printData(endQueue, ofp);

	return;
}
