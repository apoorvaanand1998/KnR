#include <stdio.h>
#include <ctype.h>
#include <string.h>

double atof(char s[])
{
  double val, power, exp_val;
  int i, sign, exp_sign;

  for (i = 0; isspace(s[i]); i++)
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;
  for (val = 0.0; isdigit(s[i]); i++)
    val = (val * 10) + (s[i] - '0');
  if (s[i] == '.')
    i++;
  for (power = 1.0; isdigit(s[i]); i++) {
    val = (val * 10) + (s[i] - '0');
    power *= 10;
  }
  if (s[i] == 'e' || s[i] == 'E')
    i++;
  exp_sign = (s[i] == '-') ? -1 : 1;
  i++;
  for (exp_val = 0.0; s[i] != '\0'; i++)
    exp_val = (exp_val * 10) + (s[i] - '0');

  if (exp_sign == -1) {
    while (exp_val > 0) {
      power *= 10;
      exp_val--;
    }
  }
  else {
    while (exp_val > 0) {
      power /= 10;
      exp_val--;
    }
  }
  return sign * val / power;
}

int main()
{
  double sd;
  char s[20] = "123.45e-6";

  sd = atof(s);
  printf("%.17f\n", sd);
  return 0;
}
