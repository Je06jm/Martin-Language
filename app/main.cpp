#define DEBUG_PRINT

/*
#include <unicode.hpp>

#include <values.hpp>
#include <tuple.hpp>

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>

#include <tokens.hpp>
#include <parse.hpp>
#include <logging.hpp>
#include <project.hpp>
*/

#include <string>
#include <iostream>
#include <logging.hpp>
#include <martin.hpp>
#include <analyze.hpp>

//Martin::UnicodeType input_unicode_type = Martin::UnicodeType_8Bits;

void PrintNodes(std::shared_ptr<peg::Ast> ast, int level = 0) {
    if (ast == nullptr) {
        return;
    }

    for (int i = 0; i < level; i++) {
        Martin::Print("\t");
    }

    std::string type = ast->is_token ? "Token" : "Node";
    std::string name = ast->name;
    std::string token = std::string {ast->token};
    Martin::Print("$ ($) $\n", type, name, token);

    for (auto node : ast->nodes) {
        PrintNodes(node, level + 1);
    }
}

int main(int argc, char** argv) {
    argc--; argv++;

    if (argc < 1) {
        Martin::Warning("Usage: ttparse.exe <file>\n");
        exit(EXIT_SUCCESS);
    }

    auto code = Martin::ReadFile(argv[0]);
    Martin::SanitizeCode(code);

    auto ast = Martin::CreateASTFromCode(code);

    PrintNodes(ast);

    Martin::Syntax::Analyze(ast);

    return 0;
}