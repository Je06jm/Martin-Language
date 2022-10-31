#include <logging.hpp>
#include <codegen.hpp>

/*
void PrintNodes(std::shared_ptr<peg::Ast> ast, int level = 0) {
    for (int i = 0; i < level; i++) {
        Martin::Print("\t");
    }

    if (ast == nullptr) {
        Martin::Print("(nullptr)\n");
        return;
    }

    std::string type = ast->is_token ? "Token" : "Node";
    std::string name = ast->name;
    std::string token = std::string {ast->token};
    Martin::Print("$ ($) $\n", type, name, token);

    for (auto node : ast->nodes) {
        PrintNodes(node, level + 1);
    }
}
*/

int main(int argc, char** argv) {
    argc--; argv++;

    if (argc < 1) {
        Martin::Warning("Usage: martin.exe <code> <obj?>\n");
        exit(EXIT_SUCCESS);
    }

    auto codegen = Martin::CodeGen::FromFile(argv[0]);
    
    if (argc < 2) {
        codegen.Run();
    } else {
        codegen.Compile(argv[1]);
    }

    return 0;
}