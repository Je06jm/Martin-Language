#include <martin.hpp>
#include <logging.hpp>

//#include "grammer.hpp"

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

        auto file = std::ifstream("grammar.txt", std::ios_base::binary | std::ios_base::in);
        if (!file.is_open()) {
            Fatal("Could not open 'grammar.txt'");
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        std::string MartinGrammar = buffer.str();

        parser->set_logger(ParserErrorLog);

        if (!parser->load_grammar(MartinGrammar)) {
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

    void SanitizeCode(std::string& code) {
        // Scrub comments out since I can't figure out how to do that in the grammar

        // Single line
        size_t index = code.find("//");
        size_t index2;
        while (index != std::string::npos) {
            index2 = code.find("\n", index);
            if (index2 == std::string::npos) {
                code = code.substr(0, index);
            } else {
                code = code.substr(0, index) + code.substr(index2);
            }

            index = code.find("//");
        }

        // Double line
        index = code.find("/*");
        while (index != std::string::npos) {
            index2 = code.find("*/", index);
            code = code.substr(0, index) + code.substr(index2 + 2);

            index = code.find("/*");
        }
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