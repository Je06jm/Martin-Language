#ifndef MARTIN_TEST_TOKEN_ARROW
#define MARTIN_TEST_TOKEN_ARROW

#include "testing.hpp"

#include <generators/arrow.hpp>

#include <tokens.hpp>

#include "helpers/validatetree.hpp"

namespace Martin {
    class Test_token_arrow : public Test {
    public:
        std::string GetName() const override {
            return "Token(Arrow)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("() -> None");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::SYM_OpenParentheses,
                TokenType::Type::SYM_CloseParentheses,
                TokenType::Type::SYM_Arrow,
                TokenType::Type::Identifier
            };

            if (!ValidateTokenList(tree, error)) return false;

            for (size_t i = 0; i < tree->size(); i++) {
                if (i >= types.size())
                    break;
                
                if ((*tree)[i]->GetType() != types[i]) {
                    error = Format("Tokenizer returned the wrong token $ at $", (*tree)[i]->GetName(), (*tree)[i]->GetLineNumber());
                    return false;
                }
            }

            return true;
        }
    };
}
#endif