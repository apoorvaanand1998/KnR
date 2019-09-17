#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b)
{
  int i, j, k, c, neg;

  i = 0;
  (n < 0) ? (neg = 1) : (neg = 0);
  if (neg)
    n = -n; //can cause overflow for min size of int
  while (n > 0) {
    if ((n%b) > 9)
      s[i++] = 'A' + (n%b) - 10;
    else
      s[i++] = (n%b)+'0';
    n /= b;
  }
  if (neg)
    s[i++] = '-';
  s[i] = '\0';
  
  for (k = 0, j = strlen(s)-1; k < j; k++, j--)
    c = s[k], s[k] = s[j], s[j] = c;
}

int main()
{
  char str[100];

  itob(-93, str, 16);
  printf("%s\n", str);
  return 0;
}
