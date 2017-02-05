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
	processQueue = enqueue(processQueue, node -> name, node -> arrival, node -> burst);

	return head;
}

process * copyQueue(process * head) {

	process * temp;

	temp = head;

	if (temp == NULL)
		return temp;

	while (temp != NULL) {
		endQueue = enqueue(endQueue, temp -> name, temp -> arrival, temp -> burst);
		temp = temp -> next;
	}

	return head;
}

void printData(process * head) {

	process * temp;

	temp = head;

	if (temp == NULL)
		return;

	while (temp != NULL) {
		printf("%s wait %d turnaround %d\n", temp -> name, temp -> wait, temp -> turnaround);
		temp = temp -> next;
	}

	return;
}