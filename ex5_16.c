#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void fold_case(char *s, char *res)
{
  char *c = s;
  int i = 0;

  while (*c != '\0') {
    if (isalpha(*c)) {
      res[i++] = toupper(*c);
    }
    else {
      res[i++] = *c;
    }
    ++c;
  }
  
  res[i] = '\0';
}

int strcmpf(char *s1, char *s2)
{
  char fs1[LINELEN];
  char fs2[LINELEN];
  
  fold_case(s1, fs1);
  fold_case(s2, fs2);
  
  return my_strcmp(fs1, fs2);
}

int strcmpfr(char *s1, char *s2)
{
  char fs1[LINELEN];
  char fs2[LINELEN];
  
  fold_case(s1, fs1);
  fold_case(s2, fs2);

  return my_strcmpr(fs1, fs2);
}

int numcmpf(char *s1, char *s2)
{
  char fs1[LINELEN];
  char fs2[LINELEN];
  
  fold_case(s1, fs1);
  fold_case(s2, fs2);

  return numcmp(fs1, fs2);
}

int numcmpfr(char *s1, char *s2)
{
  char fs1[LINELEN];
  char fs2[LINELEN];
  
  fold_case(s1, fs1);
  fold_case(s2, fs2);

  return numcmpr(fs1, fs2);
}

void directory(char *s, char *res)
{
  int i = 0;
  char *c = s;

  while (*c != '\0') {
    if (isalpha(*c) || isdigit(*c) || isspace(*c)) {
      res[i++] = *c;
    }
    ++c;
  }
  res[i] = '\0';
}

int strcmpd(char *s1, char *s2)
{
  char d1[LINELEN];
  char d2[LINELEN];

  directory(s1, d1);
  directory(s2, d2);

  return my_strcmp(d1, d2);
}

int strcmpdr(char *s1, char *s2)
{
  char d1[LINELEN];
  char d2[LINELEN];

  directory(s1, d1);
  directory(s2, d2);

  return my_strcmpr(d1, d2);
}

int strcmpdf(char *s1, char *s2)
{
  char d1[LINELEN];
  char d2[LINELEN];

  directory(s1, d1);
  directory(s2, d2);

  return strcmpf(d1, d2);
}

int strcmpdfr(char *s1, char *s2)
{
  char d1[LINELEN];
  char d2[LINELEN];

  directory(s1, d1);
  directory(s2, d2);

  return strcmpfr(d1, d2);
}

int main(int argc, char *argv[])
{
  int numeric, reverse, fold, directory, i, nlines;
  char *lineptr[MAXLINES];
  
  numeric = reverse = fold = directory = 0;

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
      if (my_strcmp(argv[i], "-f") == 0) {
	fold = 1;
      }
      if (my_strcmp(argv[i], "-d") == 0) {
	directory = 1;
      }
    }
  }

  nlines = readlines(lineptr, MAXLINES);
  if (nlines == -1)
    exit(EXIT_FAILURE);
  
  if ((numeric == 1) && (reverse == 0) && (fold == 0) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void*)) numcmp);
  }
  else if ((numeric == 0) && (reverse == 0) && (fold == 0) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) my_strcmp);
  }
  else if ((numeric == 0) && (reverse == 1) && (fold == 0) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) my_strcmpr);
  }
  else if ((numeric == 1) && (reverse == 1) && (fold == 0) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) numcmpr);
  }
  else if ((numeric == 0) && (fold == 1) && (reverse == 0) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) strcmpf);
  }
  else if ((directory == 1) && (fold == 0) && (reverse == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) strcmpd);
  }
  else if ((directory == 1) && (fold == 0) && (reverse == 1)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) strcmpdr);
  }
  else if ((directory == 1) && (fold == 1) && (reverse == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) strcmpdf);
  }
  else if ((directory == 1) && (fold == 1) && (reverse == 1)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) strcmpdfr);
  }
  else if ((numeric == 0) && (fold == 1) && (reverse == 1) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) strcmpfr);
  }
  else if ((numeric == 1) && (fold == 1) && (reverse == 0) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) numcmpf);
  }
  else if ((numeric == 1) && (fold == 1) && (reverse == 1) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) numcmpfr);
  }
  writelines(lineptr, nlines);
  return 0;
}
