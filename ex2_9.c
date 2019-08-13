#include <stdio.h>

int bitcount(unsigned x)
{
  int b;

  for (int b = 0; x != 0; x &= x - 1)
    ++b;
  return b;
}

//the reason that it deletes the right most 1-bit in x is as follows
//if x is odd, then the right most 1-bit is at the 0th position, which goes away when x-1 is done and x AND x-1 gives us all of the digits of x without the rightmost 1, which is x-1 itself, therefore the x got deleted
//if x is even, then the 0th position bit is definitely 0, and perhaps the other bits after the 0th bit are too. When subtracting 1, the 0th bit and other 0 bits next to the 0th bit will borrow 1 from the "closest" 1-bit, flipping all the bits before the 1-bit (and the one bit itself)
// when this is AND'd with x, all the bits remain the same except the rightmost 1 becomes 0
