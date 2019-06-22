

#ifndef NUMSTACK_H
#define NUMSTACK_H

#include "bignum.h"

struct num_stack_t
{
  char digit;
  int depth;
  struct num_stack_t *next;
};

struct num_stack_t *init_stack(void);
void destroy_stack(struct num_stack_t *);
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

#endif // NUMSTACK_H
