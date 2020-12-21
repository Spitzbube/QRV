#include <stddef.h>

int memcmp(const void *s1, const void *s2, size_t n)
{
    return __builtin_memcmp(s1, s2, n);
}

size_t strlen(const char *s)
{
    return __builtin_strlen(s);
}

char *strcpy(char *dest, const char *src)
{
    return __builtin_strcpy(dest, src);
}

int strcmp(const char *s1, const char *s2)
{
    return __builtin_strcmp(s1, s2);
}

void *memset(void *s, int c, size_t n)
{
    return __builtin_memset(s, c, n);
}

void *memmove(void *dest, const void *src, size_t n)
{
    return __builtin_memmove(dest, src, n);
}
