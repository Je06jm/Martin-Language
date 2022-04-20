#ifndef MARTIN_TEST_TOKEN_FLOWCONTROLS
#define MARTIN_TEST_TOKEN_FLOWCONTROLS

#include "testing.hpp"

#include <generators/flowcontrols.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_token_flowcontrols : public Test {
    public:
        std::string GetName() const override {
            return "Token(FlowControls)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("if elif else while for foreach match switch continue break return ");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::KW_If,
                TokenType::Type::KW_Elif,
                TokenType::Type::KW_Else,
                TokenType::Type::KW_While,
                TokenType::Type::KW_For,
                TokenType::Type::KW_Foreach,
                TokenType::Type::KW_Match,
                TokenType::Type::KW_Switch,
                TokenType::Type::KW_Continue,
                TokenType::Type::KW_Break,
                TokenType::Type::KW_Return
            };

            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif