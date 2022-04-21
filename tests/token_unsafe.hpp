#ifndef MARTIN_TEST_TOKEN_UNSAFE
#define MARTIN_TEST_TOKEN_UNSAFE

#include "testing.hpp"

#include <generators/unsafe.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_unsafe : public Test {
    public:
        std::string GetName() const override {
            return "Token(Unsafe)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("unsafe");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::KW_Unsafe
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif