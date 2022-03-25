#ifndef MARTIN_GENERATOR_SEPERATOR
#define MARTIN_GENERATOR_SEPERATOR

#include <parse.hpp>

namespace Martin {

    class SeperatorGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            Token last = GetIndexOrNullToken(tree, index-1);
            bool last_number = false;

            if (last) {
                last_number = (last->GetType() == TokenType::Type::Integer) ||
                    (last->GetType() == TokenType::Type::UInteger) ||
                    (last->GetType() == TokenType::Type::FloatingSingle) ||
                    (last->GetType() == TokenType::Type::FloatingDouble) ||
                    (last->GetType() == TokenType::Type::Identifier);
            }

            if (
                (sym && (sym->GetType() == TokenType::Type::Integer)) &&
                (last && last_number)
            ) {
                auto ptr = std::static_pointer_cast<intmax_t>(sym->GetData());

                if (*ptr < 0) {
                    *ptr = -(*ptr);
                    
                    auto num_tree = TokenizerSingleton.TokenizeString(std::to_string(*ptr));
                    TokenNode num_node = TokenNode(new TokenNodeBase);
                    num_node->is_token = true;
                    num_node->token = (*num_tree)[0];

                    ReplaceTreeWithTokenNode(tree, num_node, index, 1);

                    auto neg_tree = TokenizerSingleton.TokenizeString("-");
                    TokenNode node = TokenNode(new TokenNodeBase);
                    node->is_token = true;
                    node->token = (*neg_tree)[0];
                    tree->insert(tree->begin() + index, node);
                }
            } else if (
                (sym && (sym->GetType() == TokenType::Type::FloatingSingle)) &&
                (last && last_number)
            ) {
                auto ptr = std::static_pointer_cast<float>(sym->GetData());

                if (*ptr < 0.0f) {
                    *ptr = -(*ptr);
                    
                    auto num_tree = TokenizerSingleton.TokenizeString(std::to_string(*ptr) + "f");
                    TokenNode num_node = TokenNode(new TokenNodeBase);
                    num_node->is_token = true;
                    num_node->token = (*num_tree)[0];

                    ReplaceTreeWithTokenNode(tree, num_node, index, 1);

                    auto neg_tree = TokenizerSingleton.TokenizeString("-");
                    TokenNode node = TokenNode(new TokenNodeBase);
                    node->is_token = true;
                    node->token = (*neg_tree)[0];
                    tree->insert(tree->begin() + index, node);
                }
            } else if (
                (sym && (sym->GetType() == TokenType::Type::FloatingDouble)) &&
                (last && last_number)
            ) {
                auto ptr = std::static_pointer_cast<double>(sym->GetData());

                if (*ptr < 0.0) {
                    *ptr = -(*ptr);
                    
                    auto num_tree = TokenizerSingleton.TokenizeString(std::to_string(*ptr));
                    TokenNode num_node = TokenNode(new TokenNodeBase);
                    num_node->is_token = true;
                    num_node->token = (*num_tree)[0];

                    ReplaceTreeWithTokenNode(tree, num_node, index, 1);

                    auto neg_tree = TokenizerSingleton.TokenizeString("-");
                    TokenNode node = TokenNode(new TokenNodeBase);
                    node->is_token = true;
                    node->token = (*neg_tree)[0];
                    tree->insert(tree->begin() + index, node);
                }
            }

            return 0;
        }
    };

}

#endif