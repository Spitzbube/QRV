#include <stddef.h>

int memcmp(const void *s1, const void *s2, size_t n)
{
    return __builtin_memcmp(s1, s2, n);
}

size_t strlen(const char *s)
{
    return __builtin_strlen(s);
}
