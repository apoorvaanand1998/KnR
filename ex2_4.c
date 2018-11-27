#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main()
{
  char s1[101] = "aabccdebcde";
  char s2[10] = "ab";
  squeeze(s1, s2);
  printf("%s\n", s1);
  return 0;
}

void squeeze(char s1[], char s2[])
{
  int i, j, k, c1, c2;

  i = j = k = 0;

  while ((c1 = s2[j++]) != '\0') {
    while ((c2 = s1[i++]) != '\0') {
      if (c1 != c2) {
	s1[k++] = s1[i];
      }
    }
  }
  s1[k] = '\0';
}
  
