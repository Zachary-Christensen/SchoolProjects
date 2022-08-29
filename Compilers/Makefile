CC = gcc
CFLAGS = -I. -g -Wall
TARGETS = genCode
P1 = genCode
P1_OBJS = main.o semantics.o parser.o errorOutput.o scanner.o testScanner.o node.o printTree.o
.SUFFIXES: .c .o

all: $(TARGETS)
p: $(P1)

$(P1): $(P1_OBJS)
	$(CC) -o $@ $(P1_OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm *.o $(TARGETS)

