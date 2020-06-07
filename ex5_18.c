/*
   This exercise (to me) is deceptively hard. There is
   ambiguity in the question itself. Initially, my idea
   was to add a stack to check for unbalanced parentheses,
   but after running the program in the book with input 
   errors, I realized most input errors are actually 
   covered by the K&R program, but every time an error is
   "caught" it isn't "handled" properly, which affects the 
   output of the next line (the next expression to be eva-
   luated, whether right or wrong). My modifications below
   are an attempt to "handle" the errors properly.
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
  /* 
     added (error != 1) below because when there'd
     be an error because of a missing closing par-
     enthesis, the gettoken() below would read the
     tokens of the NEXT line or tokens of the cur-
     rent line in a way it should not, and the next
     line would produce (wrong) output for the 
     previous line as well as itself. This check 
     fixes that.
  */
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

int main(void)
{
  while (gettoken() != EOF) {
    if (tokentype == NAME) {
      /* 
	 the above while loop has been added to 
	 recover from the "Syntax Error" that will
	 occur in case the tokentype != '\n',
	 in which case, gettoken() runs again and
	 again until the tokentype == NAME 
	 (i.e. until the first token is a datatype 
	 and not some other character or tokentype.
      */
      strcpy(datatype, token);
      out[0] = name[0] = '\0';
      /*
	 added name[0] here because if there was a
	 missing name, the output would be almost
	 right (for the case of missing name) but 
	 it would reuse the name from the previous
	 line. This prevents that.
      */
      dcl();
      if (tokentype != '\n') {
	printf("Syntax Error\n");
      }
      printf("%s : %s%s\n", name, out, datatype);
    }
  }
  return 0;
}
