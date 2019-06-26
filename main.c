#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "bignum.h"
#include "numstack.h"
#include "numutils.h"

void
free_all(
  int n,
  ...)
{
  va_list l;
  char *s;

  va_start(
    l,
    n);
  while (--n >= 0)
  {
    s = va_arg(
      l,
      char *);
    free(s);
    s = NULL;
  }
  va_end(l);
}

int
main(void)
{
//  bignum_t num, result;
//  num = "10";
//  result = iproduct(&num, 2);
//  printf("%s\n", result);

//  struct num_stack_t *head;
//  bignum_t r;
//  head = &(struct num_stack_t){
//    '1',
//    1,
//    NULL };
//  add_int_to_stack(
//    &head,
//    123);
//  r = create_num(head);
//  free(head);
//  printf("%s\n", r);
//
//  free_all(
//    1,
//    r);

//  bignum_t n = bnadd(
//    "2",
//    "3");
//  printf("%s\n", n);
//  free(n);

  struct num_stack_t *stack;
  bignum_t str;
  stack = init_stack();
  add_int_to_stack(
    &stack,
    123);
  str = create_num(stack);
  printf("%s\n", str);
  destroy_stack(stack);

  return 0;
}