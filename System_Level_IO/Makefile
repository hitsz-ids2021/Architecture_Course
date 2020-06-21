CC = gcc

CSAPP_INC = .
CSAPP_SRC = .

CFLAGS = -Wall -g -Og -I $(CSAPP_INC) -I .
LDLIBS = -lpthread

PROGS =	statcheck\
	cpstdin\
	cpfile\
	hello\
	ffiles1\
	ffiles2\
	ffiles3\
	stdout\
	readdir\
	sharing1\
	sharing2\
	fdprob1

all: $(CSAPP_SRC)/csapp.o $(PROGS) 
$(PROGS): $(CSAPP_SRC)/csapp.o
$(CSAPP_SRC)/csapp.o: $(CSAPP_SRC)/csapp.c $(CSAPP_INC)/csapp.h

clean:
	rm -f $(PROGS) *.o *~
