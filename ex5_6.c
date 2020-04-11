#include <stdio.h>
#include <string.h>
#include <ctype.h>

// AAH! I GET IT! I DON'T WANT TO WRITE THE SAME FUNCTIONS AGAIN FULLY!
// Skipped getop and strindex, got enough practice translating
// array indices to pointers

int my_getline1(char *s, int lim) // from chapter 1
{
  int c, offset;

  for (offset = 0; offset < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++offset) {
    *(s + offset) = c;
  }
  if (c == '\n') {
    *(s + offset) = c;
    ++offset;
  }
  s[offset] = '\0';
  return offset;
}

int my_getline2(char *s, int lim) // from chapter 4
{
  int c, offset = 0;

  while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
    *(s + offset++) = c;
  }
  if (c == '\n')
    *(s + offset++) = c;
  s[offset] = '\0';
  return offset;
}

void reverse(char *s)
{
  int c, i, j;
  for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
    c = *(s + i);
    *(s + i) = *(s + j);
    *(s + j) = c;
  }
}

int atoi(char *s)
{
  int offset, n, sign;

  for (offset = 0; isspace(*(s + offset)); ++offset)
    ;
  sign = (s[offset] == '-') ? -1 : 1;
  if (*(s + offset) == '+' || *(s + offset) == '-')
    ++offset;
  for (n = 0; isdigit(*(s + offset)); ++offset)
    n = n * 10 + (*(s + offset) - '0');
  return sign * n;
}

void itoa(int n, char *s)
{
  int offset, sign;

  if ((sign = n) < 0)
    n = -n;
  offset = 0;
  do {
    *(s + offset++) = n % 10 + '0';
  } while ((n /= 10) > 0);
  s[offset] = '\0';

  if (sign < 0)
    *(s + offset++) = '-';
  s[offset] = '\0';
  reverse(s);
}

int main()
{
  char s[100];
  int lim = 99;
  char is[10];
  int n = 4224096;
  
  my_getline1(s, lim);
  printf("%s\n", s);
  my_getline2(s, lim);
  printf("%s\n", s);

  itoa(n, is);

  printf("%s\n", is);
  printf("%d\n", atoi(is));
  
  return 0;
}


  
