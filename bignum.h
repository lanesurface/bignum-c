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
 * File: bignum.h
 * Authors: Lane W. Surface
 * Version: 1.0
 *
 * This file contains functions for manipulating and working with arbitrarily
 * sized numbers. Not only does this abstract away from the underlying
 * bit-patterns, placing focus only on the presentable representation
 * thereof; but allows for numbers which cannot be represented in the native
 * C integer types provided with the language.
 */

#ifndef __BIGNUM_H__
#define __BIGNUM_H__

#include <math.h>
#include <string.h>

typedef char *bignum_t;

void iproduct(
  bignum_t *,
  int);

#endif // __BIGNUM_H__
