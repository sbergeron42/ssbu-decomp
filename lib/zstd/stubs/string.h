#ifndef _STRING_H_STUB
#define _STRING_H_STUB

#include <stddef.h>

void* memcpy(void* dst, const void* src, size_t n);
void* memmove(void* dst, const void* src, size_t n);
void* memset(void* dst, int c, size_t n);
int   memcmp(const void* s1, const void* s2, size_t n);

#endif
