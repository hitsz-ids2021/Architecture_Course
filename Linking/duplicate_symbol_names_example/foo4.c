/* $begin foo4 */
/* foo4.c */ 
#include <stdio.h>
void f(void);

int x = 15213; 
int y = 15212; 
 
int main()  
{ 
    f(); 
    printf("address of x: 0x%p, address of y: 0x%p\n", &x, &y);
    printf("x = 0x%x y = 0x%x \n", 
	   x, y); 
    return 0;
} 
/* $end foo4 */
 
