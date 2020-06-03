/* $begin foo4 */
/* foo4.c */ 
#include <stdio.h>
typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, size_t len);
void f(void);

int x = 1; 
int y = -1; 
 
int main()  
{
    printf("Previouly, the address of x and y are %p, %p \n", &x, &y);
    printf("x = 0x%x y = 0x%x \n", x, y); 
    show_bytes((byte_pointer)&x, sizeof(int));
    f(); 
    printf("x = 0x%x y = 0x%x \n", x, y);
    show_bytes((byte_pointer)&x, sizeof(int));
    show_bytes((byte_pointer)&y, sizeof(int));
    return 0;
} 
/* $end foo4 */
 
