#include <stdio.h>
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
  int type;
  char temp[MAXTOKEN];

  if (tokentype == '(') {
    dcl();
    if (tokentype != ')')
      printf("Error : Missing parentheses\n");
  }
  else if (tokentype == NAME) 
    strcpy(name, token);
  else
    printf("Error : Expression is neither a name nor a '(dcl)'\n");

  while (((type = gettoken()) == PARENS) || (type == BRACKETS)) {
    if (type == PARENS)
      strcat(out, "function returning ");
    else if (type == BRACKETS) {
      strcat(out, "array");
      strcat(out, token);
      strcat(out, " of ");
    }
  }
}

int main(void)
{
  while (gettoken() != EOF) {
    strcpy(datatype, token);
    out[0] = '\0';
    dcl();
    if (tokentype != '\n')
      printf("Syntax Error\n");
    printf("%s : %s%s\n", name, out, datatype);
  }
  return 0;
}
