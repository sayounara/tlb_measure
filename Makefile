CC=gcc
CFLAGS=-g -Wall -O0

all: tlb_bench

tlb_bench: tlb_bench.o
	$(CC) $(CFLAGS) -o $@ tlb_bench.o

.PHONY: clean
clean:
	rm -f *.o  tlb_bench

.c.o:
	$(CC) -c $(CFLAGS) $<
