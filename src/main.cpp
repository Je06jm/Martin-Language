#define DEBUG_PRINT

#include <unicode.hpp>

#include <values.hpp>
#include <tuple.hpp>

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>

#include <tokens.hpp>
#include <parse.hpp>
#include <logging.hpp>

Martin::UnicodeType input_unicode_type = Martin::UnicodeType_8Bits;

namespace Martin {

    extern Value program;

}

int main(int argc, char** argv) {
    argc--; argv++;

    if (argc < 1) {
        Martin::Warning("No file provided\n");
        return 0;
    }

    std::ifstream file(argv[0]);
    if (!file.is_open()) {
        Martin::Error("Could not open file: $\n", (const char*)argv[0]);
        return 0;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::string code = buffer.str();

    Martin::Tokenizer tokenizer;
    auto arr = tokenizer.TokenizeString(code);

#ifdef MARTIN_DEBUG
    for (auto token : *arr) {
        Martin::Print("$: $\n", token->GetLineNumber(), token->GetName());
    }
#else
    Martin::Print("Debug mode is off\n");
#endif

    std::string error;

    Martin::Print("$\n", Martin::ParserSingleton);

    auto tree = Martin::ParserSingleton.ParseTokens(arr, error);

    if (tree == nullptr)
        Martin::Error("Parsing error: $\n", error);

    else {
        // Compile / Run code here
        for (auto item : *tree) {
            if (item->is_token) 
                Martin::Print("Parsed token\n");
            
            else {
                Martin::Print("Parsed node: $\n", *item);
            }
                
        }
    }

    return 0;
}