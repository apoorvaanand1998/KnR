#include <stdio.h>

int main()
{
  int i = 0;
  char s[1000];
  int lim = 1000;
  int c;
  
  while (i < lim-1) {
    c = getchar();
    if (c == EOF)
      break;
    if (c == '\n')
      break;
    s[i++] = c;
  }
  s[i] = '\0';
  printf("%s\n", s);
  
  return 0;
}
