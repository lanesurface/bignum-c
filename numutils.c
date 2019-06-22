
#include <math.h>
#include "numutils.h"

int
get_digit(
  int number,
  int place)
{
  int tmp;
  tmp = (int)pow(
    10,
    place+1);

  return number % tmp / (tmp / 10);
}

int
get_num_digits(const int *num)
{
  int len, tmp;
  len = 0;
  tmp = *num;
  while (len++, tmp >= 10)
    tmp /= 10;

  return len;
}