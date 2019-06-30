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

#include <string.h>
#include "bignum.h"
#include "numutils.h"
#include "numstack.h"
#include "numerals.h"

static void
adder(
  int *dest,
  int n)
{
  *dest += n;
}

static void
addnapp(
  struct num_stack_t **stack,
  bignum_t n1,
  bignum_t n2,
  size_t n_digits,
  char *ov_ptr)
{
  char n;
  int x;

  while (n_digits-- > 0)
  {
    x = 0;
    n = compute_arithmetic(
      ov_ptr,
      adder,
      &x,
      2,
      *--n1,
      *--n2);

    add_char_to_stack(
      stack,
      n);
  }
}

static void
apprem(
  struct num_stack_t **stack,
  bignum_t rem,
  size_t diff,
  char overflow)
{
  char n;
  int x;

  while (overflow != ZERO)
  {
    x = 0;
    n = compute_arithmetic(
      &overflow,
      adder,
      &x,
      1,
      rem[--diff]);

    add_char_to_stack(
      stack,
      n);
  }

  char ap[diff+1];
  strncpy(
    ap,
    rem,
    diff);
  ap[diff] = '\0';
  add_str_to_stack(
    stack,
    ap);
}

bignum_t
bnadd(
  bignum_t n1,
  bignum_t n2)
{
  struct num_stack_t *stack;
  bignum_t res,
    n1_dig,
    n2_dig,
    rem;
  size_t n1_len,
    n2_len,
    ll,
    diff;
  char overflow;

  stack = init_stack();
  n1_len = strlen(n1);
  n2_len = strlen(n2);
  n1_dig = n1 + n1_len;
  n2_dig = n2 + n2_len;
  overflow = ZERO;
  ll = MIN(
    n1_len,
    n2_len);
  diff = MAX(
    n1_len,
    n2_len) - ll;

  /*
   * Add the digits of the two numbers from right to left, append their values
   * to the stack, and return the overflow in the local `overflow` variable.
   */
  addnapp(
    &stack,
    n1_dig,
    n2_dig,
    ll,
    &overflow);

  // Append remaining digits to the stack.
  rem = n1_len > n2_len ? n1 : n2;
  apprem(
    &stack,
    rem,
    diff,
    overflow);

  res = create_num(stack);
  destroy_stack(stack);

  return res;
}