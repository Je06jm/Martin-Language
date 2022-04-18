#ifndef MARTIN_TEST_TOKEN_COMMA
#define MARTIN_TEST_TOKEN_COMMA

#include "testing.hpp"

#include <generators/comma.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_comma : public Test {
    public:
        std::string GetName() const override {
            return "Token(Comma)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString(",");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::SYM_Comma
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif