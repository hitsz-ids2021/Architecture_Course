/* $begin foo3 */
/* foo3.c */ 
#include <stdio.h>
void show_pointer(void *x);
void f(void);

int x; 

int main()  
{
    x = 1;
    printf("Previously, x = 0x%x (&x+1) = 0x%x \n", x, *(&x+1));
    printf("The address of x and y are %p and &x+1 = %p\n", &x, &x+1);
    show_pointer((void *)&x);
    f(); 
    printf("Now, x = 0x%x  *(&x+1) = 0x%x\n", x, *(&x+1)); 
    return 0;
} 
/* $end foo3 */
 
