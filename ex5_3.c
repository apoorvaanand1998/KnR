#include <stdio.h>

void my_strcat(char *s, char *t)
{
  while (*s != '\0')
    s++;
  for (; (*s = *t) != '\0'; s++, t++)
    ;
}

int main()
{
  char s[10] = "forever";
  char t[10] = "whatever";

  my_strcat(s, t);
  printf("%s\n", s);
  return 0;
}
