#include <stdio.h>
#include <ctype.h>

#define MAXBUF 100
#define ARRSIZE 80

int buf[MAXBUF], buf_pos = 0;

int getch(void)
{
  return (buf_pos > 0) ? (buf[--buf_pos]) : getchar();
}

void ungetch(int c)
{
  if (buf_pos < MAXBUF)
    buf[buf_pos++] = c;
  else
    printf("Error : BUFFER FULL\n");
}

int getint(int *ip)
{
  int c, sign = 1;

  while ((c = getch()) == ' ' || c == '\t')
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);
    return 0;
  }
  if (c == '+' || c == '-') {
    sign = (c == '-') ? -1 : 1;
    c = getch();
    if (!isdigit(c)) {
      ungetch((sign < 0) ? '-' : '+');
      return 0;
    }
  }


  for (*ip = 0; isdigit(c); c = getch()) {
    *ip = *ip * 10 + (c - '0');
  }

  *ip *= sign;

  if (c != EOF)
    ungetch(c);
  return c;
}

int main()
{
  int arr[ARRSIZE], n, i;

  for (n = 0; n < ARRSIZE && getint(&arr[n]) != EOF; n++)
    ;
  for (i = 0; i < n; i++)
    printf("%d ", arr[i]);
  return 0;
}
  
  
