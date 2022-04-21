#ifndef MARTIN_TEST_TOKEN_MULDIVMOD
#define MARTIN_TEST_TOKEN_MULDIVMOD

#include "testing.hpp"

#include <generators/muldivmod.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_muldivmod : public Test {
    public:
        std::string GetName() const override {
            return "Token(MulDivMod)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("* / %");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::SYM_Mul,
                TokenType::Type::SYM_Div,
                TokenType::Type::SYM_Mod
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif