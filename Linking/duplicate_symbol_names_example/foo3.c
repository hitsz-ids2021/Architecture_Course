/* $begin foo3 */
/* foo3.c */ 
#include <stdio.h>
void show_pointer(void *x);
void f(void);


int y; 
int x; 

int main()  
{
    x = 1;
    y = -1;
    printf("Previously, x = 0x%x y = 0x%x \n", x, y);
    printf("The address of x and y are %p, %p, and &x+1 = %p\n", &x, &y, &x+1);
    show_pointer((void *)&x);
    f(); 
    printf("Now, x = 0x%x y = 0x%x  *(&x+1) = 0x%x\n", 
	   x, y, *(&x+1)); 
    return 0;
} 
/* $end foo3 */
 
