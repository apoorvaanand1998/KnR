#include <stdio.h>

int getline1(char line[], int lim);

int main()
{
    char line[1000];
    int len, i;
    
    while ((len = getline1(line, 1000)) > 0) {
        for (i = len - 1; ((line[i] == ' ') || (line[i] == '\t') || (line[i] == '\n')); --i) 
            ;
        line[++i] = '\n';
        line[++i] = '\0';
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
