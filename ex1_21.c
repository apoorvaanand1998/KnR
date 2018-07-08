#include <stdio.h>

#define TAB_WIDTH 8

int main() 
{
    int c, nos, ctr, i, not, lt, rs;
    
    nos = ctr = not = 0;
    
    while ((c = getchar()) != EOF) {
        if (c == '\n') { 
            nos = ctr = 0;
            putchar('\n');
        }
        else if ((nos == 0) && (c != ' ')) {
            putchar(c);
            ++ctr;
        }
        else if (c == ' ') {
            ++nos;
            ++ctr;
        }
        else if ((c != ' ') && (nos > 0)) {
            ++ctr;
            for (i = (ctr - nos); i < ctr; i++) {
                if (i % TAB_WIDTH == 0) {
                    ++not;
                    lt = i;
                }
            }
            rs = ctr - lt - 1;
            for (i = 0; i < not; i++)
                putchar('\t');
            for (i = 0; i < rs; i++)
                putchar(' ');
            putchar(c);
            nos = not = 0;
        }
    }
    return 0;
}
