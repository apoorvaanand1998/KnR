#include <stdio.h>

#define linewidth 5

void push(char buf[], int c);
void empty(char buf[]);

int top = 0;

int main()
{
    char buf[linewidth];
    push(buf, 'a');
    push(buf, ' ');
    push(buf, 'c');
    printf("%s\n", buf);
    empty(buf);
    push(buf, 'd');
    push(buf, 'u');
    printf("%s\n", buf);
    empty(buf);
    printf("tis empty? %s\n", buf);
    return 0;
}

void push(char buf[], int c)
{
    extern int top;
    
    buf[top++] = c;
    buf[top] = '\0';
}

void empty(char buf[])
{
    extern int top;
    
    top = 0;
    buf[top] = '\0';
}
