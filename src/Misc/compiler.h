#pragma once

#ifndef __MISC_COMPILER_H__
#define __MISC_COMPILER_H__

#define PREPROCESSOR_TO_STRING(x) #x
#define PREPROCESSOR_JOIN(x,y) x##y
#define PREPROCESSOR_IF(c,x,y) PREPROCESSOR_JOIN(PREPROCESSOR_IF_INNER_,c)(x,y)
#define PREPROCESSOR_IF_INNER_1(x,y) x
#define PREPROCESSOR_IF_INNER_0(x,y) y
#define WARNING(l) __FILE__ "(" PREPROCESSOR_TO_STRING(l) ")"
#define PUSH_MACRO(n) __pragma(push_macro(PREPROCESSOR_TO_STRING(n)))
#define POP_MACRO(n) __pragma(pop_macro(PREPROCESSOR_TO_STRING(n)))

#endif