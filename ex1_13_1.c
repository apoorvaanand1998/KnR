#include <stdio.h>

int main()
{
    int c, i, j, lwords[11];
    
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
        printf("%d ", i+1);
        for (j = 0; j < lwords[i]; j++) {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
