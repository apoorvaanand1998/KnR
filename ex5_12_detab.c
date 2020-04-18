#include <stdio.h>
#include <stdlib.h>

#define TABWIDTH 8

// return type is int but will be using as boolean type
int decide_mn(int argc, char *argv[], int *m, int *n)
{
  char *curr_ca;
  
  // there are command line arguments given
  if (argc - 1 > 0) {
    while (--argc > 0) {
      // current character array
      curr_ca = *++argv;
      // if first character character array is '+'
      if (*curr_ca == '+') {
	*n = atoi(curr_ca+1);
      }
      else if (*curr_ca == '-') {
	*m = atoi(curr_ca+1);
      }
      else {
	printf("Usage : Detab -m +n - Tabstops every n columns from m\n");
	return 0;
      }
    }
  }
  // no command line arguments, assume default tab width
  else {
    *m = 0;
    *n = TABWIDTH;
  }
  return 1;
}


int main(int argc, char *argv[])
{
  int m, n, c, i, j, nos;

  i = 0;

  // user entered incorrect format of command line options
  if (decide_mn(argc, argv, &m, &n) == 0) {
    return -1;
  }
  
  // start processing characters
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      putchar(c);
      i = 0;
    }
    else if (c != '\t' || i < m) {
      putchar(c);
      ++i;

      // tab got printed because i < m
      if (c == '\t') {
	nos = TABWIDTH - (i % TABWIDTH);
	// nos - 1 because when tab was printed i was incremented by 1
	i += nos - 1;
      }
    }
    // c is not newline
    // c is tab and i > m
    else {
      nos = n - ((i - m) % n);
      // print space nos times while updating i
      for (j = 0; j < nos; ++j) {
	putchar(' ');
	++i;
      }
    }
  }
  return 0;
}
