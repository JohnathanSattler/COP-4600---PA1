#include "helper.h"

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
