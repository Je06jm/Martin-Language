#include <unicode.hpp>

#include <string.h>

namespace Martin {

    bool unicode_validate(const uint8_t* string, UnicodeType type) {
        bool found_end = false;
        uint32_t value;

        if ((string[0] == 0xef) && (string[1] == 0xbb) && (string[2] == 0xbf))
            string += 3;
        
        else if ((string[0] == 0xff) && (string[1] == 0xfe) && (string[2] == 0) && (string[3] == 0))
            string += 4;
        
        else if ((string[0] == 0) && (string[1] == 0) && (string[3] == 0xfe) && (string[4] == 0xff))
            string += 4;
        
        else if ((string[0] == 0xff) && (string[1] == 0xfe))
            string += 2;
        
        else if ((string[0] == 0xfe) && (string[1] == 0xff))
            string += 2;

        while (!found_end) {
            switch (type) {
                case UnicodeType_8Bits:
                    if (((string[0] & 0b11111000) == 0b11110000) &&
                        (((string[1] & 0b11000000) != 0b10000000) ||
                        ((string[2] & 0b11000000) != 0b10000000) ||
                        ((string[3] & 0b11000000) != 0b10000000))
                    )
                        return false;

                    else if (((string[0] & 0b11110000) == 0b11100000) &&
                        (((string[1] & 0b11000000) != 0b10000000) ||
                        ((string[2] & 0b11000000) != 0b10000000))
                    )
                        return false;
                    
                    else if (((string[0] & 0b11100000) == 0b11000000) &&
                        ((string[1] & 0b11000000) != 0b10000000)
                    )
                        return false;
                    
                    else if (!((string[0] & 0b10000000) == 0))
                        return false;
                    
                    if ((string[0] & 0b11111000) == 0b11110000) {
                        value |= ((uint32_t)string[0] & 0b111) << 18;
                        value |= ((uint32_t)string[1] & 0b111111) << 12;
                        value |= ((uint32_t)string[2] & 0b111111) << 6;
                        value |= ((uint32_t)string[3] & 0b111111);
                        string += 4;
                    } else if ((string[0] & 0b11110000) == 0b11100000) {
                        value |= ((uint32_t)string[0] & 0b1111) << 12;
                        value |= ((uint32_t)string[1] & 0b111111) << 6;
                        value |= ((uint32_t)string[2] & 0b111111);
                        string += 3;
                    } else if ((string[0] & 0b11100000) == 0b11000000) {
                        value |= ((uint32_t)string[0] & 0b11111) << 6;
                        value |= ((uint32_t)string[1] & 0b111111);
                        string += 2;
                    } else {
                        value = (uint32_t)string[0];
                        string++;
                    }

                    break;

                case UnicodeType_16BitsLittle:
                    if (((string[2] & 0b11111100) == 0b11011000) &&
                        ((string[0] & 0b11111100) != 0b11011100)
                    )
                        return false;
                        
                    else if ((string[2] & 0b11111100) == 0b11011100)
                        return false;

                    value = (uint32_t)string[0];
                    value |= ((uint32_t)string[1]) << 8;

                    if ((string[2] & 0b11111100) == 0b11011000) {
                        string += 2;
                        uint16_t temp = 0;
                        temp |= (uint16_t)string[0];
                        temp |= ((uint16_t)string[1]) << 8;

                        temp &= 0b1111111111;
                        value &= 0b1111111111;
                        value <<= 10;
                        value |= (uint32_t)temp;
                    }

                    if ((value >= 0xd800) && (value <= 0xdfff))
                        return false;

                    string += 2;

                    break;
                    
                case UnicodeType_16BitsBig: 
                    if (((string[3] & 0b11111100) == 0b11011000) &&
                        ((string[1] & 0b11111100) != 0b11011100)
                    )
                        return false;
                    
                    else if ((string[3] & 0b11111100) == 0b11011100)
                        return false;
                    
                    value = (uint32_t)string[1];
                    value |= ((uint32_t)string[0]) << 8;

                    if ((string[3] & 0b11111100) == 0b11011000) {
                        string += 2;
                        uint16_t temp = 0;
                        temp |= (uint16_t)string[1];
                        temp |= ((uint16_t)string[0]) << 8;

                        temp &= 0b1111111111;
                        value &= 0b1111111111;
                        value <<= 10;
                        value |= (uint32_t)temp;
                    }

                    if ((value >= 0xd800) && (value <= 0xdfff))
                        return false;

                    string += 2;

                    break;

                case UnicodeType_32BitsLittle:
                    value = (uint32_t)string[0];
                    value |= ((uint32_t)string[1]) << 8;
                    value |= ((uint32_t)string[2]) << 16;
                    value |= ((uint32_t)string[3]) << 24;

                    string += 4;

                    break;

                case UnicodeType_32BitsBig:
                    value = (uint32_t)string[3];
                    value |= ((uint32_t)string[2]) << 8;
                    value |= ((uint32_t)string[1]) << 16;
                    value |= ((uint32_t)string[0]) << 24;

                    string += 4;

                    break;
            }

            if (value > 0x10ffff)
                return false;
            
            if (value == 0)
                found_end = true;
        }

        return true;
    }

    uint32_t unicode_length(const uint8_t* string, UnicodeType type, uint32_t* bytes, bool* found_bom) {
        uint32_t length = 0;
        bool found_end = false;

        const uint8_t* start = string;

        if (found_bom != nullptr)
            *found_bom = false;

        if ((string[0] == 0xef) && (string[1] == 0xbb) && (string[2] == 0xbf)) {
            if (type == UnicodeType_8Bits) {
                // Who adds the BOM to UTF-8?!?
                string += 3;

                if (found_bom != nullptr)
                    *found_bom = true;
            }
        }

        while (!found_end) {
            switch (type) {
                case UnicodeType_8Bits: {
                    uint32_t value = 0;
                    
                    if ((string[0] & 0b11111000) == 0b11110000) {
                        value |= ((uint32_t)string[0] & 0b111) << 18;
                        value |= ((uint32_t)string[1] & 0b111111) << 12;
                        value |= ((uint32_t)string[2] & 0b111111) << 6;
                        value |= ((uint32_t)string[3] & 0b111111);
                        string += 4;
                    } else if ((string[0] & 0b11110000) == 0b11100000) {
                        value |= ((uint32_t)string[0] & 0b1111) << 12;
                        value |= ((uint32_t)string[1] & 0b111111) << 6;
                        value |= ((uint32_t)string[2] & 0b111111);
                        string += 3;
                    } else if ((string[0] & 0b11100000) == 0b11000000) {
                        value |= ((uint32_t)string[0] & 0b11111) << 6;
                        value |= ((uint32_t)string[1] & 0b111111);
                        string += 2;
                    } else {
                        value = (uint32_t)string[0];
                        string++;
                    }

                    if (value == 0)
                        found_end = true;

                } break;

                case UnicodeType_16BitsLittle:
                case UnicodeType_16BitsBig: {
                    uint16_t value = 0;

                    if (type == UnicodeType_16BitsLittle) {
                        value |= (uint16_t)string[0];
                        value |= ((uint16_t)string[1]) << 8;
                    } else {
                        value |= (uint16_t)string[1];
                        value |= ((uint16_t)string[0]) << 8;
                    }

                    if (value == 0xfeff) {
                        string += 2;
                        length--;
                        if (found_bom != nullptr)
                            *found_bom = true;
                    } else if ((value & 0b1111110000000000) == 0b1101100000000000) {
                        string += 2;
                        uint16_t temp = 0;
                        if (type == UnicodeType_16BitsLittle) {
                            temp |= (uint16_t)string[0];
                            temp |= ((uint16_t)string[1]) << 8;
                        } else {
                            temp |= (uint16_t)string[1];
                            temp |= ((uint16_t)string[0]) << 8;
                        }

                        temp &= 0b1111111111;
                        value &= 0b1111111111;
                        value <<= 10;
                        value |= (uint32_t)temp;
                    }

                    if (value == 0) {
                        found_end = true;
                        break;
                    } else
                        string += 2;
                } break;
                    
                case UnicodeType_32BitsLittle:
                case UnicodeType_32BitsBig: {
                    uint32_t value = 0;

                    if (type == UnicodeType_32BitsLittle) {
                        value |= (uint32_t)string[0];
                        value |= ((uint32_t)string[1]) << 8;
                        value |= ((uint32_t)string[2]) << 16;
                        value |= ((uint32_t)string[3]) << 24;
                    } else {
                        value |= (uint32_t)string[3];
                        value |= ((uint32_t)string[2]) << 8;
                        value |= ((uint32_t)string[1]) << 16;
                        value |= ((uint32_t)string[0]) << 24;
                    }

                    if (value == 0) {
                        found_end = true;
                        break;
                    } else if (value == 0x0000feff) {
                        string += 4;
                        length--;
                        if (found_bom != nullptr)
                            *found_bom = true;
                    } else
                        string += 4;
                } break;
            }

            if (!found_end)
                length++;
        }

        if (bytes != nullptr) {
            uintmax_t ptr = (uintmax_t)string;
            ptr -= (uintmax_t)start;
            *bytes = (uint32_t)ptr;
        }

        return length;
    }

    uint8_t* unicode_convert(const uint8_t* string, UnicodeType from, UnicodeType to) {
        bool found_bom;
        uint32_t length = unicode_length(string, from, nullptr, &found_bom) + 1;

        uint8_t* new_str = new uint8_t[(length + 1) * 4]; // Allocate the maximum size possible
        uint8_t* uni = new_str;
        
        if (found_bom) {
            switch (from) {
                case UnicodeType_8Bits:
                    string += 3;
                    break;

                case UnicodeType_16BitsLittle:
                case UnicodeType_16BitsBig:
                    string += 2;
                    break;

                case UnicodeType_32BitsLittle:
                case UnicodeType_32BitsBig:
                    string += 4;
                    break;
            }
        }

        length = 0;

        bool found_end = false;

        while (!found_end) {
            uint32_t value = 0;
            switch (from) {
                case UnicodeType_8Bits:
                    if ((string[0] & 0b11111000) == 0b11110000) {
                        value |= ((uint32_t)string[0] & 0b111) << 18;
                        value |= ((uint32_t)string[1] & 0b111111) << 12;
                        value |= ((uint32_t)string[2] & 0b111111) << 6;
                        value |= ((uint32_t)string[3] & 0b111111);
                        string += 4;
                    } else if ((string[0] & 0b11110000) == 0b11100000) {
                        value |= ((uint32_t)string[0] & 0b1111) << 12;
                        value |= ((uint32_t)string[1] & 0b111111) << 6;
                        value |= ((uint32_t)string[2] & 0b111111);
                        string += 3;
                    } else if ((string[0] & 0b11100000) == 0b11000000) {
                        value |= ((uint32_t)string[0] & 0b11111) << 6;
                        value |= ((uint32_t)string[1] & 0b111111);
                        string += 2;
                    } else {
                        value = (uint32_t)string[0];
                        string++;
                    }

                    if (value == 0)
                        found_end = true;

                    break;

                case UnicodeType_16BitsLittle:
                case UnicodeType_16BitsBig:
                    if (from == UnicodeType_16BitsLittle) {
                        value |= (uint32_t)string[0];
                        value |= ((uint32_t)string[1]) << 8;
                    } else {
                        value |= (uint32_t)string[1];
                        value |= ((uint32_t)string[0]) << 8;
                    }

                    if ((value & 0b1111110000000000) == 0b1101100000000000) {
                        string += 2;
                        uint16_t temp = 0;
                        if (from == UnicodeType_16BitsLittle) {
                            temp |= (uint32_t)string[0];
                            temp |= ((uint32_t)string[1]) << 8;
                        } else {
                            temp |= (uint32_t)string[1];
                            temp |= ((uint32_t)string[0]) << 8;
                        }

                        temp &= 0b1111111111;
                        value &= 0b1111111111;
                        value <<= 10;
                        value |= temp;
                    }

                    if (value == 0)
                        found_end = true;
                    
                    else
                        string += 2;
                    
                    break;

                case UnicodeType_32BitsLittle:
                case UnicodeType_32BitsBig:
                    if (from == UnicodeType_32BitsLittle) {
                        value |= (uint32_t)string[0];
                        value |= ((uint32_t)string[1]) << 8;
                        value |= ((uint32_t)string[2]) << 16;
                        value |= ((uint32_t)string[3]) << 24;
                    } else {
                        value |= (uint32_t)string[3];
                        value |= ((uint32_t)string[2]) << 8;
                        value |= ((uint32_t)string[1]) << 16;
                        value |= ((uint32_t)string[0]) << 24;
                    }

                    if (value == 0)
                        found_end = true;
                    
                    else
                        string += 4;
                    
                    break;
            }

            switch (to) {
                case UnicodeType_8Bits:
                    if (value > 0xffff) {
                        uint8_t temp = value >> 18;
                        uni[0] = 0b11110000 | (temp & 0b111);
                        temp = value >> 12;
                        uni[1] = 0b10000000 | (temp & 0b111111);
                        temp = value >> 6;
                        uni[2] = 0b10000000 | (temp & 0b111111);
                        temp = value;
                        uni[3] = 0b10000000 | (temp & 0b111111);

                        uni += 4;
                    
                    } else if (value > 0x7ff) {
                        uint8_t temp = value >> 12;
                        uni[0] = 0b11100000 | (temp & 0b1111);
                        temp = value >> 6;
                        uni[1] = 0b10000000 | (temp & 0b111111);
                        temp = value;
                        uni[2] = 0b10000000 | (temp & 0b111111);

                        uni += 3;

                    } else if (value > 0x7f) {
                        uint8_t temp = value >> 6;
                        uni[0] = 0b11000000 | (temp & 0b11111);
                        temp = value;
                        uni[1] = 0b10000000 | (temp & 0b111111);

                        uni += 2;

                    } else {
                        uni[0] = (uint8_t)value;

                        uni++;
                    }

                    break;

                case UnicodeType_16BitsLittle:
                case UnicodeType_16BitsBig:
                    if (value > 0b1111111111) {
                        uint16_t second = value & 0b1111111111;
                        uint16_t first = (value >> 10) & 0b1111111111;

                        second |= 0xDC00;
                        first |= 0xD800;

                        if (to == UnicodeType_16BitsLittle) {
                            uni[0] = (uint8_t)first;
                            uni[1] = (uint8_t)(first >> 8);
                            uni[2] = (uint8_t)second;
                            uni[3] = (uint8_t)(second >> 8);
                        } else {
                            uni[0] = (uint8_t)(first >> 8);
                            uni[1] = (uint8_t)first;
                            uni[2] = (uint8_t)(second >> 8);
                            uni[3] = (uint8_t)second;
                        }

                        uni += 4;
                    } else {
                        if (to == UnicodeType_16BitsLittle) {
                            uni[0] = (uint8_t)value;
                            uni[1] = (uint8_t)(value >> 8);
                        } else {
                            uni[0] = (uint8_t)(value >> 8);
                            uni[1] = (uint8_t)value;
                        }

                        uni += 2;
                    }
                    break;

                case UnicodeType_32BitsLittle:
                    uni[0] = (uint8_t)value;
                    uni[1] = (uint8_t)(value >> 8);
                    uni[2] = (uint8_t)(value >> 16);
                    uni[3] = (uint8_t)(value >> 24);

                    uni += 4;
                    break;

                case UnicodeType_32BitsBig:
                    uni[3] = (uint8_t)value;
                    uni[2] = (uint8_t)(value >> 8);
                    uni[1] = (uint8_t)(value >> 16);
                    uni[0] = (uint8_t)(value >> 24);

                    uni += 4;
                    break;
            }
        }
        
        uintmax_t true_length = (uintmax_t)uni;
        true_length -= (uintmax_t)new_str;

        uint8_t* final_str = new uint8_t[true_length];
        memcpy(final_str, new_str, true_length);

        delete[] new_str;

        return final_str;
    }

    uint8_t* unicode_without_bom(const uint8_t* string, UnicodeType type) {
        uint32_t length = 0;
        uint8_t zero_length = 0;
        const uint8_t* uni;

        if ((string[0] == 0xef) && (string[1] == 0xbb) && (string[2] == 0xbf)) {
            if (type == UnicodeType_8Bits) {
                length = unicode_length(&string[3], type);
                zero_length = 1;
                uni = &string[3];
            } else {
                return nullptr;
            }
        } else if ((string[0] == 0xfe) && (string[1] == 0xff) && (string[2] == 0) && (string[3] == 0)) {
            if (type == UnicodeType_32BitsLittle) {
                length = unicode_length(&string[4], type);
                zero_length = 4;
                uni = &string[4];
            } else {
                return nullptr;
            }
        } else if ((string[0] == 0) && (string[1] == 0) && (string[2] == 0xff) && (string[3] == 0xfe)) {
            if (type == UnicodeType_32BitsBig) {
                length = unicode_length(&string[4], type);
                zero_length = 4;
                uni = &string[4];
            } else {
                return nullptr;
            }
        } else if ((string[0] == 0xff) && (string[1] == 0xfe)) {
            if (type == UnicodeType_16BitsLittle) {
                length = unicode_length(&string[2], type);
                zero_length = 2;
                uni = &string[2];
            } else {
                return nullptr;
            }
        } else if ((string[0] == 0xfe) && (string[1] == 0xff)) {
            if (type == UnicodeType_16BitsBig) {
                length = unicode_length(&string[2], type);
                zero_length = 2;
                uni = &string[2];
            } else {
                return nullptr;
            }
        } else {
            length = unicode_length(string, type);
            switch (type) {
                case UnicodeType_8Bits:
                    zero_length = 1;
                    break;
                
                case UnicodeType_16BitsLittle:
                case UnicodeType_16BitsBig:
                    zero_length = 2;
                    break;
                
                case UnicodeType_32BitsLittle:
                case UnicodeType_32BitsBig:
                    zero_length = 4;
                    break;
            }

            uni = string;
        }

        uint8_t* new_str = new uint8_t[length + zero_length];
        memcpy(new_str, uni, length + zero_length);

        return new_str;
    }

}