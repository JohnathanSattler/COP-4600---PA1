#ifndef _helper_
#define _helper_

#include "types.h"

process * selectNext(process * head);
process * copyQueue(process * head);
void printData(process * head);

process * processQueue;
process * endQueue;

#endif