#ifndef MARTIN_TEST_TOKEN_CALL
#define MARTIN_TEST_TOKEN_CALL

#include "testing.hpp"

#include <generators/call.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"

namespace Martin {
    class Test_token_call : public Test {
    public:
        std::string GetName() const override {
            return "Token(Call)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("a()");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::Identifier,
                TokenType::Type::SYM_OpenParentheses,
                TokenType::Type::SYM_CloseParentheses
            };

            if (!ValidateTokenList(tree, error)) return true;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif