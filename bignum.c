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

// This file is a work in progress. Pretty much nothing in here is functional.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "bignum.h"
#include "numutils.h"
#include "numstack.h"

#define MIN(l1, l2) l1 < l2 ? l1 : l2
#define AS_INT(c_num) (char)((c_num) - '0')

static bignum_t
add_digits(
  int n,
  ...)
{
  va_list list;
  va_start(
    list,
    n);
  int x;

  x = 0;
  while (n-- > 0)
    x += AS_INT(va_arg(
      list,
      char));
  va_end(list);

  return int_to_str(&x);
};

bignum_t
bnadd(
  bignum_t n1,
  bignum_t n2)
{
  /*
   * - Something to account for and hold the result of an overflow;
   * - A loop to add all digits and the optional overflow;
   * - And all this needs to be done on the stack so that we can grow and
   *   shrink the number as necessary.
   */
  struct num_stack_t *stack;
  bignum_t res,
    n1_dig,
    n2_dig,
    overflow;
  size_t n1_len,
    n2_len,
    ll;

  n1_len = strlen(n1);
  n2_len = strlen(n2);
  n1_dig = n1 + n1_len;
  n2_dig = n2 + n2_len;
  overflow = "0";
  ll = MIN(
    n1_len,
    n2_len);

  while (ll-- > 0)
  {
    size_t n_len;
    bignum_t n = add_digits(
      3,
      *overflow,
      *--n1_dig,
      *--n2_dig);
    n_len = strlen(n);
    strncpy(
      overflow, // Uninitialized memory!
      n,
      n_len-1);
    add_str_to_stack(
      &stack,
      &n[n_len-1]); // OK: `n` within scope of access.
  }
  res = create_num(stack);

  return res;
}

/*
 * Find the product of the given `bignum_t` and the integer factor. The
 * result is returned in a `bignum_t` as a string of character digits. The
 * value which is computed by this function is undefined if either type is
 * floating-point; that is say that this function works in terms of integers,
 * and the product is an integer itself.
 */
bignum_t
iproduct(
  bignum_t *number,
  int factor)
{
  int f_place,
    f_len,
    n_len,
    multi;
  char *p_digit,
    ovflow,
    result;
  struct num_stack_t *n_stack;
  bignum_t prod;

  f_len = get_num_digits(factor);
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
      result = (char)((*p_digit - '0') * multi);

//      *p_digit = (char) (('0' - *p_digit)
//                         * multi
//                         + '0');
    }
  }

  prod = create_num(n_stack);
  free(n_stack);

  return prod;
}