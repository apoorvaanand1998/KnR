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

  while ((c = getc(stdin)) == ' ' || c == '\t')
    ;

  if (c == '(') {
    if ((c = getc(stdin)) == ')') {
      strcpy(token, "()");
      return PARENS;
    }
    else {
      ungetc(c, stdin);
      return '(';
    }
  }
  else if (c == '[') {
    for (*p++ = c; (*p++ = getc(stdin)) != ']'; )
      ;
    *p = '\0';
    return BRACKETS;
  }
  else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getc(stdin)); )
      *p++ = c;
    ungetc(c, stdin);
    *p = '\0';
    return NAME;
  }
  else
    return c;
}

int main()
{
  int type, prev_type;
  char temp[1400];
  
  while ((prev_type = gettoken()) != EOF) {
    strcpy(out, token);
    while ((type = gettoken()) != '\n') {
      if (type == PARENS || type == BRACKETS) {
	if (prev_type == '*') {
	  sprintf(temp, "(%s)", out);
	  strcat(temp, token);
	  strcpy(out, temp);
	}
	else {
	  strcat(out, token);
	}
	prev_type = type;
      }
      else if (type == '*') {
	prev_type = type;
	sprintf(temp, "*%s", out);
	strcpy(out, temp);
      }
      else if (type == NAME) {
	prev_type = type;
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
	
