#include <stdio.h>

#define TAB_WIDTH 8

int main()
{
    int c, x, i = 0;
    
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            putchar('\n');
            i = 0;
        }
        
        else if (c == '\t') {
            x = (TAB_WIDTH - (i % TAB_WIDTH));
            
            for (int j = 0; j < x ; j++) {
                putchar(' ');
                i++;
            }
        }
            
        else {
            putchar(c);
            i++;
        }
    }
    
    return 0;
}
