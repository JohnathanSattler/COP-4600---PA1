/*
 * COP 4600
 * Group 1
 * Johnathan Sattler
 * Michael Slater
 * Christian Theriot
 */

#include "helper.h"

void init(process * head, int runFor) {

	process * temp;

	temp = head;
	runTime = runFor;
	currentTime = 0;

	copyQueue(temp);

	while (temp != NULL)
		temp = selectNext(temp);

	return;
}

process * selectNext(process * head) {

	process * temp, * node;

	temp = head;
	node = NULL;

	if (temp == NULL)
		return NULL;

	while (temp != NULL) {
		if (node == NULL)
			node = temp;
		else
			if (temp -> arrival < node -> arrival)
				node = temp;

		temp = temp -> next;
	}

	head = removeNode(head, node);
	processQueue = enqueue(processQueue, node -> name, node -> arrival, node -> burst, node -> wait, node -> turnaround);

	return head;
}

process * copyQueue(process * head) {

	process * temp;

	temp = head;

	if (temp == NULL)
		return temp;

	while (temp != NULL) {
		endQueue = enqueue(endQueue, temp -> name, temp -> arrival, temp -> burst, temp -> wait, temp -> turnaround);
		temp = temp -> next;
	}

	return head;
}

void printData(process * head, FILE * ofp) {

	process * temp;

	temp = head;

	if (temp == NULL)
		return;

	while (temp != NULL) {
		if (temp -> turnaround < 0)
			fprintf(ofp, "%s did not finish\n", temp -> name);
		else
			fprintf(ofp, "%s wait %d turnaround %d\n", temp -> name, temp -> wait, temp -> turnaround);

		temp = temp -> next;
	}

	return;
}

process * lowestBurst(process * head) {

	process * temp, * node;

	temp = head;
	node = NULL;

	if (temp == NULL)
		return temp;

	while (temp != NULL) {
		if (node == NULL)
			node = temp;
		else
			if (temp -> burst < node -> burst)
				node = temp;

		temp = temp -> next;
	}

	return node;
}

process * checkForArrivals(process * head, FILE * ofp, int sjf) {

	process * temp, * node;
	int i;

	temp = head;

	while (temp != NULL && temp -> arrival == currentTime) {
		fprintf(ofp, "Time %d: %s arrived\n", currentTime, temp -> name);

		if (readyQueue == NULL)
			fprintf(ofp, "Time %d: %s selected (burst %d)\n", currentTime, temp -> name, temp -> burst);

		readyQueue = enqueue(readyQueue, temp -> name, temp -> arrival, temp -> burst, temp -> wait + currentQuantum, temp -> turnaround);

		if (sjf) {
			node = lowestBurst(readyQueue);
			i = indexOf(readyQueue, node);

			if (i != 0) {
				readyQueue = removeNode(readyQueue, node);
				readyQueue = insertAt(readyQueue, node, 0);
				fprintf(ofp, "Time %d: %s selected (burst %d)\n", currentTime, temp -> name, temp -> burst);
			}
		}

		temp = dequeue(temp);
	}

	return temp;
}

void checkForIdle(FILE * ofp) {

	if (readyQueue == NULL && currentTime < runTime)
			fprintf(ofp, "Time %d: IDLE\n", currentTime);

	return;
}
