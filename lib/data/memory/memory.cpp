#include "memory.h"
extern "C" char _kernel_end;

void *memset(void *dest, int value, uint32_t count)
{
    uint8_t *d = static_cast<uint8_t *>(dest);

    while (count > 0) {
        *d = static_cast<uint8_t>(value);
        d++;
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

void *kmalloc(const uint32_t size, bool align, uintptr_t *phys)
{
    static uintptr_t placement_address = reinterpret_cast<uintptr_t>(&_kernel_end);
    constexpr uintptr_t page_size      = 0x1000;
    constexpr uintptr_t page_mask      = page_size - 1;

    if (align && (placement_address & page_mask))
        placement_address = (placement_address + page_mask) & ~page_mask;

    if (phys)
        *phys = placement_address;

    const uintptr_t current_address = placement_address;
    placement_address += size;

    return reinterpret_cast<void *>(current_address);
}
