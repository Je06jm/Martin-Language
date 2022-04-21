#ifndef MARTIN_TEST_TOKEN_IN
#define MARTIN_TEST_TOKEN_IN

#include "testing.hpp"

#include <generators/in.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_in : public Test {
    public:
        std::string GetName() const override {
            return "Token(In)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("in");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::KW_In
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif