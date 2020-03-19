#include <stdio.h>

#define MAXSTACK 100
#define BUFSIZE 100

double stack[MAXSTACK];
char buf[BUFSIZE];

int buf_pos = 0;
int stack_pos = 0;

void push(double el)
{
  if (stack_pos < MAXSTACK) {
    stack[stack_pos++] = el;
  }
  else {
    printf("Error : STACK FULL\n");
  }
}

double pop(void)
{
  if (stack_pos > 0) {
    return stack[--stack_pos];
  }
  else {
    printf("Error : STACK EMPTY\n");
    return 0;
  }
}

int getch(void)
{
  return (buf_pos > 0) ? buf[--buf_pos] : getchar();
}

int ungetch(int c)
{
  if (buf_pos >= BUFSIZE) {
    printf("Error : BUFFER FULL\n");
  }
  else {
    buf[buf_pos++] = c;
  }
}
  
