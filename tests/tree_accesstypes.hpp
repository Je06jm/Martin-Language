#ifndef MARTIN_TEST_TREE_ACCESS_TYPES
#define MARTIN_TEST_TREE_ACCESS_TYPES

#include "testing.hpp"

#include <generators/accesstypes.hpp>
#include <generators/comma.hpp>

#include <tokens.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"

namespace Martin {
    class Test_tree_accesstypes : public Test {
    public:
        std::string GetName() const override {
            return "Tree(AccessTypes)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("1 2 3");
            auto tree2 = TokenizerSingleton.TokenizeString("Int32");

            if (!ValidateTokenList(tree, error, 3, ValidateSizeType::Equals)) return false;
            if (!ValidateTokenList(tree2, error, 1, ValidateSizeType::Equals)) return false;

            TokenNode one = GetTokenNodeFromTokenList(tree, 0);
            TokenNode id = GetTokenNodeFromTokenList(tree2, 0);

            std::vector<Token> nums;
            nums.push_back(one->token);

            {
                ArrayTypesTreeNode node(nums, id);

                if (!node.Valid()) {
                    error = "ArrayTypesTreeNode is not valid when given (Token(1), $)";
                    error = Format(error, id->node->GetName());
                    return false;
                }
            }

            {
                std::vector<Token> empty;
                ArrayTypesTreeNode node(empty, id);

                if (node.Valid()) {
                    error = "ArrayTypesTreeNode is valid when given (nullptr, $)";
                    error = Format(error, id->node->GetName());
                    return false;
                }
            }

            {
                ArrayTypesTreeNode node(nums, nullptr);

                if (node.Valid()) {
                    error = "ArrayTypesTreeNode is valid when given (Token(1), nullptr)";
                    return false;
                }
            }

            {
                std::vector<Token> empty;
                ArrayTypesTreeNode node(empty, nullptr);
                
                if (node.Valid()) {
                    error = "ArrayTypesTreeNode is valid when given (nullptr, nullptr)";
                    return false;
                }
            }

            {
                ReferenceTypesTreeNode node(id);

                if (!node.Valid()) {
                    error = "ReferenceTypesTreeNode is not valid when given ($)";
                    error = Format(error, *id);
                    return false;
                }
            }

            {
                ReferenceTypesTreeNode node(one);

                if (node.Valid()) {
                    error = "ReferenceTypesTreeNode is valid when given ($)";
                    error = Format(error, *one);
                    return false;
                }
            }

            {
                ReferenceTypesTreeNode node(nullptr);
                
                if (node.Valid()) {
                    error = "ReferenceTypesTreeNode is valid when given (nullptr)";
                    return false;
                }
            }

            {
                SharedTypesTreeNode node(id);

                if (!node.Valid()) {
                    error = "SharedTypesTreeNode is not valid when given ($)";
                    error = Format(error, *id);
                    return false;
                }
            }

            {
                SharedTypesTreeNode node(one);

                if (node.Valid()) {
                    error = "SharedTypesTreeNode is valid when given ($)";
                    error = Format(error, *one);
                    return false;
                }
            }

            {
                SharedTypesTreeNode node(nullptr);
                
                if (node.Valid()) {
                    error = "SharedTypesTreeNode is valid when given (nullptr)";
                    return false;
                }
            }

            {
                UniqueTypesTreeNode node(id);

                if (!node.Valid()) {
                    error = "UniqueTypesTreeNode is not valid when given ($)";
                    error = Format(error, *one);
                    return false;
                }
            }

            {
                UniqueTypesTreeNode node(one);

                if (node.Valid()) {
                    error = "UniqueTypesTreeNode is valid when given ($)";
                    error = Format(error, *id);
                    return false;
                }
            }

            {
                UniqueTypesTreeNode node(nullptr);
                
                if (node.Valid()) {
                    error = "UniqueTypesTreeNode is valid when given (nullptr)";
                    return false;
                }
            }

            {
                PointerTypesTreeNode node(id);

                if (!node.Valid()) {
                    error = "PointerTypesTreeNode is not valid when given ($)";
                    error = Format(error, *id);
                    return false;
                }
            }

            {
                PointerTypesTreeNode node(one);

                if (node.Valid()) {
                    error = "PointerTypesTreeNode is not valid when given ($)";
                    error = Format(error, *one);
                    return false;
                }
            }

            {
                PointerTypesTreeNode node(nullptr);
                
                if (node.Valid()) {
                    error = "PointerTypesTreeNode is valid when given (nullptr)";
                    return false;
                }
            }

            return true;
        }
    };
}

#endif