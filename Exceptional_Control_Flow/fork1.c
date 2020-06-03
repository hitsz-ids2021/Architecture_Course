#include "csapp.h"

/* $begin fork1 */
int main() 
{
    int x = 1;

    if (Fork() == 0)
	printf("p1: x=%d\n", ++x);  
    printf("p2: x=%d\n", --x);    
    exit(0);
}
/* $end fork1 */

