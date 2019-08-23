#include <stdio.h>

void expand(char s1[], char s2[])
{
  int i, j, k;

  for (i = 0; s1[i] != '\0'; i++) {
    if (((i == 0) && (s1[i] == '-')) || (s1[i+1] == '\0' && s1[i] == '-')) {
      s2[j++] = '-';
    }
    else if (((s1[i] >= 'a') && (s1[i] <= 'z') && (s1[i+1] == '-')) ||
	((s1[i] >= 'A') && (s1[i] <= 'Z') && (s1[i+1] == '-')) ||
	((s1[i] >= '0') && (s1[i] <= '9') && (s1[i+1] == '-'))) {
      k = 0;
      do {
	  s2[j++] = s1[i] + (k++);
      } while (s2[j-1] < s1[i+2]);
      if (s2[j] == s1[i+2])
	continue;
    }
  }
  s2[j] = '\0';
}

int main()
{
  char s1[100] = "-a-z0-9";
  char s2[100];

  expand(s1, s2);

  printf("%s\n", s2);
  return 0;
}

  
