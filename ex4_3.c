#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAXSTACK 100
#define BUFSIZE 100
#define MAXOP 50
#define NUMBER '0'

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

void ungetch(int c)
{
  if (buf_pos >= BUFSIZE) {
    printf("Error : BUFFER FULL\n");
  }
  else {
    buf[buf_pos++] = c;
  }
}

int getop(char s[])
{
  int c, d, i;

  while ((c = s[0] = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';

  if (!isdigit(c) && c != '.' && c != '-')
    return c;

  i = 0;
  if (c == '-') {
    if ((d = getch()) == ' ')
      return c;
    else {
      s[++i] = d;
      c = d;
    }
  }

  if (isdigit(c))
    while (isdigit((c = s[++i] = getch())))
      ;
  if (c == '.')
    while (isdigit((c = s[++i] = getch())))
      ;

  s[i] = '\0';

  if (c != EOF)
    ungetch(c);
  return NUMBER;
}

int main()
{
  char s[MAXOP];
  int type;
  double op2;
  
  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 == 0)
	printf("Error : DIVISION BY ZERO");
      else
	push(pop() / op2);
      break;
    case '%':
      op2 = pop();
      if (op2 == 0)
	printf("Error : MODULUS WITH ZERO");
      else
	push(fmod(pop(), op2));
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("Error : INVALID ENTRY");
      break;
    }
  }
  return 0;
}
  
