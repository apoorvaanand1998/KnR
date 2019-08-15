#include <stdio.h>

void escape(char s[], char t[])
{
  int i = 0;
  int j = 0;
  
  while (t[i] != '\0') {
    switch (t[i]) {
    case '\n': case '\t':
      s[j++] = '\\';
      s[j++] = (t[i] == '\n') ? 'n' : 't';
      break;
    default:
      s[j++] = t[i];
      break;
    }
    i++;
  }
  s[j] = '\0';
}

void rev_escape(char s[], char t[])
{
  int i = 0;
  int j = 0;

  while (s[i] != '\0') {
    switch (s[i]) {
    case '\\':
      i++;
      switch (s[i+1]) {
      case 'n':
	t[j++] = '\n';
	break;
      case 't':
	t[j++] = '\t';
	break;
      }
      break;
    default:
      t[j++] = s[i];
    }
    i++;
  }
  t[i] = '\0';
}

int main() {
  char t[10] = "adele\n";
  char s[10];

  escape(s, t);
  printf("%s\n", s);

  rev_escape(s, t);
  printf("%s", t);
  
  return 0;
}
