#include "strhelper.hpp"

namespace Martin::StrHelper {

    bool IsFirstMatch(const void* string_ptr, const void* first_ptr) {
        const uint8_t* string = (const uint8_t*)string_ptr;
        const uint8_t* first = (const uint8_t*)first_ptr;
        
        while (true) {
            if (*first == '\0')
                return true;
            
            else if (*string == '\0')
                return false;
            
            else if (*first++ != *string++)
                return false;
        }
    }

    bool IsMatch(const std::string& in) {
        char delim = in[0];

        if ((delim != '\'') && (delim != '\"') && (delim != '`'))
            return false;
        

        for (size_t i = 1; i < in.length(); i++) {
            if (in[i] == delim)
                return true;
            
            else if (in[i] == '\\')
                i++;
        }

        return false;
    }

    std::shared_ptr<uint8_t[]> Process(std::string& in, UnicodeType utype) {
        char delim = in[0];
        in.erase(0, 1);
        
        std::string str = "";

        size_t i = 0;
        for (; i < in.length(); i++) {
            if (in[i] == delim)
                break;
            
            else if (in[i] == '\\') {
                i++;

                if (in[i] == 'n')
                    str += '\n';
                
                else if (in[i] == 'r')
                    str += '\r';
                
                else if (in[i] == 't')
                    str += '\t';
                
                else if (in[i] == '0')
                    str += '\0';
                
                else if (in[i] == '\'')
                    str += '\'';
                
                else if (in[i] == '\"')
                    str += '\"';
                
                else if (in[i] == '`')
                    str += '`';
                
                //else
                    // Todo: Error here

            } else
                str += in[i];
        }

        in.erase(0, i + 1);

        const uint8_t* c_str = (const uint8_t*)str.c_str();
        
        return std::shared_ptr<uint8_t[]>(unicode_convert(c_str, UnicodeType_8Bits, utype));
    }

}