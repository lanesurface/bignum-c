cmake_minimum_required(VERSION 3.8)
project(bignum_c)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c bignum.h numstack.c numstack.h numutils.h numutils.c bnadd.c numerals.h bnprod.c)
add_executable(bignum_c ${SOURCE_FILES} bignum.h)