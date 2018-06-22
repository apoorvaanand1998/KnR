#include <stdio.h>

int getline1(char line[], int lim);

int main()
{
    char line[1000];
    int len;
    
    while ((len = getline1(line, 1000)) > 0) {
    if (len > 80)
        printf("%s", line);
    }
    
    return 0;
}

int getline1(char line[], int lim)
{
    int c, i, j;
    
    i = j = 0;
    
    while ((c = getchar()) != EOF && (c != '\n')) {
        if (i < lim - 1)
            line[j++] = c;
        ++i;
    }
    if (c == '\n') {
        if (i <= lim - 1)
            line[j++] = c;
        ++i;
    }
    line[j] = '\0';
    return i;
}

