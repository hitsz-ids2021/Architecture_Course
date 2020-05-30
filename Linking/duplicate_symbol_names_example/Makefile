CC = gcc
CFLAGS = -Wall -Og
FOOBARS = foobar2\
      foobar3\
	  foobar4\
	  foobar5\
	  foobar6\

all: $(FOOBARS)

# linker puzzles
foobar1: foo1.o bar1.o
	$(CC) $(CFLAGS) -o foobar1 foo1.o bar1.o
foobar2: foo2.o bar2.o
	$(CC) $(CFLAGS) -o foobar2 foo2.o bar2.o
foobar3: foo3.o bar3.o
	$(CC) $(CFLAGS) -o foobar3 foo3.o bar3.o show_bytes_b.c
foobar4: foo4.o bar4.o
	$(CC) $(CFLAGS) -o foobar4 foo4.o bar4.o
foobar5: foo5.o bar5.o
	$(CC) $(CFLAGS) -o foobar5 foo5.o bar5.o
foobar6: foo6.o bar6.o 
	$(CC) $(CFLAGS) -o foobar6 foo6.o bar6.o show_bytes_b.c

clean:
	rm -f $(FOOBARS) *.o *~ *.d *.so *.a *.s

