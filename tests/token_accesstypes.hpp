#ifndef MARTIN_TEST_TOKEN_ACCESS_TYPES
#define MARTIN_TEST_TOKEN_ACCESS_TYPES

#include "testing.hpp"

#include <generators/accesstypes.hpp>

#include <tokens.hpp>

namespace Martin {
    class Test_token_accesstypes : public Test {
    public:
        std::string GetName() const override {
            return "Token(AccessTypes)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("array[1] reference shared unique pointer ");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::KW_Array,
                TokenType::Type::SYM_OpenBracket,
                TokenType::Type::Integer,
                TokenType::Type::SYM_CloseBracket,
                TokenType::Type::KW_Reference,
                TokenType::Type::KW_Shared,
                TokenType::Type::KW_Unique,
                TokenType::Type::KW_Pointer
            };

            if (!tree) {
                error = "Tokenizer returned a nullptr";
                return false;
            }

            for (size_t i = 0; i < tree->size(); i++) {
                if (i >= types.size())
                    break;
                
                if ((*tree)[i]->GetType() != types[i]) {
                    error = Martin::Format("Tokenizer returned the wrong token $ at $", (*tree)[i]->GetName(), (*tree)[i]->GetLineNumber());
                    return false;
                }
            }

            return true;
        }
    };
}

#endif