#include <stdio.h>

#define linewidth 10

void push(char buf[], int c);
void empty(char buf[]);

int top = 0;

int main()
{
    char buf[linewidth];
    int c, pc = -1;
    
    while ((c = getchar()) != EOF) {
        if (c == '\n')
            continue;
        if (pc != ' ' && c == ' ') {
            empty(buf);
        }
        else {
            push(buf, c);
        }
        printf("%s\n", buf);
        pc = c;
    }
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
