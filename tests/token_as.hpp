#ifndef MARTIN_TEST_TOKEN_AS
#define MARTIN_TEST_TOKEN_AS

#include "testing.hpp"

#include <generators/as.hpp>

namespace Martin {
    class Test_token_as : public Test {
    public:
        std::string GetName() const override {
            return "Token(As)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("What as no");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::Identifier,
                TokenType::Type::KW_As,
                TokenType::Type::Identifier
            };

            if (!ValidateTokenList(tree, error)) return false;

            for (size_t i = 0; i < tree->size(); i++) {
                if (i >= types.size())
                    break;
                
                if ((*tree)[i]->GetType() != types[i]) {
                    error = Martin::Format("Tokenizer returned the wrong token $ at $, $", (*tree)[i]->GetName(), (*tree)[i]->GetLineNumber(), i);
                    return false;
                }
            }

            return true;
        }
    };
}
#endif