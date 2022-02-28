#include <parse.hpp>

#include "generators/addsub.hpp"
#include "generators/muldivmod.hpp"
#include "generators/pow.hpp"
#include "generators/bitwise.hpp"
#include "generators/equality.hpp"
#include "generators/logical.hpp"
#include "generators/enclosures.hpp"
#include "generators/dot.hpp"
#include "generators/as.hpp"
#include "generators/comma.hpp"
#include "generators/fromimport.hpp"

namespace Martin {

    Parser ParserSingleton;

    Parser::Parser() {
        generators.push_back(TreeGenerator(new StructEnclosuresTreeGenerator));
        generators.push_back(TreeGenerator(new OPDotTreeGenerator));
        generators.push_back(TreeGenerator(new StructAsTreeGenerator));
        generators.push_back(TreeGenerator(new OPMulDivModTreeGenerator));
        generators.push_back(TreeGenerator(new OPPowTreeGenerator));
        generators.push_back(TreeGenerator(new OPAddSubTreeGenerator));
        generators.push_back(TreeGenerator(new OPBitwiseTreeGenerator));
        generators.push_back(TreeGenerator(new OPEqualityTreeGenerator));
        generators.push_back(TreeGenerator(new OPNotLogicTreeGenerator));
        generators.push_back(TreeGenerator(new OPLogicalsTreeGenerator));
        generators.push_back(TreeGenerator(new StructCommaTreeGenerator));
        generators.push_back(TreeGenerator(new MiscFromImportTreeGenerator));
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

        Print("Parsing branch\n");
        for (auto it : *tree) {
            Print("$\n", *it);
        }

        for (auto gen : generators) {
            if (gen->IsReversed()) {
                index = end - 1;
                size_t accum = 0;
                while ((index < end) && (index >= start) && (index < tree->size())) {
                    removed = gen->ProcessBranch(tree, index, end);
                    if (removed)
                        accum += removed - 1;
                    
                    index--;
                }
                end -= accum;
            } else {
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

}