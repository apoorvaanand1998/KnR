/* https://stackoverflow.com/q/61402355/4338528
   I've learned a lot from this question :))) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100

int readlines(char **pa, int n)
{
  char buf[MAXLEN], *p;
  int tmp, nlines = 0;

  while (fgets(buf, MAXLEN, stdin)) {
    // did not put + 1 below before
    // valgrind caught it
    // wouldn't have caught it without valgrind because the program
    // worked alright. After googling, found that can use strdup here
    if ((p = calloc(strlen(buf) + 1, sizeof(char))) == NULL)
      return -1;
    else {
      tmp = nlines++ % n;
      free(pa[tmp]);
      strcpy(p, buf);
      pa[tmp] = p;
    }
  }
  return nlines;
}

void writelines(char **pa, int n, int nlines)
{
  int i, start = ((nlines - n) < 0) ? 0 : (nlines - n);

  for (i = start; i < nlines; i++) 
    printf("%s", pa[i % n]);
}
  
int main(int argc, char *argv[])
{
  int n, nlines, i;
  char **pa;

  (argc == 1) ? (n = 10) : (n = strtol(*++argv, NULL, 0));
  
  pa = calloc(n, sizeof(char *));
  if (pa == NULL)
    exit(EXIT_FAILURE);
      
  nlines = readlines(pa, n);
  if (nlines == -1)
    exit(EXIT_FAILURE);
      
  writelines(pa, n, nlines);

  for (i = 0; i < n; i++)
    free(pa[i]);
  free(pa);

  return 0;
}
  
