#include <stdio.h>

int main()
{
    int c, n1, n2, n3;
    
    n1 = n2 = n3 = 0;
    
    while ((c = getchar()) != EOF) {
        if (c == ' ')
            ++n1;
        if (c == '\t')
            ++n2;
        if (c == '\n')
            ++n3;
    }
        
        printf("The number of blanks = %d", n1);
        printf("The number of tabs = %d", n2);
        printf("The number of newlines = %d", n3);
        
        return 0;
}
