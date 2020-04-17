/* prints spaces until the next tabstop which is given with commandline 
   arguments. Tries emulating typewriter's tabs. If next tabstop is 
   lesser than the number of currently printed line, it defaults 
   to a tabwidth of 8 */

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

void detab(char *output, char *input, int *tabstops, int nts)
{
  int i, j, o, t, next_tabstop, nos;

  i = o = t = 0;

  while (*(input + i) != '\0') {
    if (*(input + i) != '\t') {
      *(output + o++) = *(input + i);
      
      if (o > *(tabstops + t) && t < nts)
	++t;
    }
    else {
      if (t < nts) {
	next_tabstop = *(tabstops + t);
	nos = ((next_tabstop - i) >= 0) ? (next_tabstop - i) : (TABWIDTH - (i % TABWIDTH));

	for (j = 0; j < nos; ++j) {
	  *(output + o++) = ' ';
	}

	if (o > *(tabstops + t) && t < nts) {
	  ++t;
	}
      }
      else {
	nos = TABWIDTH - (i % TABWIDTH);

	for (j = 0; j < nos; ++j) {
	  *(output + o++) = ' ';
	}
      }
    }
    ++i;
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
    detab(output, input, tabstops, nts);
    printf("%s", output);
  }
  return 0;
}
