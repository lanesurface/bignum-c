#include <stdio.h>
#include "bignum.h"

int
main(void)
{
  bignum_t num, result;
  num = "10";
  result = iproduct(&num, 2);
  printf("%s\n", result);

  return 0;
}