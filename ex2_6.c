#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
  mask = ~(~0 << n); //sets the last n bits to 1
  //mask off p to p + n bits of x OR'd with mask on only the last n digits of y and move them to the right position i.e p to p + n
  return ((x & ~(mask << p + 1 - n)) | (y & mask) << p + 1 - n);
}
