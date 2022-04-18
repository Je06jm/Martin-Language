#ifndef MARTIN_TEST_TREE_CLASSTYPE
#define MARTIN_TEST_TREE_CLASSTYPE

#include "testing.hpp"

#include <generators/classtype.hpp>
#include <generators/assignments.hpp>
#include <generators/definitions.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_classtype : public Test {
    public:
        std::string GetName() const override {
            return "Tree(ClassType)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("virtual override static a Int32");

            if (!ValidateTokenList(tree, error, 5)) return false;

            TokenNode lt_a = GetTokenNodeFromTokenList(tree, 3);
            TokenNode let_a, assigned_a;
            TokenNode int32 = GetTokenNodeFromTokenList(tree, 4);

            {
                // let a : Int32
                std::vector<Token> ids;
                ids.push_back(lt_a->token);

                TreeNode let = TreeNode(new LetTreeNode(ids, int32));

                let_a = TokenNode(new TokenNodeBase);
                let_a->node = let;
            }

            {
                // let a : Int32 = 3
                TreeNode assign = TreeNode(new AssignTreeNode(let_a, lt_a));

                assigned_a = TokenNode(new TokenNodeBase);
                assigned_a->node = assign;
            }


            SUBTEST_TREE_SINGLE("virtual let a : Int32", let_a, ClassTypeVirtualTreeNode, true);
            SUBTEST_TREE_SINGLE("override let a : Int32", let_a, ClassTypeOverrideTreeNode, true);
            SUBTEST_TREE_SINGLE("static let a : Int32", let_a, ClassTypeStaticTreeNode, true);

            SUBTEST_TREE_SINGLE("virtual let a : Int32 = a", assigned_a, ClassTypeVirtualTreeNode, true);
            SUBTEST_TREE_SINGLE("override let a : Int32 = a", assigned_a, ClassTypeOverrideTreeNode, true);
            SUBTEST_TREE_SINGLE("static let a : Int32 = a", assigned_a, ClassTypeStaticTreeNode, true);

            {
                TreeNode node = TreeNode(new ClassTypeOverrideTreeNode(let_a));
                TokenNode tn_override = TokenNode(new TokenNodeBase);
                tn_override->node = node;

                SUBTEST_TREE_SINGLE("virtual override let a : Int32", tn_override, ClassTypeVirtualTreeNode, true);
            }

            {
                TreeNode node = TreeNode(new ClassTypeStaticTreeNode(let_a));
                TokenNode tn_static = TokenNode(new TokenNodeBase);
                tn_static->node = node;

                SUBTEST_TREE_SINGLE("override static let a : Int32", tn_static, ClassTypeOverrideTreeNode, true);
            }

            {
                TreeNode node = TreeNode(new ClassTypeVirtualTreeNode(let_a));
                TokenNode tn_virtual = TokenNode(new TokenNodeBase);
                tn_virtual->node = node;

                SUBTEST_TREE_SINGLE("static virtual let a : Int32", tn_virtual, ClassTypeStaticTreeNode, true);
            }

            return true;
        }
    };
}
#endif