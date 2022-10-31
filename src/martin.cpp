#include <martin.hpp>
#include <logging.hpp>

#ifndef MARTIN_DEBUG
#include "grammar.hpp"
#endif

#include <iostream>
#include <fstream>

namespace Martin {

    std::string current_file;

    void ParserErrorLog(size_t line, size_t col, const std::string& message, const std::string& rule) {
#ifdef MARTIN_DEBUG
        Fatal("Syntax error, $($). Rule $: $\n", current_file, line, rule, message);
#else
        Fatal("Syntax error, $($): $\n", current_file, line, message);
#endif
    }

    std::unique_ptr<peg::parser> CreateParser() {
        auto parser = std::make_unique<peg::parser>();

#ifdef MARTIN_DEBUG
        auto file = std::ifstream("src/grammar.txt", std::ios_base::binary | std::ios_base::in);
        if (!file.is_open()) {
            Fatal("Could not open 'src/grammar.txt'");
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        std::string martin_grammar = buffer.str();
#else
        std::string martin_grammar = std::string(grammar);
#endif

        parser->set_logger(ParserErrorLog);

        if (!parser->load_grammar(martin_grammar)) {
            Fatal("Could not create parser");
        }

        parser->enable_ast();

        return std::move(parser);
    }

    std::string ReadFile(const std::string& path) {
        std::ifstream file(path, std::ios_base::binary | std::ios_base::in);
        if (!file.is_open()) {
            Fatal("Could not open file '$'", path);
        }

        std::stringstream buf;
        buf << file.rdbuf();
        file.close();

        std::string code = buf.str();

        return code;
    }

    std::shared_ptr<peg::Ast> CreateASTFromCode(const std::string& code, bool optimize) {
        current_file = "Code";
        
        auto parser = CreateParser();

        std::shared_ptr<peg::Ast> ast;

        parser->parse(code, ast);

        if (optimize) {
            ast = parser->optimize_ast(ast);
        }

        return ast;
    }

}