#include <stdio.h>
#include <stdlib.h>

#define IOMAXSIZE 100
#define TABSMAX 20
#define TABWIDTH 8

int my_getline(char s[], int lim)
{
  int c, i;

  i = 0;
  
  while ((c = getchar()) != EOF && c != '\n' && i < lim) {
    s[i++] = c;
  }
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';

  return i;
}

void entab(char *output, char *input, int *tabstops, int nts)
{
  int i, j, t, o, spaces;

  i = o = t = spaces = 0;
  
  while (*(input + i) != '\0') {
    if (*(input + i) != ' ' || i == t) {
      if (spaces && i == t) {
	spaces = 0;
	*(output + o++) = '\t';
      }
      else if (spaces && i != t) {
	spaces = 0;
	if (t == -1) {
	  for (j = 0; j < i/TABWIDTH; ++j) {
	    *(output + o++) = '\t';
	  }
	}
	while (o < i) {
	  *(output + o++) = ' ';
	}
	*(output + o++) = *(input + i);
      }
      else {
	*(output + o++) = *(input + i);
      }
    }
    else {
      spaces = 1;
    }
    ++i;
    
    if (*(tabstops + t) < i && t < nts) {
      ++t;
      if (t == nts) {
	t = -1;
      }
    }
  }
  *(output + o) = '\0';
}

int main(int argc, char *argv[])
{
  char input[IOMAXSIZE];
  char output[IOMAXSIZE];
  int tabstops[TABSMAX];
  int nts = argc - 1;
  int t = 0;
  
  while (--argc > 0) {
    tabstops[t++] = atoi(*++argv);
  }
  
  while (my_getline(input, IOMAXSIZE) > 0) {
    entab(output, input, tabstops, nts);
    printf("%s", output);
  }
  return 0;
}
  
