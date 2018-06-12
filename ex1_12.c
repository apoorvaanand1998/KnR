#include <stdio.h>

int main()
{
    int c, cp;
    
    cp = 0;
    
    while ((c = getchar()) != EOF) {
        if ((c == '\t' || c == ' ' || c == '\n') && (cp != '\n')) {
            putchar('\n');
            cp = '\n';
        }
        else if ((c == '\t' || c == ' ' || c == '\n') && (cp == '\n'))
            ;
        else {
            putchar(c);
            cp = c;
        }
    }
    return 0;
}
