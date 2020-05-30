CC = gcc
CFLAGS = -Wall -Og

prog2 = prog2c\
		prog2l\
		prog2r\

all: $(prog2)

# Static library linked at compile time
prog2c: main2.o addvec.o multvec.o
	$(CC) $(CFLAGS) -c main2.c addvec.c multvec.c
	ar rcs libvector.a addvec.o multvec.o
	$(CC) $(CFLAGS) -static -o prog2c main2.o libvector.a
	$(CC) $(CFLAGS) -static -o prog2c main2.o -L. -lvector

# Shared library linked at load-time
prog2l: main2.o libvector.so
	$(CC) $(CFLAGS) -o prog2l main2.o ./libvector.so
	objdump -dx main2.o          > main2-relo.d
	objdump -dx prog2l > prog2l-exe.d
	objdump -xs -j .data -j .got prog2l > prog2ldata-exe.d

# Shared library linked at run time
prog2r: dll.c
	$(CC) $(CFLAGS) -rdynamic -o prog2r dll.c -ldl

libvector.so: addvec.c multvec.c	
	$(CC) $(CFLAGS) -shared -fpic -o libvector.so addvec.c multvec.c
	objdump -xd libvector.so > libvector-relo.d
	objdump -xRr -j .data -j .got -j .got.plt -j rela.dyn -j rela.plt libvector.so > libvectordata-relo.d

clean:
	rm -f $(prog2) *.o *~ *.d *.so *.a *.s

