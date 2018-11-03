#include <stdio.h>
#include <limits.h>

int main()
{
  signed int n = 0;
  signed int n2 = 1;
  
  while (n2 >= n) {
    ++n;
    ++n2;
  }

  printf("Min value = %d\n", n2);
  printf("Max value = %u\n", n);
  printf("USHRT_MAX = %u\n", INT_MAX);
  return 0;
}
