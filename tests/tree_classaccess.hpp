#ifndef MARTIN_TEST_TREE_CLASSACCESS
#define MARTIN_TEST_TREE_CLASSACCESS

#include "testing.hpp"

#include <generators/classaccess.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"

#define SUBTEST_SINGLE(str, left, type, valid)\
{\
    type node(left);\
    if (node.Valid()) {\
        if (!valid) {\
            error = ParseNodeError("valid", str);\
            return false;\
        }\
    } else if (valid) {\
        error = ParseNodeError("not valid", str);\
        return false;\
    }\
}

namespace Martin {
    class Test_tree_classaccess : public Test {
    public:
        std::string GetName() const override {
            return "Tree(ClassAccess)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("public private protected friend wow");

            if (!ValidateTokenList(tree, error, 5)) return false;

            TokenNode tn_public = GetTokenNodeFromTokenList(tree, 0);
            TokenNode tn_private = GetTokenNodeFromTokenList(tree, 1);
            TokenNode tn_protected = GetTokenNodeFromTokenList(tree, 2);
            TokenNode tn_friend = GetTokenNodeFromTokenList(tree, 3);
            TokenNode wow = GetTokenNodeFromTokenList(tree, 4);

            SUBTEST_SINGLE("public wow", wow, ClassAccessPublicTreeNode, true);
            SUBTEST_SINGLE("private wow", wow, ClassAccessPrivateTreeNode, true);
            SUBTEST_SINGLE("protected wow", wow, ClassAccessProtectedTreeNode, true);
            SUBTEST_SINGLE("friend wow", wow, ClassAccessProtectedTreeNode, true);

            SUBTEST_SINGLE("public friend", tn_friend, ClassAccessPublicTreeNode, false);
            SUBTEST_SINGLE("private public", tn_public, ClassAccessPrivateTreeNode, false);
            SUBTEST_SINGLE("protected private", tn_private, ClassAccessProtectedTreeNode, false);
            SUBTEST_SINGLE("friend protected", tn_protected, ClassAccessFriendTreeNode, false);

            return true;
        }
    };
}

#undef SUBTEST_SINGLE

#endif