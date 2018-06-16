#include <stdio.h>

int main() {
    int c, i, j, m, fc[26];
    
    for (i = 0; i < 26; i++)
        fc[i] = 0;
    
    while ((c = getchar()) != EOF) {
        if (c >= 'a' && c <= 'z') {
            ++fc[c - 'a'];
        }
    }
    
    
     for (i = 0; i < 26; i++)
        printf("fc[%c] = %d\n", (char)i + 'a', fc[i]);
    
    
    for (i = 0; i < 26; i++) 
        if (fc[i] > m)
            m = fc[i];
    
        
    for (j = m; j >= 1; j--) {
        for (i = 0; i < 26; i++) {
            if (fc[i] >= j) {
                printf("%*c", i - 1, ' ');
                printf("*");
            }
        }
        printf("\n");
    }
    
    return 0;
}
