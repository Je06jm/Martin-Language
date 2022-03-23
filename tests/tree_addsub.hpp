#ifndef MARTIN_TEST_TREE_ADDSUB
#define MARTIN_TEST_TREE_ADDSUB

#include "testing.hpp"

#include <generators/addsub.hpp>

#include <parse.hpp>

namespace Martin {
    class Test_tree_addsub : public Test {
    public:
        std::string GetName() const override {
            return "Tree(AddSub)";
        }

        bool RunTest() override {
            {
                auto tree = TokenizerSingleton.TokenizeString("1 + a");

                

                TokenNode plus = TokenNode(new TokenNodeBase);
                plus->node = (*tree)[0];

                return true;
            }
        }
    };
}
#endif