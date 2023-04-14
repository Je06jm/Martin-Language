#include <file.hpp>

#include <martin.hpp>

#include <functional>

namespace Martin {

    std::shared_ptr<File> File::ReadFile(const std::string& path) {
        auto file = std::make_shared<File>();
        file->code = Martin::ReadFile(path);
        SanitizeCode(file->code);

        auto ast = CreateASTFromCode(file->code);

        std::function<void(std::shared_ptr<peg::Ast>, const std::string&, std::vector<std::shared_ptr<peg::Ast>>&)> GetSub;

        GetSub = [&GetSub](std::shared_ptr<peg::Ast> ast, const std::string& node_name, std::vector<std::shared_ptr<peg::Ast>>& nodes) {
            if (ast == nullptr) {
                return;
            }

            if (ast->name == node_name) {
                nodes.push_back(ast);
            }

            for (auto& node : ast->nodes) {
                GetSub(node, node_name, nodes);
            }
        };

        std::function<void(std::shared_ptr<peg::Ast>, bool)> Skim;

        Skim = [&file, &Skim, &GetSub](std::shared_ptr<peg::Ast> ast, bool is_private) {
            if (ast == nullptr) {
                return;
            }

            if (ast->name == "PrivateGlobalScope") {
                for (auto& node : ast->nodes) {
                    Skim(node, true);
                }
            } else if (ast->name == "TypedefDefinition") {
                file->typedefs[std::string(ast->nodes[0]->token)] = std::make_pair(ast->nodes[0], is_private);
            } else if (ast->name == "UnionTypeDefinition") {
                file->unions[std::string(ast->nodes[0]->token)] = std::make_pair(ast->nodes[0], is_private);
            } else if (ast->name == "StructTypeDefinition") {
                file->structs[std::string(ast->nodes[0]->token)] = std::make_pair(ast->nodes[0], is_private);
            } else if (ast->name == "EnumTypeDefinition") {
                file->enums[std::string(ast->nodes[0]->token)] = std::make_pair(ast->nodes[0], is_private);
            } else if (ast->name == "InterfaceDefinition") {
                file->interfaces[std::string(ast->nodes[0]->token)] = std::make_pair(ast->nodes[0], is_private);
            } else if (ast->name == "FunctionImplementation") {
                file->functions[std::string(ast->nodes[0]->nodes[0]->token)] = std::make_pair(ast, is_private);
            } else if (ast->name == "FunctionPureDefinition") {
                file->functions[std::string(ast->nodes[0]->token)] = std::make_pair(ast, is_private);
            } else if (ast->name == "ClassDefinition") {
                //file->classes[std::string(ast->nodes[0]->token)];
            }
        };

    }

}