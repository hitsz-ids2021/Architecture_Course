/* $begin foo6 */
/* foo6.c */ 
#include <stdio.h>
void p2(void);
void  show_bytes(unsigned char *start, size_t len);

typedef struct
{
    int x;
    double y;
}s;

 s s1;
int main()  
{
    s1.x = 1;
    s1.y = 2.0;
    printf("Previously, struct s1's element x = %d, y = %lf\n", s1.x, s1.y);
    printf("The binary of struct is:\n");
    show_bytes((unsigned char *)&s1, sizeof(s));

    p2();
    printf("Now, struct s1's element x = %d, y = %lf\n", s1.x, s1.y);
    printf("The binary of struct is:\n");
    show_bytes((unsigned char *)&s1, sizeof(s));
    return 0;
}  
/* $end foo6 */
