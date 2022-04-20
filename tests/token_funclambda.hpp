#ifndef MARTIN_TEST_TOKEN_FUNCLAMBDA
#define MARTIN_TEST_TOKEN_FUNCLAMBDA

#include "testing.hpp"

#include <generators/funclambda.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_funclambda : public Test {
    public:
        std::string GetName() const override {
            return "Token(FuncLambda)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("func lambda");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::KW_Func,
                TokenType::Type::KW_Lambda
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif