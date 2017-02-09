#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "queue.h"
#include "helper.h"

void startRr(process * head, int runFor, int quantum, FILE * ofp);
void runRr(int quantum, FILE * ofp);