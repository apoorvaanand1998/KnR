#include <stdio.h>
#include <string.h>

int strrindex(char s[], char t[])
{
  int len, i, j, k;
  len = strlen(s);

  for (i = len-1; i >= 0; i--) {
    for (j = i, k = 0; s[j] == t[k] && t[k] != '\0'; j++, k++) {
      ;
    }
    if (t[k] == '\0' && k > 0)
      return i;
  }
  return -1;
}

int main()
{
  char s[20] = "fantasticalfantasy";
  char t[10] = "fan";

  printf("%d\n", strrindex(s, t));
  return 0;
}
