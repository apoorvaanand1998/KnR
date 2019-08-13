#include <stdio.h>

unsigned invert(unsigned x, int p, int n)
{
  mask = (~(~0 << n)) << p + 1 - n; //make last n bits 1 and bring them to position p to p + n
  // turn off p to p + n bits of x OR'd with inverted x with only p to p + n bits turned on
  return ((x & ~mask) | (~x & mask));
}
