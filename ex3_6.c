#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int min)
{
  int i, sign, j, k, temp;
  
  i = 0;
  (n < 0) ? (sign = 1) : (sign = 0);
  
  if (sign)
    n = -n; //can cause overflow
  while (n > 0) {
    s[i++] = n % 10 + '0';
    n /= 10;
  }
  if (sign)
    s[i++] = '-';
  s[i] = '\0';

  while (strlen(s) < min) {
    s[i++] = ' ';
  }
  s[i] = '\0';

  for (k = 0, j = strlen(s)-1; k < j; k++, j--) {
    temp = s[k], s[k] = s[j], s[j] = temp;
  }
}

int main()
{
  char s[100];

  itoa(-69, s, 10);
  printf("%s\n", s);

  return 0;
}
  
