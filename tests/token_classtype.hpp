#ifndef MARTIN_TEST_TOKEN_CLASSTYPE
#define MARTIN_TEST_TOKEN_CLASSTYPE

#include "testing.hpp"

#include <generators/classtype.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_classtype : public Test {
    public:
        std::string GetName() const override {
            return "Token(ClassType)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("virtual override static");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::KW_Virtual,
                TokenType::Type::KW_Override,
                TokenType::Type::KW_Static
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif