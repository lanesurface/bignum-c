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

// This file is a work in progress.

#include <stdio.h>
#include <string.h>
#include "bignum.h"
#include "numstack.h"
#include "numutils.h"

#define MIN_MAX_AND_LEN(n1,                       \
                        n2,                       \
                        min_dest,                 \
                        max_dest,                 \
                        min_len,                  \
                        max_len)                  \
  size_t __n1_len, __n2_len;                      \
  __n1_len = strlen(n1);                          \
  __n2_len = strlen(n2);                          \
  (min_dest) = __n1_len < __n2_len ? (n1) : (n2); \
  (max_dest) = __n1_len > __n2_len ? (n1) : (n2); \
  (min_len) = MIN(                                \
    __n1_len,                                     \
    __n2_len);                                    \
  (max_len) = MAX(                                \
    __n1_len,                                     \
    __n2_len);

static char
mult_digit(
  struct num_stack_t **stack,
  char *overflow,
  int n,
  ...)
{
  return '\0';
}

bignum_t
bnproduct(
  bignum_t n1,
  bignum_t n2)
{
  struct num_stack_t *stack;
  bignum_t sm, lg;
  size_t sm_len,
    lg_len,
    sm_pos,
    lg_pos;
  char dig,
    n,
    overflow;

  MIN_MAX_AND_LEN(
    n1,
    n2,
    sm,
    lg,
    sm_len,
    lg_len);
  sm_pos = sm_len;
  lg_pos = lg_len;
  bignum_t interres[sm_len];

  /*
   * A few things need to be kept in mind for this particular function:
   *  - The largest number needs to "be on top"; that is to say that we
   *    should iterate over the smallest number's digits only once, while
   *    taking each of these digits and multiplying it by the digits on the
   *    top to create an _intermediate result_.
   */

  while (sm_pos-- > 0)
  {
    // Multiply the digit by all digits in `lg`.
    dig = sm[sm_len];

    while (lg_pos-- > 0)
      n = mult_digit(
        &stack,
        &overflow,
        3,
        overflow,
        dig,
        lg[lg_pos]);
  }
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
  bignum_t number,
  int factor); // TODO