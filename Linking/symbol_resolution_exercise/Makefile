# swap.c, m.c
swap: swap.o m.o
	$(CC) $(CFLAGS) -c swap.c
	$(CC) $(CFLAGS) -c m.c
	objdump -t swap.o		> swapsym.d
	objdump -t m.o 		    > msym.d
clean:
	rm -f swap *.o *~ *.d *.so *.a *.s

