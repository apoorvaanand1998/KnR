#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 1000
#define LINELEN 100

int readlines(char *lineptr[], int maxlines)
{
  char buf[LINELEN], *p;
  int nlines = 0;

  while (fgets(buf, maxlines, stdin)) {
    if ((nlines >= maxlines) || (buf == NULL) || ((p = strdup(buf)) == NULL))
      return -1;
    else {
      lineptr[nlines++] = p;
    }
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

void swap(void *v[], int p1, int p2)
{
  int *temp;

  temp = v[p1];
  v[p1] = v[p2];
  v[p2] = temp;
}

void my_qsort(void *v[], int left, int right,
	   int (*comp)(void *, void*))
{
  int last, i;

  if (left >= right)
    return;

  swap(v, left, (left+right)/2);
  last = left;
  for (i = left+1; i <= right; ++i) {
    if ((*comp)(v[i], v[left]) < 0) {
      swap(v, ++last, i);
    }
  }
  swap(v, last, left);
  my_qsort(v, left, last-1, comp);
  my_qsort(v, last+1, right, comp);
}

int my_strcmp(char *s1, char *s2)
{
  int i;

  while (*s1 == *s2) {
    if (*s1 == '\0') {
      return 0;
    }
    s1++;
    s2++;
  }

  return (*s1 - *s2);
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

int my_strcmpr(char *s1, char *s2)
{
  while (*s1 == *s2) {
    if (*s1 == '\0') {
      return 0;
    }
    s1++;
    s2++;
  }
  return (*s2 - *s1);
}

int numcmpr(char *s1, char *s2)
{
  double d1, d2;

  d1 = strtod(s1, NULL);
  d2 = strtod(s2, NULL);

  if (d1 < d2)
    return 1;
  else if (d1 > d2)
    return -1;
  return 0;
}

int main(int argc, char *argv[])
{
  int numeric, reverse, i, nlines;
  char *lineptr[MAXLINES];
  
  numeric = reverse = 0;

  if (argc > 1) {
    for (i = 1; i < argc; ++i) {
      if (my_strcmp(argv[i], "-n") == 0) {
	numeric = 1;
      }
      if (my_strcmp(argv[i], "-r") == 0) {
	reverse = 1;
      }
      if (my_strcmp(argv[i], "-nr") == 0) {
	numeric = reverse = 1;
      }
    }
  }

  nlines = readlines(lineptr, MAXLINES);
  if (nlines == -1)
    exit(EXIT_FAILURE);
  
  if ((numeric == 1) && (reverse == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	  (int (*)(void *, void*)) numcmp);
  }
  else if ((numeric == 0) && (reverse == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	  (int (*)(void *, void *)) my_strcmp);
  }
  else if ((numeric == 0) && (reverse == 1)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	  (int (*)(void *, void *)) my_strcmpr);
  }
  else if ((numeric == 1) && (reverse == 1)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	  (int (*)(void *, void *)) numcmpr);
  }

  writelines(lineptr, nlines);
  return 0;
}


