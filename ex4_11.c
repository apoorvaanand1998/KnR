#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'
#define MAXGETCH 100

// ((ung_pos > 0) ? (ungetched[--ung_pos]) : (getchar()))

int getop(char s[])
{
  static int ungetched[MAXGETCH], ung_pos = 0;
  int c, i = 0;

  while ((c = s[0] = ((ung_pos > 0) ? (ungetched[--ung_pos]) : (getchar()))) == ' ' || c == '\t')
    ;
  s[1] = '\0';

  if (!isdigit(c) && c != '.')
    return c;

  if (isdigit(c))
    while (isdigit(c = s[++i] = ((ung_pos > 0) ? (ungetched[--ung_pos]) : (getchar()))))
      ;
  if (c == '.')
    while (isdigit(c = s[++i] = ((ung_pos > 0) ? (ungetched[--ung_pos]) : (getchar()))))
      ;
  s[i] = '\0';
  
  if (c != EOF)
    ungetched[ung_pos++] = c;

  return NUMBER;
}

int main()
{
  int type;
  char s[MAXGETCH];

  // try input 123 123+ yes, without space. The + gets swallowed up without static ungetched
  while ((type = getop(s)) != EOF) {
    printf("%s %d\n", s, type);
  }
  return 0;
}
