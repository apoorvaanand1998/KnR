#include <stdio.h>

int main()
{
  int c, parens, brackets, braces, sq, dq;

  parens = brackets = braces = 0;
  sq = dq = 1;

  while ((c = getchar()) != EOF) {

    if (c == '[')
      ++parens;
    if (c == ']')
      --parens;
    if (c == '(')
      ++brackets;
    if (c == ')')
      --brackets;
    if (c == '[')
      ++braces;
    if (c == ']')
      --braces;

    if (c == '\'')
      sq *= -1;
    if (c == '"')
      dq *= -1;
  }
  
  if ((parens != 0) || (brackets != 0) || (braces != 0))
    printf("Check your brackets/parentheses/braces.\n");
  if ((sq != 1) || (dq != 1))
    printf("Check your single/double quotes.\n");
  else
    printf("Things might be fine. But probably not.\n");

  return 0;
}
