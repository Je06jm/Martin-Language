#ifndef MARTIN_TEST_TOKEN_DATATYPES
#define MARTIN_TEST_TOKEN_DATATYPES

#include "testing.hpp"

#include <generators/datatypes.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_datatypes : public Test {
    public:
        std::string GetName() const override {
            return "Token(DataTypes)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("struct union enum ");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::KW_Struct,
                TokenType::Type::KW_Union,
                TokenType::Type::KW_Enum
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif