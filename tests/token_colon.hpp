#ifndef MARTIN_TEST_TOKEN_COLON
#define MARTIN_TEST_TOKEN_COLON

#include "testing.hpp"

#include <generators/colon.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_colon : public Test {
    public:
        std::string GetName() const override {
            return "Token(Colon)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString(":");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::SYM_Colon
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif