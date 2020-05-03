// lots of non-category 0 stuff here
// but they're essentially doing the same thing
// are safer and/or easier

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 1000
#define MAXLEN 100

int readlines(char *lineptr[], int maxlines)
{
  int nlines = 0;
  char buf[MAXLEN], *sp;

  while (fgets(buf, MAXLEN, stdin)) {
    if ((nlines >= maxlines) || ((sp = strdup(buf)) == NULL))
      return -1;
    else
      lineptr[nlines++] = sp;
  }
  return nlines;
}

void writelines(char *lineptr[], int nlines)
{
  int i;

  for (i = 0; i < nlines; ++i) {
    printf("%s", lineptr[i]);
    free(lineptr[i]);
  }
}

int numcmp(char *s1, char *s2)
{
  double d1, d2;

  d1 = strtod(s1, NULL);
  d2 = strtod(s2, NULL);

  if (d1 < d2)
    return -1;
  else if (d1 > d2)
    return 1;
  return 0;
}

int my_strcmp(char *s, char *t)
{
  int i;

  for (i = 0; s[i] == t[i]; i++) {
    if (s[i] == '\0') {
      return 0;
    }
  }
  return s[i] - t[i];
}

void swap(void *v[], int p1, int p2)
{
  void *temp;

  temp = v[p1];
  v[p1] = v[p2];
  v[p2] = temp;
}

void my_qsort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *), int reverse)
{
  int i, last;

  if (left >= right)
    return;
  
  swap(lineptr, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    if ((reverse * (*comp)(lineptr[i], lineptr[left])) < 0) {
      swap(lineptr, ++last, i);
    }
  }
  swap(lineptr, last, left);
  my_qsort(lineptr, left, last-1, comp, reverse);
  my_qsort(lineptr, last+1, right, comp, reverse);
}

int main(int argc, char *argv[])
{
  int nlines, numeric, reverse, i;
  char *lineptr[MAXLINES];
  
  numeric = reverse = 0;
  if (argc > 1) 
    for (i = 1; i < argc; ++i)
      if (my_strcmp(argv[i], "-nr") == 0)
	numeric = reverse = 1;
      else if (my_strcmp(argv[i], "-n") == 0)
	numeric = 1;
      else if (my_strcmp(argv[i], "-r") == 0)
	reverse = 1;

  nlines = readlines(lineptr, MAXLINES);
  my_qsort((void **) lineptr, 0, nlines-1,
	(int (*) (void *, void *)) (numeric ? numcmp : my_strcmp),
	(reverse ? -1 : 1));
  writelines(lineptr, nlines);

  return 0;
}
