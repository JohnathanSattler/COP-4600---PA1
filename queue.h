/*
 * COP 4600
 * Group 1
 * Johnathan Sattler
 * Michael Slater
 * Christian Theriot
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

process * enqueue(process * head, char * name, int arrival, int burst, int wait, int turnaround);
process * dequeue(process * head);
void printQueue(process * head);
process * removeNode(process * head, process * node);
int size(process * head);
process * edit(process * head, process * node, int wait, int turnaround);
int indexOf(process * head, process * node);
process * insertAt(process * head, process * node, int index);
process * moveToEnd(process * head);