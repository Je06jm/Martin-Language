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

int main(int argc, char** argv) {
    argc--; argv++;

    if (argc < 1) {
        Martin::Warning("No file provided\n");
        return 0;
    }

    std::string error;
    auto tree = Martin::ParserSingleton.ParseFile(argv[0], error);

    if (tree == nullptr)
        Martin::Error("Parsing error: $\n", error);

    else {
        // Compile / Run code here
        for (auto it : *tree) {
            if (it->is_token) {
                Martin::Warning("Found a token in tree vector($): $\n", it->token->GetLineNumber(), it->token->GetName());
            } else {
                Martin::Print("$\n", *it);
            }
        }

        Martin::Print("Nothing to do yet. If no warnings have printed, then the parser has accepted your syntax as valid.\n");
        Martin::Print("Note that this does not mean your syntax is valid as there is no verification run to make sure that the code is valid.\n");
        Martin::Print("For example, the following code will run as valid: \"func hello(func what() -> None{}) {}\"\n");
    }

    return 0;
}