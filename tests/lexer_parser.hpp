#include "testing.hpp"

#include "sample.martin"

#include <parse.hpp>

namespace Martin {
    class Test_lexer_parser : public Test {
    public:
        std::string GetName() const override {
            return "Lexer(Parser)";
        }

        bool RunTest() override {
            auto tree = ParserSingleton.ParseString(martin_sample, error);

            if (!tree) {
                error = Format("Parser encountered an error: $", error);
                return false;
            }

            for (auto it : *tree) {
                if (it->is_token) {
                    error = "Parser returned a tree with tokens without ownership";
                    return false;
                }
            }

            for (auto it : *tree) {
                if (!it->node->Valid()) {
                    error = "Parser returned a tree with an invalid node";
                    return false;
                }
            }

            tree = ParserSingleton.ParseString("", error);

            if (!tree) {
                error = Format("Parser encountered an error when given an empty string: $", error);
                return false;
            }

            if (tree->size() != 0) {
                error = "Parser returned a non-empty array when givin an empty string";
                return false;
            }

            return true;
        }
    };
}