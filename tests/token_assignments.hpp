#ifndef MARTIN_TEST_TOKEN_ASSIGNMENTS
#define MARTIN_TEST_TOKEN_ASSIGNMENTS

#include "testing.hpp"

#include <generators/assignments.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"

namespace Martin {
    class Test_token_assignments : public Test {
    public:
        std::string GetName() const override {
            return "Token(Assignments)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("= := += -= *= /= %= **= &= |= ^= ~= <<= >>=");
            const std::vector<TokenType::Type> types = {
                TokenType::Type::SYM_Assign,
                TokenType::Type::SYM_TypeAssign,
                TokenType::Type::SYM_AssignAdd,
                TokenType::Type::SYM_AssignSub,
                TokenType::Type::SYM_AssignMul,
                TokenType::Type::SYM_AssignDiv,
                TokenType::Type::SYM_AssignMod,
                TokenType::Type::SYM_AssignPow,
                TokenType::Type::SYM_AssignBitAnd,
                TokenType::Type::SYM_AssignBitOr,
                TokenType::Type::SYM_AssignBitXOr,
                TokenType::Type::SYM_AssignBitNot,
                TokenType::Type::SYM_AssignBitShiftLeft,
                TokenType::Type::SYM_AssignBitShiftRight
            };
            
            if (!ValidateTokenList(tree, error)) return false;
            return ValidateExpectedTokenList(tree, types, error);
        }
    };
}
#endif