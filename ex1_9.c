#include <stdio.h>

int main()
{
    int c, cp;
    
    cp = 0; //any value that is not a space
    
    while ((c = getchar()) != EOF) {
        if (cp == ' ' && c == ' ') 
            ;
        else {
            putchar(c);
            cp = c;
        }
    }
    
    return 0;
}
