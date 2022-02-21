#define DEBUG_PRINT

#include <unicode.hpp>

#include <values.hpp>
#include <tuple.hpp>

#include <stdio.h>
#include <iostream>
#include <string>

#include <tokens.hpp>

UnicodeType input_unicode_type = UnicodeType_8Bits;

namespace Martin {

    extern Value program;

}

int main(int argc, char** argv) {
    argc--; argv++;

    const std::string code = "from 1.23 mystr";

    Martin::InitTokenizer();
    auto arr = Martin::Tokenize(code);

    for (auto token : *arr) {
        std::cout << token->GetLineNumber() << ": ";
        if (token->GetType() == Martin::TokenType::Type::UInteger)
            std::cout << "UInteger\n";
        
        else if (token->GetType() == Martin::TokenType::Type::Integer)
            std::cout << "Integer\n";
        
        else if (token->GetType() == Martin::TokenType::Type::FloatingSingle)
            std::cout << "FloatingSingle\n";
        
        else if (token->GetType() == Martin::TokenType::Type::FloatingDouble)
            std::cout << "FloatingDouble\n";
        
        else if (token->GetType() == Martin::TokenType::Type::String8)
            std::cout << "String8\n";
        
        else if (token->GetType() == Martin::TokenType::Type::String16)
            std::cout << "String16\n";

        else if (token->GetType() == Martin::TokenType::Type::String32)
            std::cout << "String32\n";

        else if (token->GetType() == Martin::TokenType::Type::String16l)
            std::cout << "String16l\n";

        else if (token->GetType() == Martin::TokenType::Type::String32l)
            std::cout << "String32l\n";

        else if (token->GetType() == Martin::TokenType::Type::String16b)
            std::cout << "String16b\n";

        else if (token->GetType() == Martin::TokenType::Type::String32b)
            std::cout << "String32b\n";

        else if (token->GetType() == Martin::TokenType::Type::Identifier)
            std::cout << "Identifier\n";

        else
            std::cout << "Unknown\n";
    }

    return 0;
}