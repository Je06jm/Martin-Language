#ifndef MARTIN_UNICODE
#define MARTIN_UNICODE

#include <stdint.h>
#include "platform.hpp"

namespace Martin {

typedef enum {
    UnicodeType_8Bits,

    UnicodeType_16BitsLittle,
    UnicodeType_16BitsBig,

    UnicodeType_32BitsLittle,
    UnicodeType_32BitsBig
} UnicodeType;

#ifdef cpu_x86

inline constexpr UnicodeType UnicodeType_16Bits = UnicodeType_16BitsLittle;
inline constexpr UnicodeType UnicodeType_32Bits = UnicodeType_32BitsLittle;

#endif

bool unicode_validate(const uint8_t* string, UnicodeType type);
uint32_t unicode_length(const uint8_t* string, UnicodeType type, uint32_t* bytes = nullptr, bool* found_bom = nullptr);
uint8_t* unicode_convert(const uint8_t* string, UnicodeType from, UnicodeType to);
uint8_t* unicode_without_bom(const uint8_t* string, UnicodeType type);

}

#endif