#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100 
#define NUMBER '0' 
#define MAXLINE 1000
#define MAXVAL 100

int getop(char [], char[], int);
void push(double);
double pop(void);
int getline2(char [], int);

int sp = 0; 
double val[MAXVAL];
int line_pos;

int main(void)
{
  int type, line_len;
  double op2;
  char s[MAXOP], line[MAXLINE];

  while ((line_len = getline2(line, MAXLINE)) > 0)
    {
      while((type = getop(s, line, line_len)) != EOF)
	{
	  switch(type)
	    {
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
	      if(op2 != 0.0)
		push(pop() / op2);
	      else
		printf("error: zero divisor\n");
	      break;
	    case '\n':
	      printf("\t%.8g\n", pop());
	      break;
	    default:
	      printf("error: unknown command %s\n", s);
	      break;
	    }
	}
    }

  return 0;
}

void push(double f)
{
  if(sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
  if(sp > 0)
    return val[--sp];
  else
  {
    printf("error: stack empty\n");
    return 0.0;
  }
}

int getop(char s[], char line[], int line_len)
{
  int c, i = 0;

  while (line_pos < line_len) {
    while (((c = s[0] = line[line_pos++]) == ' ') || c == '\t')
      ;
    s[1] = '\0';
    
    if (!isdigit(c) && c != '.')
      return c;
    if (isdigit(c))
      while (isdigit(s[++i] = c = line[line_pos++]))
	;
    if (c == '.')
      while (isdigit(s[++i] = c = line[line_pos++]))
	;
    s[i] = '\0';
    line_pos--;
  return NUMBER;
  }
  return EOF;
}

int getline2(char s[], int lim)
{
  line_pos = 0;
  int c, i = 0;
  while (--lim > 0 && (((c = getchar()) != EOF) && (c != '\n')))
    s[i++] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return i;
}
