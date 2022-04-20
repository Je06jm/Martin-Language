#ifndef MARTIN_TEST_TOKEN_EXTERN
#define MARTIN_TEST_TOKEN_EXTERN

#include "testing.hpp"

#include <generators/extern.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_extern : public Test {
    public:
        std::string GetName() const override {
            return "Token(Extern)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("extern");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::KW_Extern
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif