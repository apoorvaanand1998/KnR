#include <stdio.h>
#include <limits.h>
#include <string.h>

/* The version in the book cannot handle the largest negative number because
the range for signed ints is from -(2^(wordsize-1)) to (2^(wordsize-1))-1.
So when the largest negative number is converted to a positive number, i.e., 
n = -n happens, there is a overflow */

void itoa(int n, char s[])
{
  int i, j, k, c, sign, of;

  (n == INT_MIN) ? (of = 1) : (of = 0);
  if ((of == 0) && ((sign = n) < 0))
    n = -n;
  else if (of == 1) {
    n += 1;
    n = -n;
  }
  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0)
    s[i++] = '-';
  if (of == 1)
    s[0] += 1;
  s[i] = '\0';
  for (k = 0, j = strlen(s)-1; k < j; k++, j--)
    c = s[k], s[k] = s[j], s[j] = c;    
}

int main()
{
  int n1, n2;
  char s1[50], s2[50];

  n1 = -123;
  n2 = INT_MIN;
  itoa(n1, s1);
  itoa(n2, s2);
  printf("%s\n%s\n", s1, s2);
  return 0;
}
