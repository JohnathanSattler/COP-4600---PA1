/*
 * COP 4600
 * Group 1
 * Johnathan Sattler
 * Michael Slater
 * Christian Theriot
 */

#ifndef _pa1_
#define _pa1_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "queue.h"
#include "fcfs.h"
#include "sjf.h"
#include "rr.h"

process * readFile(FILE * ifp, process * head, FILE * ofp);
int useStrToInt(char * use, FILE * ofp);
void printValues(FILE * ofp);

int processcount;
int runfor;
int use;
int quantum;

#endif