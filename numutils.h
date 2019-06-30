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
 * File: numutils.h
 * Authors: Lane W. Surface
 *
 * Manipulation and transformation functions dealing with native C integer
 * types. Allows for the library to work with these types at a higher level
 * than the actual bits which they are composed of.
 */

#ifndef __NUMUTILS_H__
#define __NUMUTILS_H__

#include "bignum.h"

#define MAX(l1, l2) ((l1) > (l2) ? (l1) : (l2))
#define MIN(l1, l2) ((l1) < (l2) ? (l1) : (l2))
#define AS_INT(c_num) (char)((c_num) - '0')

int get_digit(
  int number,
  int place);
int get_num_digits(const int *num);
char *int_to_str(const int *);
typedef void (*arith_func)(
  int *,
  int);
char compute_arithmetic(
  char *,
  arith_func,
  int *,
  int,
  ...);

#endif // __NUMUTILS_H__