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

#include <string.h>
#include "bignum.h"
#include "numstack.h"
#include "numutils.h"
#include "numerals.h"

static void
multiplier(
  int *dest,
  int n)
{
  *dest *= n;
}

static void
push_zeros(
  struct num_stack_t **stack,
  int n)
{
  while (n-- > 0)
    add_char_to_stack(
      stack,
      ZERO);
}

bignum_t
bnproduct(
  bignum_t n1,
  bignum_t n2)
{
  struct num_stack_t *stack;
  bignum_t sm,
    lg,
    lg_pos,
    interres;
  size_t sm_len, lg_len;
  char dig, overflow;
  int x, i;

  MIN_MAX_AND_LEN(
    n1,
    n2,
    sm,
    lg,
    sm_len,
    lg_len);
  interres = "0";

  for (i = 0; i < sm_len; i++)
  {
    stack = init_stack();
    dig = sm[sm_len-i-1];
    lg_pos = lg + lg_len;
    overflow = ZERO;

    push_zeros(
      &stack,
      i);

    while (lg_pos > lg)
    {
      x = 1;
      add_char_to_stack(
        &stack,
        compute_arithmetic(
          &overflow,
          multiplier,
          &x,
          2,
          dig,
          *--lg_pos));
    }
    if (AS_INT(overflow))
      add_char_to_stack(
        &stack,
        overflow);

    interres = bnadd(
      interres,
      create_num(stack));
    destroy_stack(stack);
  }

  return interres;
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