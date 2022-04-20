#ifndef MARTIN_TEST_TOKEN_ENCLOSURES
#define MARTIN_TEST_TOKEN_ENCLOSURES

#include "testing.hpp"

#include <generators/enclosures.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_enclosures : public Test {
    public:
        std::string GetName() const override {
            return "Token(Enclosures)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("() {} []");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::SYM_OpenParentheses,
                TokenType::Type::SYM_CloseParentheses,
                TokenType::Type::SYM_OpenCurly,
                TokenType::Type::SYM_CloseCurly,
                TokenType::Type::SYM_OpenBracket,
                TokenType::Type::SYM_CloseBracket
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif