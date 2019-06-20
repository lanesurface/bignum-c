#include <stdio.h>
#include "bignum.h"

int
main(void)
{
  bignum_t num = "10";
  iproduct(&num, 2);
  printf("%s\n", num);

  return 0;
}