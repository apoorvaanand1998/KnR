#include <stdio.h>

#define MAXLINE 1000

int getline1(char line[], int lim);
void copy(char to[], char from[]);

int main() 
{
    int len, longlen;
    char line[MAXLINE], longline[MAXLINE];
    
    longlen = 0;
    
    while ((len = getline1(line, MAXLINE)) > 0) {
        printf("%d: %s", len, line);
        
        if (len > longlen) {
            longlen = len;
            copy(longline, line);
        }
    }
    printf("Longest line is %swith %d characters\n", longline, longlen);
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

void copy(char to[], char from[])
{
    int i = 0;
    
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}
