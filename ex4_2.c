#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <float.h>

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
  if (s[i] == '+' || s[i] == '-')
    i++;
  for (exp_val = 0.0; s[i] != '\0'; i++)
    exp_val = (exp_val * 10) + (s[i] - '0');

  if (exp_sign == -1)
    power *= pow(10, exp_val);
  else
    power /= pow(10, exp_val);
 
  return sign * val / power;
}

int main()
{
  double sd;
  char s[20] = "123.45513e-9";

  sd = atof(s);
  printf("%.*e\n", FLT_DIG, sd); // https://stackoverflow.com/a/16839757/4338528
  return 0;
}
