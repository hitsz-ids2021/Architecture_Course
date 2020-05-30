CC = gcc
CFLAGS = -Wall -Og

prog: main.o sum.o
	$(CC) $(CFLAGS) -o prog main.o sum.o
	$(CC) $(CFLAGS) -S main.c
	objdump -dx main.o          > main.d
	objdump -dr main.o          > main-relo.d
	objdump -dx -j .data main.o > maindata-relo.d
	readelf -s main.o	    > mainsym.d	
	objdump -dx sum.o           > sum.d
	objdump -dr sum.o           > sum-relo.d
	objdump -dx -j .data sum.o  > sumdata-relo.d
	objdump -dx prog            > prog-exe.d
	objdump -dx -j .data prog   > progdata-exe.d

clean:
	rm -f prog  *.o *~ *.d *.so *.a *.s


