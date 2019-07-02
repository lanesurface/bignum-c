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

bignum_t
bnadd(
  bignum_t n1,
  bignum_t n2)
{
  bignum_t sm,
    lg,
    res;
  size_t sm_size, lg_index;
  struct num_stack_t *stack;
  char n, overflow;
  int x;

  MIN_MAX_AND_LEN(
    n1,
    n2,
    sm,
    lg,
    sm_size,
    lg_index);
  stack = init_stack();
  sm = sm + sm_size;
  overflow = ZERO;

  while (lg_index-- > 0)
  {
    x = 0;
    n = compute_arithmetic(
      &overflow,
      adder,
      &x,
      2,
      lg[lg_index],
      sm_size <= lg_index ? *--sm : ZERO);

    add_char_to_stack(
      &stack,
      n);
  }

  if (AS_INT(overflow))
    add_char_to_stack(
      &stack,
      overflow);

  res = create_num(stack);
  destroy_stack(stack);

  return res;
}