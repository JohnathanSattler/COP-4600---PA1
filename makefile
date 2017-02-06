pa1: pa1.o fcfs.o sjf.o rr.o queue.o helper.o
	gcc -o pa1 pa1.o fcfs.o sjf.o rr.o queue.o helper.o

pa1.o: pa1.c types.h fcfs.h queue.h
	gcc -c pa1.c

queue.o: queue.c queue.h types.h
	gcc -c queue.c

helper.o: helper.c helper.h types.h queue.h
	gcc -c helper.c

fcfs.o: fcfs.c types.h fcfs.h queue.h helper.h
	gcc -c fcfs.c

sjf.o: sjf.c types.h sjf.h queue.h helper.h
	gcc -c sjf.c

rr.o: rr.c types.h rr.h queue.h helper.h
	gcc -c rr.c

clean:
	rm -f *.o pa1