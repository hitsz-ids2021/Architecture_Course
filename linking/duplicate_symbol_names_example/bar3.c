/* $begin bar3 */
/* bar3.c */ 
#include <stdio.h>
void show_double(double x);
double x; 
 
void f()  
{
    x = 2.0;
    printf("In bar3.c , double x: "); 
    show_double(x);
} 
/* $end bar3 */
 
