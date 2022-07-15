#include <lambda.hpp>

#include <stdint.h>

#include <generators/funclambda.hpp>

namespace Martin {

    uint32_t num = 0;

    void ResetLambdaCounter() {
        num = 0;
    }

    void ProcessLambdas(Tree tree, const std::string& module_name) {
        auto list = Parser::GetAllNodesOfType(tree, TreeNodeBase::Type::Misc_Lambda);

        for (auto node : list) {
            auto lambda = std::static_pointer_cast<LambdaTreeNode>(node);

            lambda->has_name = true;
            lambda->name = module_name + std::string("_lambda_") + std::to_string(num++);

            TreeNode op = TreeNode(new FuncTreeNode(lambda->arrow, lambda->scope));
            TokenNode token_node = TokenNode(new TokenNodeBase);
            token_node->node = op;
            tree->push_back(token_node);
        }
    }

}