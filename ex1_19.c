#include <stdio.h>

int getline1(char line[], int lim);
void reverse(char s[]);

int main()
{
    char line[1000];
    
    while (getline1(line, 1000) > 0) {
        reverse(line);
        printf("%s\n", line);
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

void reverse(char s[]) 
{
    int i, j;
    char temp;
    
    //finds the length of the character array
    for (i = 0; s[i] != '\0'; ++i)
        ;
    --i;
    
    //removes newline character if present
    if (s[i] == '\n') {
        s[i] = '\0';
        --i;
    }
    
    for (j = 0; j < i; j++) {
        temp = s[j];
        s[j] = s[i];
        s[i] = temp;
        --i;
    }
}
