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

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "numstack.h"
#include "numutils.h"
#include "bignum.h"

struct num_stack_t *
init_stack(void)
{
  struct num_stack_t *stack;

  stack = malloc(sizeof(struct num_stack_t));
  stack->digit = '\0'; // So that the string is null-terminated.
  stack->depth = 0;
  stack->next = NULL;

  return stack;
}

void
destroy_stack(struct num_stack_t *head)
{
  struct num_stack_t *next, *free_targets[head->depth+1];
  int i = 0;

  /*
   * Free the stack from the last node to the first so that we preserve the
   * pointer to the previous node.
   */
  next = head;
  do
  {
    free_targets[i++] = next;
  } while (
    next = next->next,
    next);

  while (i-- > 0)
    free(free_targets[i]);
}

void
add_char_to_stack(
  struct num_stack_t **head,
  char num)
{
  struct num_stack_t *node;
  node = malloc(sizeof(struct num_stack_t));
  node->depth = (*head)->depth + 1;
  node->digit = num;
  node->next = *head;
  *head = node;
}

typedef char *(*digits_to_str)(const void *);

void
add_to_stack(
  struct num_stack_t **head,
  const void *num,
  digits_to_str to_chars)
{
  size_t n_digits;
  struct num_stack_t *node;
  char *num_str;

  num_str = to_chars(num);
  n_digits = strlen(num_str);
  while (n_digits-- > 0)
    add_char_to_stack(
      head,
      num_str[n_digits]);
}

void
add_int_to_stack(
  struct num_stack_t **head,
  int num)
{
  add_to_stack(
    head,
    &num,
    (digits_to_str)int_to_str);
}

static char *
char_identity(const void *num)
{
  return num;
}

void
add_str_to_stack(
  struct num_stack_t **head,
  const char *num)
{
  add_to_stack(
    head,
    num,
    char_identity);
}

bignum_t
create_num(struct num_stack_t *n_stack)
{
  bignum_t num;
  int i, depth;
  struct num_stack_t *curr_num;

  depth = n_stack->depth;
  num = malloc((size_t)(depth+1));
  curr_num = n_stack;
  for (i = 0; i < depth; i++)
  {
    num[i] = curr_num->digit;
    curr_num = curr_num->next;
  }

  return num;
}