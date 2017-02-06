#ifndef _types_
#define _types_

typedef enum useType {
	fcfs = 1,
	sjf,
	rr
} useType;

typedef struct process {
	char name[100];
	int arrival;
	int burst;
	int wait;
	int turnaround;
	int timeRun;
	struct process * next;
} process;

#endif