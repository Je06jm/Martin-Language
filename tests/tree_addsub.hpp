#ifndef MARTIN_TEST_TREE_ADDSUB
#define MARTIN_TEST_TREE_ADDSUB

#include "testing.hpp"

#include <generators/addsub.hpp>

#include <parse.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"

namespace Martin {
    class Test_tree_addsub : public Test {
    public:
        std::string GetName() const override {
            return "Tree(AddSub)";
        }

        bool RunTest() override {
            {
                auto tree = TokenizerSingleton.TokenizeString("1 + a - 2.3 true while");

                if (!ValidateTokenList(tree, error, 7)) return false;

                TokenNode one = GetTokenNodeFromTokenList(tree, 0);
                TokenNode plus = GetTokenNodeFromTokenList(tree, 1);
                TokenNode a = GetTokenNodeFromTokenList(tree, 2);
                TokenNode minus = GetTokenNodeFromTokenList(tree, 3);
                TokenNode two_three = GetTokenNodeFromTokenList(tree, 4);
                TokenNode boolean = GetTokenNodeFromTokenList(tree, 5);
                TokenNode keyword = GetTokenNodeFromTokenList(tree, 6);

                {
                    OPAddTreeNode node(one, a);

                    if (!node.Valid()) {
                        error = "OPAddTreeNode is not valid when given (Token(1), Token(a))";
                        return false;
                    }
                }

                {
                    OPAddTreeNode node(a, one);

                    if (!node.Valid()) {
                        error = "OPAddTreeNode is not valid when given (Token(a), Token(1))";
                        return false;
                    }
                }

                {
                    OPAddTreeNode node(one, two_three);

                    if (!node.Valid()) {
                        error = "OPAddTreeNode is not valid when given (Token(1), Token(2.3))";
                        return false;
                    }
                }

                {
                    OPAddTreeNode node(two_three, one);
                    
                    if (!node.Valid()) {
                        error = "OPAddTreeNode is not valid when given (Token(2.3), Token(1))";
                        return false;
                    }
                }

                {
                    OPAddTreeNode node(a, two_three);

                    if (!node.Valid()) {
                        error = "OPAddTreeNode is not valid when given (Token(a), Token(2.3))";
                        return false;
                    }
                }

                {
                    OPAddTreeNode node(two_three, a);

                    if (!node.Valid()) {
                        error = "OPAddTreeNode is not valid when given (Token(2.3), Token(a))";
                        return false;
                    }
                }

                {
                    OPAddTreeNode node(one, boolean);

                    if (node.Valid()) {
                        error = "OPAddTreeNode is valid when given (Token(1), Token(true))";
                        return false;
                    }
                }

                {
                    OPAddTreeNode node(boolean, one);

                    if (node.Valid()) {
                        error = "OPAddTreeNode is valid when given (Token(true), Token(1))";
                        return false;
                    }
                }

                {
                    OPAddTreeNode node(boolean, boolean);

                    if (node.Valid()) {
                        error = "OPAddTreeNode is valid when given (Token(true), Token(true))";
                        return false;
                    }
                }

                {
                    OPAddTreeNode node(one, keyword);

                    if (node.Valid()) {
                        error = "OPAddTreeNode is valid when given (Token(1), Token(while))";
                        return false;
                    }
                }

                {
                    OPAddTreeNode node(keyword, one);

                    if (node.Valid()) {
                        error = "OPAddTreeNode is valid when given (Token(while), Token(1))";
                        return false;
                    }
                }

                {
                    OPAddTreeNode node(boolean, keyword);

                    if (node.Valid()) {
                        error = "OPAddTreeNode is valid when given (Token(true), Token(while))";
                        return false;
                    }
                }

                {
                    OPAddTreeNode node(keyword, boolean);
                    
                    if (node.Valid()) {
                        error = "OPAddTreeNode is valid when given (Token(true), Token(while))";
                        return false;
                    }
                }

                {
                    OPAddTreeNode node(keyword, keyword);

                    if (node.Valid()) {
                        error = "OPAddTreeNode is valid when given (Token(while), Token(while))";
                        return false;
                    }
                }

                                {
                    OPSubTreeNode node(one, a);

                    if (!node.Valid()) {
                        error = "OPSubTreeNode is not valid when given (Token(1), Token(a))";
                        return false;
                    }
                }

                {
                    OPSubTreeNode node(a, one);

                    if (!node.Valid()) {
                        error = "OPSubTreeNode is not valid when given (Token(a), Token(1))";
                        return false;
                    }
                }

                {
                    OPSubTreeNode node(one, two_three);

                    if (!node.Valid()) {
                        error = "OPSubTreeNode is not valid when given (Token(1), Token(2.3))";
                        return false;
                    }
                }

                {
                    OPSubTreeNode node(two_three, one);
                    
                    if (!node.Valid()) {
                        error = "OPSubTreeNode is not valid when given (Token(2.3), Token(1))";
                        return false;
                    }
                }

                {
                    OPSubTreeNode node(a, two_three);

                    if (!node.Valid()) {
                        error = "OPSubTreeNode is not valid when given (Token(a), Token(2.3))";
                        return false;
                    }
                }

                {
                    OPSubTreeNode node(two_three, a);

                    if (!node.Valid()) {
                        error = "OPSubTreeNode is not valid when given (Token(2.3), Token(a))";
                        return false;
                    }
                }

                {
                    OPSubTreeNode node(one, boolean);

                    if (node.Valid()) {
                        error = "OPSubTreeNode is valid when given (Token(1), Token(true))";
                        return false;
                    }
                }

                {
                    OPSubTreeNode node(boolean, one);

                    if (node.Valid()) {
                        error = "OPSubTreeNode is valid when given (Token(true), Token(1))";
                        return false;
                    }
                }

                {
                    OPSubTreeNode node(boolean, boolean);

                    if (node.Valid()) {
                        error = "OPSubTreeNode is valid when given (Token(true), Token(true))";
                        return false;
                    }
                }

                {
                    OPSubTreeNode node(one, keyword);

                    if (node.Valid()) {
                        error = "OPSubTreeNode is valid when given (Token(1), Token(while))";
                        return false;
                    }
                }

                {
                    OPSubTreeNode node(keyword, one);

                    if (node.Valid()) {
                        error = "OPSubTreeNode is valid when given (Token(while), Token(1))";
                        return false;
                    }
                }

                {
                    OPSubTreeNode node(boolean, keyword);

                    if (node.Valid()) {
                        error = "OPSubTreeNode is valid when given (Token(true), Token(while))";
                        return false;
                    }
                }

                {
                    OPSubTreeNode node(keyword, boolean);
                    
                    if (node.Valid()) {
                        error = "OPSubTreeNode is valid when given (Token(true), Token(while))";
                        return false;
                    }
                }

                {
                    OPSubTreeNode node(keyword, keyword);

                    if (node.Valid()) {
                        error = "OPSubTreeNode is valid when given (Token(while), Token(while))";
                        return false;
                    }
                }

                {
                    TokenNode node_add = TokenNode(new TokenNodeBase);
                    node_add->node = TreeNode(new OPAddTreeNode(one, two_three));
                    OPSubTreeNode node_sub(a, node_add);

                    if (!node_sub.Valid()) {
                        error = "OPSubTreeNode is valid when given (Token(a), AddNode)";
                        return false;
                    }
                }

                return true;
            }
        }
    };
}
#endif