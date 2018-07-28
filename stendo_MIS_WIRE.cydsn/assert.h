#ifndef __ASSERT_H__
#define __ASSERT_H__

extern char text[500];
extern void __assert__(int test, char msg[], char file[], int line);

#define assert(test, msg) __assert__(test, msg,  __FILE__, __LINE__)

#endif
