#include <parse.hpp>

#include "generators/addsub.hpp"
#include "generators/muldivmod.hpp"
#include "generators/pow.hpp"
#include "generators/bitwise.hpp"
#include "generators/equality.hpp"
#include "generators/logical.hpp"
#include "generators/enclosures.hpp"

namespace Martin {

    Parser ParserSingleton;

    Parser::Parser() {
        generators.push_back(TreeGenerator(new StructEnclosuresTreeGenerator));
        generators.push_back(TreeGenerator(new OPMulDivModTreeGenerator));
        generators.push_back(TreeGenerator(new OPPowTreeGenerator));
        generators.push_back(TreeGenerator(new OPAddSubTreeGenerator));
        generators.push_back(TreeGenerator(new OPBitwiseTreeGenerator));
        generators.push_back(TreeGenerator(new OPEqualityTreeGenerator));
        generators.push_back(TreeGenerator(new OPLogicalsTreeGenerator));
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