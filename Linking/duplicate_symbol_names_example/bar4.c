/* $begin bar4 */
/* bar4.c */ 
#include <stdio.h>
void show_bytes(unsigned char* start, size_t len);
double x; 
 
void f()  
{ 
    x = 2.0; 
    double y = 2.0;
    printf("doulbe 2.0's binary representation: \n");
    show_bytes((unsigned char*)&y, sizeof(y));
} 
/* $end bar4 */
 
