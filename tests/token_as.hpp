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
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif