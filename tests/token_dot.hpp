#ifndef MARTIN_TEST_TOKEN_DOT
#define MARTIN_TEST_TOKEN_DOT

#include "testing.hpp"

#include <generators/dot.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_dot : public Test {
    public:
        std::string GetName() const override {
            return "Token(Dot)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString(".");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::SYM_Period
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif