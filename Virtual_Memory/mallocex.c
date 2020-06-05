#include <stdio.h>
#include <stdlib.h>

void foo(int n) {
    int i, *p;
  
    /* Allocate a block of n ints */
    p = (int *) malloc(n * sizeof(int));
    if (p == NULL) {
        perror("malloc");
        exit(0);
    }
  
    /* Initialize allocated block */
    for (i=0; i<n; i++) 
        p[i] = i;

  
    /* Return allocated block to the heap */
    free(p); 
}