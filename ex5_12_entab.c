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

// when a space to non-space transition happens
// i and nos given as input, finds out by how much i should be updated
// and how many tabs and spaces to replace spaces with
void find_i_tabs_spaces(int *i, int nos, int m, int n, int *tabs, int *spaces)
{
  int og_i, j;

  // if everything happened before m, do nothing, i.e. don't entab
  if ((*i + nos) < m) {
    *tabs = 0;
    *spaces = nos;
    *i += nos;
  }
  else {
    og_i = *i;
    for (j = *i; j < nos; ++j) {
      if (((j - m) % n) == 0) {
	*i = j;
	*tabs += 1;
      }
    }
    // after tabbing as many spaces as possible
    // if spaces remain
    if ((og_i + nos) > *i) {
      *i += og_i + nos;
      *spaces += 1; // I guess you can also do *++spaces;
    }
  }
} 

int main(int argc, char *argv[])
{
  int m, n, c, i, j, nos, nt, ns;

  i = nos = ns = nt = 0;

  // user entered incorrect format of command line options
  if (decide_mn(argc, argv, &m, &n) == 0) {
    return -1;
  }

  // start processing characters
  while ((c = getchar()) != EOF) {
    if (c != ' ') {
      // check if a space to non-space transition is happening
      // this is where you have to entab
      if (nos > 0) {
	find_i_tabs_spaces(&i, nos, m, n, &nt, &ns);
	// put tabs nt times
	for (j = 0; j < nt; ++j) {
	  putchar('\t');
	}
	// put spaces ns times
	for (j = 0; j < ns; ++j) {
	  putchar(' ');
	}
	nos = 0;
      }
      
      putchar(c);
      ++i;

      // if c is newline, reset column counter to 0
      if (c == '\n') {
	i = 0;
      }
    }
    // c is space
    else {
      ++nos;
    }
  }
  return 0;
}
      

  
