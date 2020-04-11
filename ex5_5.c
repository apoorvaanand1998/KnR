#include <stdio.h>

char *my_strncpy(char *s, char *ct, int n)
{
  int offset, pad;

  offset = pad = 0;

  while (offset < n) {
    if (*(ct + offset) == '\0') {
      pad = 1;
      break;
    }
    
    *(s + offset) = *(ct + offset);
    offset++;
  }
  s[offset] = '\0';

  if (pad) {
    while (offset++ < n) {
      *(s + offset) = '\0';
    }
  }
  return s;
}

char *my_strncat(char *s, char *ct, int n)
{
  int offset = 0;

  while (*s++ != '\0')
    ;
  s--;

  // above code is ugly should probably use strlen but
  // did it for didatic purposes

  while (offset < n) {
    if (*(ct + offset) == '\0') {
      break;
    }
    *(s + offset) = *(ct + offset);
    offset++;
  }
  s[offset] = '\0';

  return s;
}

int my_strncmp(char *cs, char *ct, int n)
{
  int offset = 0;

  while (offset < n) {
    if (*(cs + offset) != *(ct + offset))
      return (*(cs + offset) - *(ct + offset));
    offset++;
  }
  return 0;
}

int main()
{
  char s[100] = "";
  char t[100] = "hey are you gonna copy this?";
  char at[100] = "hey";

  char a[5] = "abc";
  char b[5] = "b";
  char c[5] = "c";
  char d[5] = "a";
  
  my_strncpy(s, t, 15);
  printf("%s\n", s);
  
  my_strncpy(s, at, 15);
  printf("%s\n", s);
  
  my_strncat(t, at, 6);
  printf("%s\n", t);

  printf("%d\n", my_strncmp(b, c, 2));
  printf("%d\n", my_strncmp(c, b, 2));
  printf("%d\n", my_strncmp(a, d, 1));
  printf("%d\n", my_strncmp(a, d, 5));
  
  return 0;
}
      
