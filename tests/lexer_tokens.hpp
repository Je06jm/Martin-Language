#include "testing.hpp"

#include "sample.martin"

#include <tokens.hpp>

namespace Martin {
    class Test_lexer_tokens : public Test {
    public:
        std::string GetName() const override {
            return "Lexer(Tokens)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString(martin_sample);
            const std::vector<TokenType::Type> types = {
                TokenType::Type::KW_Func,
                TokenType::Type::Identifier,
                TokenType::Type::SYM_OpenParentheses,
                TokenType::Type::KW_Let,
                TokenType::Type::Identifier,
                TokenType::Type::SYM_Colon,
                TokenType::Type::Identifier,
                TokenType::Type::SYM_CloseParentheses,
                TokenType::Type::SYM_Arrow,
                TokenType::Type::Identifier,
                TokenType::Type::SYM_OpenCurly,
                TokenType::Type::KW_Set,
                TokenType::Type::Identifier,
                TokenType::Type::SYM_TypeAssign,
                TokenType::Type::FloatingDouble,
                TokenType::Type::KW_Return,
                TokenType::Type::Identifier,
                TokenType::Type::SYM_OpenParentheses,
                TokenType::Type::Identifier,
                TokenType::Type::SYM_CloseParentheses,
                TokenType::Type::SYM_CloseCurly
            };

            if (!tree) {
                error = "Tokenizer returned a nullptr\n";
            }

            for (size_t i = 0; i < tree->size(); i++) {
                if (i >= types.size())
                    break;

                if ((*tree)[i]->GetType() != types[i]) {
                    error = Martin::Format("Tokenizer returned the wrong token $ at $\n", (*tree)[i]->GetName(), (*tree)[i]->GetLineNumber());
                    return false;
                }
            }
            
            return true;
        }
    };
}