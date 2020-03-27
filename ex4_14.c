#include <stdio.h>

#define swap(t, x, y) {				\
    t temp;					\
    temp = x, x = y, y = temp;			\
  }

int main()
{
  double a = 100.5;
  double b = 200.9;
  double p = 3.03;
  double q = 4.04;
  int x = 42;
  int y = 245;
  char *px, *py;
  px = "hello";
  py = "world";
  printf("a, b BEFORE = %f %f\n", a, b);
  printf("p, q BEFORE = %f %f\n", p, q);
  printf("x, y BEFORE = %d %d\n", x, y);
  printf("px, py BEFORE = %s %s\n", px, py);
  swap(int, x, y);
  swap(double, a, b);
  swap(double, p, q);
  swap(char *, px, py);
  printf("a, b AFTER = %f %f\n", a, b);
  printf("p, q AFTER = %f %f\n", p, q);
  printf("x, y AFTER = %d %d\n", x, y);
  printf("px, py AFTER = %s %s\n", px, py);
  return 0;
}

