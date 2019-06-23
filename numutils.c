/*
 * Copyright 2019 Lane W. Surface
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <stdarg.h>
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

char *
int_to_str(const int *num)
{
  char *str;
  str = malloc((size_t)get_num_digits(num));
  itoa(
    *num,
    str,
    10);

  return str;
}

bignum_t
add_digits(
  int n,
  ...)
{
  va_list list;
  int x;

  va_start(
    list,
    n);
  x = 0;
  while (n-- > 0)
    x += AS_INT(va_arg(
      list,
      int));
  va_end(list);

  return int_to_str(&x);
};