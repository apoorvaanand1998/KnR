#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

char token[MAXTOKEN];
char out[1000];

int gettoken(void)
{
  int c;
  char *p = token;

  while ((c = getc()) == ' ' || c == '\t')
    ;

  if (c == '(') {
    if ((c = getc()) == ')') {
      strcpy(token, "()");
      return PARENS;
    }
    else {
      ungetc(c);
      return '(';
    }
  }
  else if (c == '[') {
    for (*p++ = c; (*p++ = getc()) != ']'; )
      ;
    *p = '\0';
    return BRACKETS;
  }
  else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getc()); )
      *p++ = c;
    ungetc(c);
    *p = '\0';
    return NAME;
  }
  else
    return c;
}

int main()
{
  int type;
  char temp[MAXTOKEN];
  
  while (gettoken() != EOF) {
    strcpy(out, token);
    while ((type = gettoken()) != '\n') {
      if (type == PARENS || type == BRACKETS) {
	strcat(out, token);
      }
      else if (type == '*') {
	sprintf(temp, "(*%s)", out);
	strcpy(out, temp);
      }
      else if (type == NAME) {
	sprintf(temp, "%s %s", token, out);
	strcpy(out, temp);
      }
      else {
	printf("Invalid input at %s\n", token);
      }
    }
    printf("%s\n", out);
  }
  return 0;
}
	
