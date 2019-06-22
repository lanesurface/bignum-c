#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"
#include "numstack.h"

int
main(void)
{
//  bignum_t num, result;
//  num = "10";
//  result = iproduct(&num, 2);
//  printf("%s\n", result);

  struct num_stack_t *head;
  bignum_t r;
  head = &(struct num_stack_t){
    '1',
    1,
    NULL };
  add_int_to_stack(
    &head,
    123);
  r = create_num(head);
  free(head);
  printf("%s\n", r);

  return 0;
}