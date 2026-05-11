#include "memory.h"

void *memset(void *dest, int value, uint32_t count)
{
    uint8_t *p = static_cast<uint8_t *>(dest);

    while (count > 0) {
        *p = static_cast<uint8_t>(value);
        p++;
        --count;
    }

    return dest;
}

void *memcpy(void *dest, const void *src, uint32_t count)
{
    uint8_t *d       = static_cast<uint8_t *>(dest);
    const uint8_t *s = static_cast<const uint8_t *>(src);

    for (uint32_t i = 0; i < count; ++i)
        d[i] = s[i];

    return dest;
}
