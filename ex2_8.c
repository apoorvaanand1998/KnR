#include <stdio.h>

unsigned rightrot(unsigned x, int n)
{
  //shift n bits to right, OR it with the last n bits that have been lost due to shifting, shifted to the right position (sizeof returns size of int in bytes)
  return ((x >> n) | ((~(~0 << n) & x) << (sizeof(int) * 8 - n)));
}
