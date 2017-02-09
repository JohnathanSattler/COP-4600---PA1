pa1: pa1.o fcfs.o sjf.o rr.o queue.o helper.o
	gcc -o pa1 pa1.o fcfs.o sjf.o rr.o queue.o helper.o

pa1.o: pa1.c pa1.h types.h queue.h fcfs.h sjf.h rr.h
	gcc -c pa1.c

queue.o: queue.c queue.h types.h
	gcc -c queue.c

helper.o: helper.c helper.h types.h queue.h
	gcc -c helper.c

fcfs.o: fcfs.c fcfs.h helper.h types.h queue.h
	gcc -c fcfs.c

sjf.o: sjf.c sjf.h helper.h types.h queue.h
	gcc -c sjf.c

rr.o: rr.c rr.h helper.h types.h queue.h
	gcc -c rr.c

clean:
	rm -f *.o pa1