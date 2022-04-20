#ifndef MARTIN_TEST_TOKEN_DEFINITIONS
#define MARTIN_TEST_TOKEN_DEFINITIONS

#include "testing.hpp"

#include <generators/definitions.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_definitions : public Test {
    public:
        std::string GetName() const override {
            return "Token(Definitions)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("let set const constexpr ");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::KW_Let,
                TokenType::Type::KW_Set,
                TokenType::Type::KW_Const,
                TokenType::Type::KW_Constexpr
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif