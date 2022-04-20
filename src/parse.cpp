#include <parse.hpp>
#include <tokens.hpp>
#include <fstream>
#include <sstream>

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
#include "generators/definitions.hpp"
#include "generators/datatypes.hpp"
#include "generators/accesstypes.hpp"
#include "generators/assignments.hpp"
#include "generators/arrow.hpp"
#include "generators/flowcontrols.hpp"
#include "generators/in.hpp"
#include "generators/colon.hpp"
#include "generators/funclambda.hpp"
#include "generators/unsafe.hpp"
#include "generators/classtype.hpp"
#include "generators/classaccess.hpp"
#include "generators/class.hpp"
#include "generators/extern.hpp"
#include "generators/call.hpp"
#include "generators/gettersetter.hpp"
#include "generators/seperator.hpp"
#include "generators/rettypes.hpp"

namespace Martin {

    Parser ParserSingleton;

    Parser::Parser() {
        generators.push_back(TreeGenerator(new SeperatorGenerator));
        generators.push_back(TreeGenerator(new StructEnclosuresTreeGenerator));
        generators.push_back(TreeGenerator(new CallTreeGenerator));
        generators.push_back(TreeGenerator(new OPDotTreeGenerator));
        generators.push_back(TreeGenerator(new StructAsTreeGenerator));
        generators.push_back(TreeGenerator(new OPMulDivModTreeGenerator));
        generators.push_back(TreeGenerator(new OPPowTreeGenerator));
        generators.push_back(TreeGenerator(new OPAddSubTreeGenerator));
        generators.push_back(TreeGenerator(new OPBitwiseTreeGenerator));
        generators.push_back(TreeGenerator(new OPEqualityTreeGenerator));
        generators.push_back(TreeGenerator(new OPNotLogicTreeGenerator));
        generators.push_back(TreeGenerator(new OPLogicalsTreeGenerator));
        generators.push_back(TreeGenerator(new AccessTypesTreeGenerator));
        generators.push_back(TreeGenerator(new ArrowTreeGenerator));
        generators.push_back(TreeGenerator(new DefinitionsTreeGenerator));
        generators.push_back(TreeGenerator(new RetTypesTreeGenerator));
        generators.push_back(TreeGenerator(new DataTypesTreeGenerator));
        generators.push_back(TreeGenerator(new AssignmentsTreeGenerator));
        generators.push_back(TreeGenerator(new FlowControlsTreeGenerator));
        generators.push_back(TreeGenerator(new FuncLambdaTreeGenerator));
        generators.push_back(TreeGenerator(new ClassTypeTreeGenerator));
        generators.push_back(TreeGenerator(new GetterSetterTreeGenerator));
        generators.push_back(TreeGenerator(new ClassAccessTreeGenerator));
        generators.push_back(TreeGenerator(new UnsafeTreeGenerator));
        generators.push_back(TreeGenerator(new StructCommaTreeGenerator));
        generators.push_back(TreeGenerator(new MiscFromImportTreeGenerator));
        generators.push_back(TreeGenerator(new InTreeGenerator));
        generators.push_back(TreeGenerator(new ColonTreeGenerator));
        generators.push_back(TreeGenerator(new ClassTreeGenerator));
        generators.push_back(TreeGenerator(new ExternTreeGenerator));
    }

    Tree Parser::ParseFile(const std::string& path, std::string& error_msg) {
        std::ifstream file(path);
        if (!file.is_open()) {
            error_msg = Format("Could not open file: $", path);
            return nullptr;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        std::string code = buffer.str();

        return ParseString(code, error_msg);
    }

    Tree Parser::ParseString(const std::string& code, std::string& error_msg) {
        auto token_array = TokenizerSingleton.TokenizeString(code);
        auto tree = ParserSingleton.ParseTokens(token_array);

        // Run verifier here
        // Run codegen/code here

        return tree;
    }

    Tree Parser::ParseTokens(TokenList tokens) {
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