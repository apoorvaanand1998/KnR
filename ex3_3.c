#include <stdio.h>

void expand(char s1[], char s2[])
{
  int i, j, putc;

  for (i = 0; s1[i] != '\0'; i++) {
    if (((i == 0) && (s1[i] == '-')) || (s1[i+1] == '\0' && s1[i] == '-')) {
      s2[j++] = '-';
    }
    else if (((s1[i] >= 'a') && (s1[i] <= 'z') && ((s1[i+2] >= 'a') && (s1[i+2] <= 'z'))) ||
	     ((s1[i] >= 'A') && (s1[i] <= 'Z') && ((s1[i+2] >= 'A') && (s1[i+2] <= 'Z'))) ||
	     ((s1[i] >= '0') && (s1[i] <= '9') && ((s1[i+2] >= '0') && (s1[i+2] <= '9')))) {
      putc = s1[i];

      while (putc != s1[i+2]) {
	if (putc != s2[j-1])
	  s2[j++] = putc;
	putc += 1;
      }
      s2[j++] = putc;
    }
  }
  s2[j] = '\0';
}

int main()
{
  char s1[100] = "-a-b-c-g0-37-9-";
  char s2[100];

  expand(s1, s2);

  printf("%s\n", s2);
  return 0;
}

  
