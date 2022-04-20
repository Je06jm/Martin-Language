#ifndef MARTIN_TEST_TOKEN_EQUALITY
#define MARTIN_TEST_TOKEN_EQUALITY

#include "testing.hpp"

#include <generators/equality.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_equality : public Test {
    public:
        std::string GetName() const override {
            return "Token(Equality)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("== != < > <= >=");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::SYM_Equals,
                TokenType::Type::SYM_NotEquals,
                TokenType::Type::SYM_LessThan,
                TokenType::Type::SYM_GreaterThan,
                TokenType::Type::SYM_LessThanEquals,
                TokenType::Type::SYM_GreaterThanEquals
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif