#ifndef MARTIN_TEST_TOKEN_FROMIMPORT
#define MARTIN_TEST_TOKEN_FROMIMPORT

#include "testing.hpp"

#include <generators/fromimport.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_fromimport : public Test {
    public:
        std::string GetName() const override {
            return "Token(FromImport)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("import from ");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::KW_Import,
                TokenType::Type::KW_From
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif