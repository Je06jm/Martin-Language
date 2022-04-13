#ifndef MARTIN_TEST_TOKEN_BITWISE
#define MARTIN_TEST_TOKEN_BITWISE

#include "testing.hpp"

#include <generators/bitwise.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"

namespace Martin {
    class Test_token_bitwise : public Test {
    public:
        std::string GetName() const override {
            return "Token(Bitwise)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("& | ^ ~ << >>");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::SYM_BitAnd,
                TokenType::Type::SYM_BitOr,
                TokenType::Type::SYM_BitXOr,
                TokenType::Type::SYM_BitNot,
                TokenType::Type::SYM_BitShiftLeft,
                TokenType::Type::SYM_BitShiftRight
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif