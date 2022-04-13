#ifndef MARTIN_TEST_TOKEN_CLASS
#define MARTIN_TEST_TOKEN_CLASS

#include "testing.hpp"

#include <generators/class.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"

namespace Martin {
    class Test_token_class : public Test {
    public:
        std::string GetName() const override {
            return "Token(Class)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("class a : public b {}");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::KW_Class,
                TokenType::Type::Identifier,
                TokenType::Type::SYM_Colon,
                TokenType::Type::KW_Public,
                TokenType::Type::Identifier,
                TokenType::Type::SYM_OpenCurly,
                TokenType::Type::SYM_CloseCurly
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif