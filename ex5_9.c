#include <stdio.h>

static int daytab[2][12] =
  {
   { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
   { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
  };

int day_of_year(int year, int month, int day)
{
  // you could put error checking here
  // I'm not going to :)

  int (*leapptr)[12], *ndays, leap, i;
  // not an array of 12 pointers but a pointer to an array of 12 integers
  
  leapptr = daytab;
  leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
  if (leap)
    leapptr++;

  ndays = *leapptr;

  for (i = 0; i < month-1; ++i) {
    day += *ndays++;
  }
  return day;
}

void month_day(int year, int yearday, int *month, int *day)
{
  int (*leapptr)[12], *ndays, leap, i = 0;
  // not an array of 12 pointers but a pointer to an array of 12 integers
  
  leapptr = daytab;
  leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
  if (leap)
    leapptr++;

  ndays = *leapptr;

  while ((yearday - *(ndays + i)) > 0) {
    yearday -= *(ndays + i);
    i++;
  }

  *month = i+1;
  *day = yearday;
}

int main()
{
  int m1, d1, m2, d2;
  
  printf("%d\n", day_of_year(2019, 3, 1));
  printf("%d\n", day_of_year(2020, 3, 1));
  printf("%d\n", day_of_year(2020, 4, 16));
  
  month_day(1988, 60, &m1, &d1);
  month_day(2020, 107, &m2, &d2);
  printf("%d %d\n", m1, d1);
  printf("%d %d\n", m2, d2);
  return 0;
}
