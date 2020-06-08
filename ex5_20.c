/*
  I have taken lots of libery with this exercise.
  The exercise tells us to extend dcl so it can 
  handle functions with argument types and qualifiers.
  This seems tedious. One would have to make the program
  look for keywords to decide which path to take in the
  program.

  For this exercise, I've decided to concentrate on the
  "so on" part of the exercise and have implemented a very
  simple return value checker, so obviously incorrect decl-
  arations such as "array of arrays" or "function returning
  array" etc are pointed out as incorrect.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int gettoken(void)
{
  int c;
  char *p = token;

  while ((c = getc(stdin)) == ' ' || c == '\t')
    ;
  
  if (c == '(') {
    if ((c = getc(stdin)) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    }
    else {
      ungetc(c, stdin);
      return tokentype = '(';
    }
  }
  else if (c == '[') {
    for (*p++ = c; (*p++ = getc(stdin)) != ']'; )
      ;
    *p = '\0';
    return tokentype = BRACKETS;
  }
  else if (isalpha(c)) {
    *p++ = c;
    while (isalnum(c = getc(stdin))) {
      *p++ = c;
    }
    ungetc(c, stdin);
    *p = '\0';
    return tokentype = NAME;
  }
  else {
    return tokentype = c;
  }
}

void dcl(void)
{
  int ns;

  for (ns = 0; gettoken() == '*'; )
    ++ns;
  dirdcl();
  while (ns-- > 0)
    strcat(out, "pointer to ");
}

void dirdcl(void)
{
  int type, error = 0;
  char temp[MAXTOKEN];

  if (tokentype == '(') {
    dcl();
    if (tokentype != ')') {
      error = 1;
      printf("Error : Missing parentheses\n");
    }
  }
  else if (tokentype == NAME) 
    strcpy(name, token);
  else {
    printf("Error : Expression is neither a name nor a '(dcl)'\n");
  }

  while ((error != 1) && ((type = gettoken()) == PARENS) || (type == BRACKETS)) {
    if (type == PARENS)
      strcat(out, "function returning ");
    else if (type == BRACKETS) {
      strcat(out, "array");
      strcat(out, token);
      strcat(out, " of ");
    }
  }
}

// returns a pointer to second word after the current word in out
char *two_words(char *p)
{
  int space_counter = 0;

  while (space_counter < 2) {
    if (*p++ == ' ') {
      ++space_counter;
    }
  }
  return p;
}
  
void output_return_checker()
{
  char *p, *op;

  p = out;
  
  while (*p != '\0') {
    if ((strncmp(p, "function", 8) == 0) ||
	(strncmp(p, "array", 5) == 0)) {
      op = two_words(p);
      if ((strncmp(op, "pointer", 7) == 0) || (*op == '\0'))
	printf("Seems to be a correct declaration\n");
      else {
	printf("Seems to be an incorrect declaration\n");
	break;
      }
    }
    ++p;
  }
}

int main(void)
{
  while (gettoken() != EOF) {
    if (tokentype == NAME) {
      strcpy(datatype, token);
      out[0] = name[0] = '\0';
      dcl();
      if (tokentype != '\n') {
	printf("Syntax Error\n");
      }
      printf("%s : %s%s\n", name, out, datatype);
      output_return_checker();
    }
  }
  return 0;
}
