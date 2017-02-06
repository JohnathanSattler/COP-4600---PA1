#include "types.h"

process * enqueue(process * head, char * name, int arrival, int burst);
process * dequeue(process * head);
void printQueue(process * head);
process * removeNode(process * head, process * node);
int size(process * head);
process * edit(process * head, process * node, int end, int wait, int turnaround);
int indexOf(process * head, process * node);
process * insertAt(process * head, process * node, int index);