/*
 * Copyright 2019 Lane W. Surface
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

/*
 * File: bignum.c
 * Authors: Lane W. Surface
 * Version: 1.0
 *
 * This file contains functions for manipulating and working with arbitrarily
 * sized numbers. Not only does this abstract away from the underlying
 * bit-patterns, placing focus only on the presentable representation
 * thereof; but allows for numbers which cannot be represented in the native
 * C integer types provided with the language.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
get_num_digits(int num)
{
  int len, tmp;
  len = 0;
  tmp = num;
  while (len++, tmp >= 10)
    tmp /= 10;

  return len;
}

static struct num_stack_t
{
  char digit;
  int depth;
  struct num_stack_t *next;
};

static bignum_t
create_num(struct num_stack_t *n_stack)
{
  bignum_t num;
  int i, depth;
  struct num_stack_t *curr_num;

  depth = n_stack->depth;
  num = malloc((size_t)depth);
  curr_num = n_stack;
  for (i = 0; i < depth; i++)
  {
    *num++ = curr_num->digit;
    curr_num = curr_num->next;
  }

  return num;
}

static void
add_to_stack(
  struct num_stack_t *head,
  int num)
{
  int n_digits;
  struct num_stack_t *node;

  n_digits = get_num_digits(num);
  while (n_digits-- > 0)
  {
    node = malloc(sizeof(struct num_stack_t));
    node->depth = head->depth + 1;
    node->next = head;
    node->digit = (char)('0' + get_digit(
      num,
      n_digits));
    head = node;
  }
}

static void
destroy_stack(struct num_stack_t *head)
{
  struct num_stack_t *next;

  next = head;
  while (next = next->next, next)
    free(next);
  free(head);
}

/*
 * Find the product of the given number and the factor, storing the result in
 * the object pointed to by number. This function assumes that both the
 * number and the factor are integers, and thus does not handle floating-point
 * inputs. Using a floating point number as the destination will result in
 * an undefined value.
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
  destroy_stack(n_stack);

  return prod;
}