#include <stdio.h>
#include <limits.h>

int main()
{
  unsigned int i;

  i = ~0;

  printf("Unsigned print = %u\n", i);
  printf("UINT_MAX = %u\n", UINT_MAX);

  i >>= 1;
  printf("Signed print = %u\n", i);
  printf("INT_MAX = %u\n", INT_MAX);
  printf("Signed min = %d\n", -i-1);
  return 0;
}
