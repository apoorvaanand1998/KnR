#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

double stack[MAXSIZE];
double *stackp = stack;

void push(int n)
{
  if (stackp == stack + MAXSIZE)
    printf("Error : Stack is full\n");
  else 
    *stackp++ = n;
}

double pop(void)
{
  if (stackp == stack) 
    printf("Error : Stack is empty\n");
  else
    return *--stackp;
}

int main(int argc, char *argv[])
{
  double op2;
  char *curr_op;
  
  while (--argc > 0) {
    curr_op = *++argv;
    if (*curr_op == '+') 
      push(pop() + pop());
    else if (*curr_op == '-') {
      op2 = pop();
      push(pop() - op2);
    }
    else if (*curr_op == '*') 
      push(pop() * pop());
    else if (*curr_op == '/') {
      op2 = pop();
      if (op2 == 0)
	printf("Error : Division by zero\n");
      else
	push(pop() / op2);
    }
    else 
      push(atof(curr_op));
  }
  printf("%f\n", pop());
  return 0;
}
	
     
