#ifndef MARTIN_TEST_TOKEN_POW
#define MARTIN_TEST_TOKEN_POW

#include "testing.hpp"

#include <generators/pow.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_pow : public Test {
    public:
        std::string GetName() const override {
            return "Token(Pow)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("**");
            std::vector<TokenType::Type> types = {
                TokenType::Type::SYM_Pow
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif