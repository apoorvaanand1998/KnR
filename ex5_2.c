#include <stdio.h>
#include <ctype.h>

#define MAXBUF 100
#define MAXARR 80

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

int getfloat(float *fp)
{
  int c, sign = 1;
  double val, exp = 1;

  while ((c = getch()) == ' ' || c == '\t')
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
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

  for (val = 0.0; isdigit(c); c = getch()) {
    val = val * 10 + (c - '0');
  }
  if (c == '.') {
    c = getch();
    for (exp = 1.0; isdigit(c); c = getch()) {
      exp *= 10;
      val = val * 10 + (c - '0');
    }
  }
  printf("%d %f %f\n", sign, val, exp);
  *fp = sign * val / exp;

  if (c != EOF)
    ungetch(c);
  return c;
}

int main()
{
  int n, i;
  float arr[MAXARR];

  for (n = 0; n < MAXARR && getfloat(&arr[n]) != EOF; n++)
    ;
  for (i = 0; i < n; i++)
    printf("%f ", arr[i]);
  return 0;
}
    
  
  
