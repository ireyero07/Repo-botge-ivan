CC = cc -std=c99 -Wall -Wextra
#CFLAGS = -O3
LDLIBS = -lm

PROGRAMS = exercise1 \
           exercise2 \
           exercise3

all: $(PROGRAMS)

permutations.o: permutations.c permutations.h
	$(CC) $(CFLAGS) -c permutations.c

search.o: search.c search.h permutations.h
	$(CC) $(CFLAGS) -c search.c

times.o: times.c times.h search.h permutations.h
	$(CC) $(CFLAGS) -c times.c

exercise1: exercise1.c search.o permutations.o
	$(CC) $(CFLAGS) -o $@ exercise1.c search.o permutations.o $(LDLIBS)

exercise2: exercise2.c search.o permutations.o
	$(CC) $(CFLAGS) -o $@ exercise2.c search.o permutations.o $(LDLIBS)

exercise3: exercise3.c times.o search.o permutations.o
	$(CC) $(CFLAGS) -o $@ exercise3.c times.o search.o permutations.o $(LDLIBS)

clean:
	rm -f *.o $(PROGRAMS)
