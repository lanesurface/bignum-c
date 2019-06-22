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

/*
 * File: numstack.h
 * Authors: Lane W. Surface
 *
 * Functions for handling numbers whose size changes during runtime. Allows
 * for functions which perform arithmetic to push and pop numbers from the
 * highest-order numeral to the lowest. This makes it convenient to deal
 * with numbers in terms of their respective digits rather than the string
 * of characters that they are made up of. After finishing all arithmetic
 * operations on each of the numerals, `create_num` should be called to
 * transform this stack back into a string.
 */

#ifndef __NUMSTACK_H__
#define __NUMSTACK_H__

#include "bignum.h"

struct num_stack_t
{
  char digit;
  int depth;
  struct num_stack_t *next;
};

struct num_stack_t *init_stack(void);
void add_to_stack(
  struct num_stack_t **,
  void *num,
  char *(*)(void *));
void add_int_to_stack(
  struct num_stack_t **,
  int);
void add_str_to_stack(
  struct num_stack_t **,
  char *);
bignum_t create_num(struct num_stack_t *n_stack);

#endif // __NUMSTACK_H__
