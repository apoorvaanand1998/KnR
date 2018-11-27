#include <stdio.h>
#include <math.h>

int main()
{
  char s[1000];
  int c, i, j, result;

  i = result = 0;
  
  while ((c = getchar()) != EOF) {
    if (c == '\n')
      break;
    s[i++] = c;
  }
  s[i] = '\0';

  for (j = 0; j < i; j++) {
    if (s[j] >= '0' && s[j] <= '9') {
      result += pow(16, i - j - 1) * (s[j] - '0');
    }
    else if (s[j] == 'a' || s[j] == 'A')
      result = result + pow(16, i - j - 1) * 10;
    else if (s[j] == 'b' || s[j] == 'B')
      result = result + pow(16, i - j - 1) * 11;
    else if (s[j] == 'c' || s[j] == 'C')
      result = result + pow(16, i - j - 1) * 12;
    else if (s[j] == 'd' || s[j] == 'D')
      result = result + pow(16, i - j - 1) * 13;
    else if (s[j] == 'e' || s[j] == 'E')
      result = result + pow(16, i - j - 1) * 14;
    else if (s[j] == 'f' || s[j] == 'F')
      result = result + pow(16, i - j - 1) * 15;
  }
  printf("Result = %d\n", result);
  return 0;
}
