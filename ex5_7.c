#include <stdio.h>
#include <string.h>
#define MAXLINES 500
#define MAXLEN 100
#define TOTMEM 5000

char *lptr[MAXLINES];

int my_getline2(char *s, int lim)
{
  int c, offset = 0;

  while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
    *(s + offset++) = c;
  }
  if (c == '\n')
    *(s + offset++) = c;
  s[offset] = '\0';
  return offset;
}

int readlines(char *linearr, char *lineptr[], int maxlines)
{
  int len, nlines, tot_len;
  char line[MAXLEN];
  char *p;

  nlines = tot_len = 0;
  p = linearr;
  
  while ((len = my_getline2(line, MAXLEN)) > 0) {
    if ((nlines >= maxlines) || (tot_len + len >= TOTMEM))
      return -1;
    else {
      line[len-1] = '\0';
      strcpy(p, line);
      lineptr[nlines++] = p;
      p += len;
      tot_len += len;
    }
  }
  return nlines;
}

void writelines(char *lineptr[], int nlines)
{
  while (nlines-- > 0)
    printf("%s\n", *lineptr++);
}

int main()
{
  char linearr[TOTMEM];
  int nol;

  nol = readlines(linearr, lptr, MAXLINES);

  if (nol != -1)
    writelines(lptr, nol);

  return 0;
}
    

  
      
    
    
