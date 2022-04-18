#ifndef MARTIN_TEST_TOKEN_CLASSACCESS
#define MARTIN_TEST_TOKEN_CLASSACCESS

#include "testing.hpp"

#include <generators/classaccess.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"

namespace Martin {
    class Test_token_classaccess : public Test {
    public:
        std::string GetName() const override {
            return "Token(ClassAccess)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("public private protected friend");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::KW_Public,
                TokenType::Type::KW_Private,
                TokenType::Type::KW_Protected,
                TokenType::Type::KW_Friend
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif