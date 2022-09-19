#ifndef MARTIN_STR_HELPER
#define MARTIN_STR_HELPER

#include <string>
#include <memory>
#include <stdint.h>
#include <unicode.hpp>

namespace Martin::StrHelper {

    bool IsFirstMatch(const void* string, const void* first);

    bool IsMatch(const std::string& in);
    std::shared_ptr<uint8_t[]> Process(std::string& in, UnicodeType utype);

}

#endif