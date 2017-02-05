#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct process {
	char name[100];
	int arrival;
	int burst;
	struct process * next;
} process;

void readFile(FILE * ifp);
int useStrToInt(char * use);
void printValues();
void enqueue(char * name, int arrival, int burst);
process * dequeue();
void printQueue();

process * head;
int processcount;
int runfor;
int use;
int quantum;

int main() {
   
	char * inputFile  = "processes.in";
	char * outputFile = "processes.out";
	FILE * ifp, * ofp;

	head = NULL;

	processcount = 0;
	runfor = 0;
	use = 0;
	quantum = 0;

	ifp = fopen(inputFile, "r");

	readFile(ifp);

	fclose(ifp);

	printValues();

	printf("\n");
	printQueue();

	free(head);

   return 0; 
}

void readFile(FILE * ifp) {

	char * strIn, * nameIn;
	char charIn;
	int arrivalIn, burstIn, i = 0;

	int input[4];

	input[3] = -1;

	if (ifp == NULL) {
		printf("Error: File not found\n");
		return;
	}

	strIn = (char *) malloc(sizeof(char) * 100);
	nameIn = (char *) malloc(sizeof(char) * 100);

	while (fscanf(ifp, "%s", strIn) != EOF) {

		//printf("%s\n", strIn);

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

			enqueue(nameIn, arrivalIn, burstIn);
			continue;
		}

		if (i >= 4) {
			printf("Error: Too many arguments\n");
			return;
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

	return;
}

int useStrToInt(char * use) {

	if (strcmp(use, "fcfs") == 0) {
		return 1;
	} else if (strcmp(use, "sjf") == 0) {
		return 2;
	} else if (strcmp(use, "rr") == 0) {
		return 3;
	}

	printf("Error: Unknown use type\n");
	return 0;
}

void printValues() {

	printf("%d processes\n", processcount);

	printf("Using ");
	switch (use) {
		case 1: // fcfs
			printf("First-Come, First-Served\n");
			break;

		case 2:
			printf("Shortest Job First\n");
			break;

		case 3:
			printf("Round-Robin\n");
			break;

		default:
			printf("Unknown\n");
			break;
	}

	printf("Quantum %d\n", quantum);

	return;
}

void enqueue(char * name, int arrival, int burst) {

	process * temp, * loop;

	temp = (process *) malloc(sizeof(process));
	loop = head;

	strcpy(temp -> name, name);
	temp -> arrival = arrival;
	temp -> burst = burst;
	temp -> next = NULL;

	if (head == NULL) {
		head = temp;
		return;
	}

	while (loop -> next != NULL)
		loop = loop -> next;

	loop -> next = temp;

	return;
}

process * dequeue() {

	process * temp;

	if (head == NULL)
		return head;

	temp = head;

	head = head -> next;

	return temp;
}

void printQueue() {

	process * temp;

	temp = head;

	if (temp == NULL)
		return;

	while (temp != NULL) {
		printf("Name: %s, Arrival: %d, Burst: %d\n", temp -> name, temp -> arrival, temp -> burst);
		temp = temp -> next;
	}

	return;
}
