#include <stdio.h>

#define MAXSTACK 100

double stack[MAXSTACK];
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

double top(void)
{
  if (stack_pos > 0)
    return stack[stack_pos-1];
  else {
    printf("Error : STACK EMPTY\n");
    return 0;
  }
}

void duplicate(void)
{
  if (stack_pos < MAXSTACK) 
    stack[stack_pos++] = top();
  else
    printf("Error : STACK FULL\n");
}

void swap(void)
{
  double temp1, temp2;

  temp1 = pop();
  temp2 = pop();

  push(temp1);
  push(temp2);
}

void clear(void)
{
  stack_pos = 0;
  stack[stack_pos] = '\0';
}

