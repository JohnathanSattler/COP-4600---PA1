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

int processcount;
int runfor;
int use;
int quantum;

int main() {
   
	char * inputFile  = "processes.in";
	char * outputFile = "processes.out";
	FILE * ifp, * ofp;

	processcount = 0;
	runfor = 0;
	use = 0;
	quantum = 0;

	ifp = fopen(inputFile, "r");

	readFile(ifp);

	fclose(ifp);

	printValues();

   return 0; 
}

void readFile(FILE * ifp) {

	char * strIn;
	char charIn;
	int intIn, i = 0;

	int input[4];

	input[3] = -1;

	if (ifp == NULL) {
		printf("Error: File not found\n");
		return;
	}

	strIn = (char *) malloc(sizeof(char) * 100);

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
			fscanf(ifp, "%s", strIn);

			// arrival
			fscanf(ifp, "%s", strIn);
			fscanf(ifp, "%d", &intIn);

			// burst
			fscanf(ifp, "%s", strIn);
			fscanf(ifp, "%d", &intIn);
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

	printf("==================================================\n");
	printf("\tprocesscount\t: %d\n", processcount);
	printf("\trunfor\t\t: %d\n", runfor);
	printf("\tuse\t\t: %d (fcfs = 1, sjf = 2, rr = 3)\n", use);
	printf("\tquantum\t\t: %d\n", quantum);
	printf("==================================================\n");

	return;
}
