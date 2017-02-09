#ifndef _helper_
#define _helper_

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "types.h"

void init(process * head, int runFor);
process * selectNext(process * head);
process * copyQueue(process * head);
void printData(process * head, FILE * ofp);
process * lowestBurst(process * head);
void checkForIdle(FILE * ofp);
process * checkForArrivals(process * head, FILE * ofp, int sjf);

process * processQueue;
process * endQueue;
process * readyQueue;
int runTime;
int currentTime;

#endif