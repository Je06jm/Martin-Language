#ifndef MARTIN_TEST_TOKEN_LOGIC
#define MARTIN_TEST_TOKEN_LOGIC

#include "testing.hpp"

#include <generators/logical.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_logic : public Test {
    public:
        std::string GetName() const override {
            return "Token(Logic)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("and or not");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::KW_And,
                TokenType::Type::KW_Or,
                TokenType::Type::KW_Not
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif