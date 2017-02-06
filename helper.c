#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include "queue.h"

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
		fprintf(ofp, "%s wait %d turnaround %d", temp -> name, temp -> wait, temp -> turnaround);

		if (temp -> turnaround < 0)
			fprintf(ofp, " (process did not finish)");

		fprintf(ofp, "\n");

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
