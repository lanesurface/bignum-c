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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bignum.h"
#include "numutils.h"
#include "numstack.h"

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

      *p_digit = (char) (('0' - *p_digit)
                         * multi
                         + '0');
    }
  }

  prod = create_num(n_stack);
  free(n_stack);

  return prod;
}