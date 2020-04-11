#include <stdio.h>
#include <string.h>

int strend(char *s, char *t)
{
  size_t ls = strlen(s);
  size_t lt = strlen(t);

  if (ls < lt)
    return 0;
  s += (ls - lt);
  while (*s++ == *t++)
    if (*s == '\0')
      return 1;
  return 0;
}

int main()
{
  char *s = "forever";
  char *t = "forever";

  printf("%d\n", strend(s, t));
  return 0;
}
