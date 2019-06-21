
#include <stdio.h>
#include "bignum.h"

static int
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

static int
get_num_digits(int);

/*
 * Find the product of the given number and the factor, storing the result in
 * the object pointed to by number. This function assumes that both the
 * number and the factor are integers, and thus does not handle floating-point
 * inputs. Using a floating point number as the destination will result in
 * an undefined value.
 */
void
iproduct(
  bignum_t *number,
  int factor)
{
  int f_place,
    f_len,
    n_len,
    tmp,
    multi;
  char *p_digit, ovflow;

  // Find the number of digits in our factor.
  f_len = 0;
  tmp = factor;
  while (f_len++, tmp >= 10)
    tmp /= 10;

  n_len = (int)strlen(*number);
  for (f_place = 0; f_place < f_len; f_place++)
  {
    multi = get_digit(
      factor,
      f_place);
    printf("%d\n", multi);
    p_digit = *number + n_len;
    while (--p_digit >= *number)
    {
      int r = (*p_digit - '0') * multi;
      *p_digit = (char) (('0' - *p_digit)
                         * multi
                         + '0');
    }
  }
}