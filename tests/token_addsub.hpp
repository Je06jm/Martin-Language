#ifndef MARTIN_TEST_TOKEN_ADDSUB
#define MARTIN_TEST_TOKEN_ADDSUB

#include "testing.hpp"

#include <generators/addsub.hpp>

#include <tokens.hpp>

#include "helpers/validatetree.hpp"

namespace Martin {
    class Test_token_addsub : public Test {
    public:
        std::string GetName() const override {
            return "Token(AddSub)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("1 + b - 1.2f");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::Integer,
                TokenType::Type::SYM_Add,
                TokenType::Type::Identifier,
                TokenType::Type::SYM_Sub,
                TokenType::Type::FloatingSingle
            };

            if (!ValidateTokenList(tree, error)) return false;

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