#define DEBUG_PRINT

#include <unicode.hpp>

#include <values.hpp>
#include <tuple.hpp>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <tokens.hpp>

UnicodeType input_unicode_type = UnicodeType_8Bits;

namespace Martin {

    extern Value program;

}

int main(int argc, char** argv) {
    argc--; argv++;

    if (argc < 1) {
        std::cout << "Expected file\n";
        return 0;
    }

    std::ifstream file(argv[0]);
    if (!file.is_open()) {
        std::cout << "Could not open file " << argv[0] << "\n";
        return 0;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string code = buffer.str();

    Martin::InitTokenizer();
    auto arr = Martin::Tokenize(code);

#ifdef MARTIN_DEBUG
    for (auto token : *arr) {
        std::cout << token->GetLineNumber() << ": ";
        std::cout << token->GetName() << "\n";
    }
#else
    std::cout << "Debug mode is off\n";
#endif

    return 0;
}