/*
  This program can obviously be engineered more to add more options 
and to make it "better". Some cons of this program 
    - Can't give multiple options together. Each option must be prefixed with "-"
    (./a.out -nrdf isn't possible)
    - Can only give one field for sorting and it MUST be the last option

    Example usage - ./a.out -n -r -d -f 2
where 2 is referring to the field the sorting will be performed on
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXLINES 1000
#define LINELEN 100

int min_field(char *lineptr[], int nlines)
{
  int line_i, char_i, min_field, field;

  min_field = LINELEN;

  for (line_i = 0; line_i < nlines; ++line_i) {
    field = 0;
    for (char_i = 0; char_i < strlen(lineptr[line_i]); ++char_i) {
      // non-space to space transition counts as one field
      if (!(isspace(lineptr[line_i][char_i])) && (isspace(lineptr[line_i][char_i+1]))) {
	++field;
      }
    }
    if (field < min_field)
      min_field = field;
  }
  return min_field;
}

int get_field(int field, char *line, char *result)
{
  int i, j, f;

  j = f = 0;
  
  for (i = 0; i < strlen(line); ++i) {
    if ( (! (isspace(line[i]))) && (isspace(line[i+1]))) {
      ++f;
    }
    if (f == field-1)
      break;
  }
  
  ++i;
  while (1) {
    if (! (isspace(line[i])))
      result[j++] = line[i];
    if ((! (isspace(line[i]))) && (isspace(line[i+1]))) 
      break;
    ++i;
  }
  result[j] = '\0';
  return j;
}
    
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
	      int (*comp)(void *, void*), int field)
{
  int last, i;
  char field1[LINELEN], field2[LINELEN];

  if (left >= right)
    return;

  swap(v, left, (left+right)/2);
  last = left;

  if (field == 0) {
    for (i = left+1; i <= right; ++i) {
      if ((*comp)(v[i], v[left]) < 0) {
	swap(v, ++last, i);
      }
    }
  }
  else {
    for (i = left+1; i <= right; ++i) {
      get_field(field, v[i], field1);
      get_field(field, v[left], field2);

      if ((*comp)(field1, field2) < 0) {
	swap(v, ++last, i);
      }
    }
  }
  swap(v, last, left);
  my_qsort(v, left, last-1, comp, field);
  my_qsort(v, last+1, right, comp, field);
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
  int numeric, reverse, fold, directory, i, nlines, user_field;
  char *lineptr[MAXLINES], *endptr, field_result[LINELEN];
  
  numeric = reverse = fold = directory = user_field = 0;

  if (argc > 1) {
    for (i = 1; i < argc; ++i) {
      user_field = strtol(argv[i], &endptr, 0);
      if (! (my_strcmp(argv[i], "") != 0) && (*endptr == '\0')) {
	user_field = 0;
      }
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

  if ((user_field >= 1) && (user_field <= min_field(lineptr, nlines))) {
    printf("Using field %d for sorting\n", user_field);
  }
  else {
    printf("Not sorting using fields\n");
    user_field = 0;
  }

  if ((numeric == 1) && (reverse == 0) && (fold == 0) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void*)) numcmp, user_field);
  }
  else if ((numeric == 0) && (reverse == 0) && (fold == 0) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) my_strcmp, user_field);
  }
  else if ((numeric == 0) && (reverse == 1) && (fold == 0) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) my_strcmpr, user_field);
  }
  else if ((numeric == 1) && (reverse == 1) && (fold == 0) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) numcmpr, user_field);
  }
  else if ((numeric == 0) && (fold == 1) && (reverse == 0) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) strcmpf, user_field);
  }
  else if ((directory == 1) && (fold == 0) && (reverse == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) strcmpd, user_field);
  }
  else if ((directory == 1) && (fold == 0) && (reverse == 1)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) strcmpdr, user_field);
  }
  else if ((directory == 1) && (fold == 1) && (reverse == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) strcmpdf, user_field);
  }
  else if ((directory == 1) && (fold == 1) && (reverse == 1)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) strcmpdfr, user_field);
  }
  else if ((numeric == 0) && (fold == 1) && (reverse == 1) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) strcmpfr, user_field);
  }
  else if ((numeric == 1) && (fold == 1) && (reverse == 0) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) numcmpf, user_field);
  }
  else if ((numeric == 1) && (fold == 1) && (reverse == 1) && (directory == 0)) {
    my_qsort((void **) lineptr, 0, nlines-1,
	     (int (*)(void *, void *)) numcmpfr, user_field);
  }
  writelines(lineptr, nlines);
  return 0;
}
