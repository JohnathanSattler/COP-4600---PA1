/*
 * COP 4600
 * Group 1
 * Johnathan Sattler
 * Michael Slater
 * Christian Theriot
 */

#include "queue.h"

process * enqueue(process * head, char * name, int arrival, int burst, int wait, int turnaround) {

	process * temp, * loop;

	temp = (process *) malloc(sizeof(process));
	loop = head;

	strcpy(temp -> name, name);
	temp -> arrival = arrival;
	temp -> burst = burst;
	temp -> wait = wait;
	temp -> turnaround = turnaround;
	temp -> next = NULL;

	if (head == NULL)
		return temp;

	while (loop -> next != NULL)
		loop = loop -> next;

	loop -> next = temp;

	return head;
}

process * dequeue(process * head) {

	return head == NULL ? head : head -> next;
}

void printQueue(process * head) {

	process * temp;

	temp = head;

	while (temp != NULL) {
		printf("Name: %s, Arrival: %d, Burst: %d\n", temp -> name, temp -> arrival, temp -> burst);
		temp = temp -> next;
	}

	return;
}

process * removeNode(process * head, process * node) {

	process * temp, * last;

	temp = head;
	last = NULL;

	while (temp != NULL) {
		if (strcmp(temp -> name, node -> name) == 0) {

			if (last == NULL)
				return temp -> next;
			else {
				last -> next = temp -> next;
				return head;
			}
		}

		last = temp;
		temp = temp -> next;
	}

	return head;
}

int size(process * head) {

	process * temp;
	int i = 0;

	temp = head;

	while (temp != NULL) {
		i++;
		temp = temp -> next;
	}

	return i;
}

process * edit(process * head, process * node, int wait, int turnaround) {

	process * temp;

	temp = head;

	while (temp != NULL) {
		if (strcmp(temp -> name, node -> name) == 0) {
			temp -> wait = wait;
			temp -> turnaround = turnaround;
		}

		temp = temp -> next;
	}

	return head;
}

int indexOf(process * head, process * node) {

	process * temp;
	int i = 0;

	temp = head;

	while (temp != NULL) {
		if (strcmp(temp -> name, node -> name) == 0)
			return i;

		i++;
		temp = temp -> next;
	}

	return -1;
}

process * insertAt(process * head, process * node, int index) {

	process * temp, * last;
	int i = 0;

	temp = head;
	node -> next = temp;

	if (temp == NULL || index == 0)
		return node;

	last = temp;
	temp = temp -> next;

	while (temp != NULL) {
		if (i == index) {
			node -> next = temp;
			last -> next = node;
		}

		i++;
		last = temp;
		temp = temp -> next;
	}

	return head;
}

process * moveToEnd(process * head) {

	head = enqueue(head, head -> name, head -> arrival, head -> burst, head -> wait, head -> turnaround);
	head = dequeue(head);

	return head;
}
