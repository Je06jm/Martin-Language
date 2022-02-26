#include <parse.hpp>

#include "generators/addsub.hpp"
#include "generators/muldivmod.hpp"

namespace Martin {

    Parser::Parser() {
        generators.push_back(TreeGenerator(new OPMulDivModTreeGenerator));
        generators.push_back(TreeGenerator(new OPAddSubTreeGenerator));
    }

    Tree Parser::ParseTokens(TokenList tokens, std::string& error_msg) {
        Tree tree = Tree(new std::vector<TokenNode>);

        tree->reserve(tokens->size());
        TokenNode token_node;

        for (auto tk : *tokens) {
            token_node = TokenNode(new TokenNodeBase);
            token_node->token = tk;
            token_node->is_token = true;
            tree->push_back(token_node);
        }

        ParseBranch(tree, 0, tree->size());

        return tree;
    }

    void Parser::ParseBranch(Tree tree, size_t start, size_t end) {
        size_t removed, index;

        for (auto gen : generators) {
            index = start;
            while ((index < end) && (index < tree->size())) {
                removed = gen->ProcessBranch(tree, index, end);
                if (removed)
                    end -= removed - 1;
                
                else
                    index++;
            }
        }
    }

}