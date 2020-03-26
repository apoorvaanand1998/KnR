#include <stdio.h>

int itoa(int n, char s[])
{
  int i = 0;
  
  if (n / 10)
    i = itoa(n / 10, s);

  if (n > -10 && n < 0) {
    s[i++] = '-';
  }
  s[i++] = ((n < 0) ? -n : n) % 10 + '0';
  s[i] = '\0';
  return i;
}

int main()
{
  int n1, n2;
  char s1[10], s2[10];

  n1 = 1234;
  itoa(n1, s1);
  printf("%s\n", s1);
  n2 = -4321;
  itoa(n2, s2);
  printf("%s\n", s2);
  return 0;
}
