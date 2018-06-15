#include <stdio.h>

int main()
{
    int c, i, j, m, lwords[11];
    
    m = -1;
    
    for (i = 0; i < 11; i++)
        lwords[i] = 0;

    i = 0;
    
    while ((c = getchar()) != EOF) {
        if (c != ' ' && c != '\n' && c != '\t')
            ++i;
        else {
            i = i - 1;
            if (i < 10)
                ++lwords[i];
            else
                ++lwords[10];
            i = 0;
        }
    }
    
    for (i = 0; i < 11; i++) {
        if (lwords[i] > m)
            m = lwords[i];
    }
    
    for (j = m; j >= 1; j--) {
        for (i = 0; i < 11; i++) {
            if (lwords[i] >= j) {
                printf("%*c", i, ' ');
                printf("*");
            }
        }
        printf("\n");
    }
    return 0;
}
