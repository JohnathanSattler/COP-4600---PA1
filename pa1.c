#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "queue.h"
#include "fcfs.h"
#include "sjf.h"
#include "rr.h"

process * readFile(FILE * ifp, process * head, FILE * ofp);
int useStrToInt(char * use);
void printValues(FILE * ofp);

int processcount;
int runfor;
int use;
int quantum;

int main() {
   
	char * inputFile  = "processes.in";
	char * outputFile = "processes.out";
	FILE * ifp, * ofp;
	process * head;

	head = NULL;

	processcount = 0;
	runfor = 0;
	use = 0;
	quantum = 0;

	ifp = fopen(inputFile, "r");
	ofp = fopen(outputFile, "w");

	head = readFile(ifp, head, ofp);

	fclose(ifp);

	printValues(ofp);
	fprintf(ofp, "\n");

	switch (use) {
		case fcfs:
			startFcfs(head, runfor, ofp);
			break;

		case sjf:
			startSjf(head, runfor, ofp);
			break;

		case rr:
			startRr(head, runfor, quantum, ofp);
			break;

		default:
			fprintf(ofp, "Error: Unknown use type\n");
			break;
	}

	fclose(ofp);

	free(head);

   return 0; 
}

process * readFile(FILE * ifp, process * head, FILE * ofp) {

	char * strIn, * nameIn;
	char charIn;
	int arrivalIn, burstIn, i = 0;

	int input[4];

	input[3] = -1;

	if (ifp == NULL) {
		fprintf(ofp, "Error: File not found\n");
		return NULL;
	}

	strIn = (char *) malloc(sizeof(char) * 100);
	nameIn = (char *) malloc(sizeof(char) * 100);

	while (fscanf(ifp, "%s", strIn) != EOF) {
		if (strIn[0] == '#') {
			while (fscanf(ifp, "%c", &charIn) != EOF)
				if (charIn == '\n')
					break;

			continue;
		}

		if (strcmp(strIn, "end") == 0) {
			break;
		}

		if (strcmp(strIn, "process") == 0) {
			// name
			fscanf(ifp, "%s", strIn);
			fscanf(ifp, "%s", nameIn);

			// arrival
			fscanf(ifp, "%s", strIn);
			fscanf(ifp, "%d", &arrivalIn);

			// burst
			fscanf(ifp, "%s", strIn);
			fscanf(ifp, "%d", &burstIn);

			head = enqueue(head, nameIn, arrivalIn, burstIn, 0, -1);
			continue;
		}

		if (i >= 4) {
			fprintf(ofp, "Error: Too many arguments\n");
			return NULL;
		}

		if (strcmp(strIn, "use") == 0) {
			fscanf(ifp, "%s", strIn);
			input[i++] = useStrToInt(strIn);
		} else {
			fscanf(ifp, "%d", &input[i++]);
		}
	}

	processcount = input[0];
	runfor = input[1];
	use = input[2];
	quantum = input[3];

	free(strIn);
	free(nameIn);

	return head;
}

int useStrToInt(char * use) {

	if (strcmp(use, "fcfs") == 0) {
		return fcfs;
	} else if (strcmp(use, "sjf") == 0) {
		return sjf;
	} else if (strcmp(use, "rr") == 0) {
		return rr;
	}

	printf("Error: Unknown use type\n");
	return 0;
}

void printValues(FILE * ofp) {

	fprintf(ofp, "%d processes\n", processcount);

	fprintf(ofp, "Using ");
	switch (use) {
		case 1: // fcfs
			fprintf(ofp, "First Come First Served\n");
			break;

		case 2:
			fprintf(ofp, "Shortest Job First (Pre)\n");
			break;

		case 3:
			fprintf(ofp, "Round-Robin\n");
			fprintf(ofp, "Quantum %d\n", quantum);
			break;

		default:
			fprintf(ofp, "Unknown\n");
			break;
	}

	return;
}
