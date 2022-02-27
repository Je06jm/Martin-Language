#ifndef MARTIN_TYPE_HELPER
#define MARTIN_TYPE_HELPER

#include <parse.hpp>

namespace Martin::TypeHelper {

    bool IsPrimitiveLiteral(TokenNode node) {
        if (node->is_token) {
            TokenType::Type type = node->token->GetType();
            return (
                (type == TokenType::Type::Integer) ||
                (type == TokenType::Type::UInteger) ||
                (type == TokenType::Type::FloatingSingle) ||
                (type == TokenType::Type::FloatingDouble) ||
                (type == TokenType::Type::Boolean)
            );
        }

        return false;
    }

    bool CanDoMath(TokenNode node) {
        if (node->is_token) {
            TokenType::Type type = node->token->GetType();
            return (
                (type == TokenType::Type::Integer) ||
                (type == TokenType::Type::UInteger) ||
                (type == TokenType::Type::FloatingSingle) ||
                (type == TokenType::Type::FloatingDouble)
            );
        }

        return false;
    }

    bool CanDoLogic(TokenNode node) {
        if (node->is_token) {
            TokenType::Type type = node->token->GetType();
            return (
                (type == TokenType::Type::Boolean)
            );
        }

        return false;
    }

}

#endif