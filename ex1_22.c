#include <stdio.h>

#define MAXCOL 10

void my_flush(char buf[]);

int main()
{
  int c, prev_char, i, j, ctr, spaceleft, first_non_space_buf;
  char buf[MAXCOL+2];

  prev_char = -1;
  i = first_non_space_buf = ctr = 0;
  spaceleft = MAXCOL;

  printf("Just keep typing once the output has been printed");
  
  while ((c = getchar()) != EOF) {
    if (buf[0] == '\n') {
      i = 0;
      my_flush(buf);
    }
    //printf("Prev char = %c and Current char = %c and i = %d and fnsb = %d and spaceleft = %d and j = %d and buf = %s \n", prev_char, c, i, first_non_space_buf, spaceleft, j,  buf);
    if ((((prev_char != ' ') && (prev_char != '\t') && (prev_char != '\n')) &&
	 ((c == ' ') || (c == '\t') || (c == '\n'))) ||
	(i == MAXCOL)) {
      if (i <= spaceleft) {
	printf("%s", buf);
	spaceleft -= i;
      }
      else {
	putchar('\n');
	spaceleft = MAXCOL;
	for (j = first_non_space_buf; buf[j] != '\0'; ++j) {
	  putchar(buf[j]);
	  ++ctr;
	}
	spaceleft -= ctr;
      }
      i = 0;
      my_flush(buf);
      buf[i++] = c;
      first_non_space_buf = j = ctr = 0;
    }
    else {
      if (((prev_char == ' ') || (prev_char == '\t') || (prev_char == '\n')) &&
	  ((c != ' ') && (c != '\t') && (c != '\n'))) {
	first_non_space_buf = i;
      }
      buf[i++] = c;
      buf[i] = '\0';
    }
    prev_char = c;
  }
  printf("%s", buf);
  return 0;
}

void my_flush(char buf[])
{
  int i;

  for (i = 0; i < MAXCOL; ++i)
    buf[i] = '\0';
}
