#include <stdio.h>
#include <string.h>

void reverse_helper(char s[], int start, int end)
{
  int temp;
  
  if (start >= end)
    return;

  temp = s[start], s[start] = s[end], s[end] = temp;
  reverse_helper(s, start+1, end-1);
}

void reverse(char s[])
{
  int len;

  len = strlen(s);

  reverse_helper(s, 0, len-1);
}

int main()
{
  char s[10] = "abcde";
  reverse(s);
  printf("%s\n", s);
  return 0;
}
