/* $begin show-bytes */
#include <stdio.h>
/* $end show-bytes */
#include <stdlib.h>
#include <string.h>
/* $begin show-bytes */

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (i =0; i < len; i++)
	    printf(" %.2x", start[len-i-1]); 
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int)); 
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float)); 
}

void show_double(double x) {
    show_bytes((byte_pointer) &x, sizeof(double));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *)); 
}
/* $end show-bytes */

/*
int main(int argc, char *argv[])
{
    int val = 12345;
    show_int(val);
    //show_int(54321);
    //show_float(1.0);
    //show_double(0.0);
    //show_double(1.0);
    //show_double(12345);
    return 0;
}
*/
