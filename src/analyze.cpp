#include <analyze.hpp>

#include <utils.hpp>

#include <string>
#include <vector>
#include <unordered_set>

namespace Martin::Syntax {

    class Scope {
    private:
        using scope = std::shared_ptr<std::unordered_set<std::string>>;
        std::vector<scope> scopes;
        scope current = std::make_shared<std::unordered_set<std::string>>();
        
    public:
        void Push() {
            scopes.push_back(current);
            current = std::make_shared<std::unordered_set<std::string>>();
        }

        void Pop() {
            current = scopes.back();
            scopes.pop_back();
        }

        void Insert(const std::string& name) {
            current->insert(name);
        }
        
        void Insert(const std::string_view& view) {
            Insert(std::string {view});
        }

        bool Has(const std::string& name) {
            return current->find(name) != current->end();
        }
        
        bool Has(const std::string_view& view) {
            return Has(std::string {view});
        }

        bool HasAll(const std::string& name) {
            if (Has(name)) return true;

            for (auto& scope : scopes) {
                if (scope->find(name) != scope->end()) return true;
            }

            return false;
        }

        bool HasAll(const std::string_view& view) {
            return HasAll(std::string {view});
        }

        std::unordered_set<std::string> GetCurrentNames() {
            return *current;
        }

        std::unordered_set<std::string> GetAllNames() {
            std::unordered_set<std::string> names_set;

            for (auto& name : *current) {
                names_set.insert(name);
            }

            for (auto& scope : scopes) {
                for (auto& name : *scope) {
                    names_set.insert(name);
                }
            }

            return names_set;
        }
    };

    void Analyze(std::shared_ptr<peg::Ast> ast) {
        if (ast == nullptr) return;
        
        Scope names;

        auto namespace_to_string = [](std::shared_ptr<peg::Ast> node) -> std::string {
            if (node == nullptr) internal_error;
            if (node->is_token) internal_error;
            if (node->name != "NAMESPACE") internal_error;

            std::string name;

            for (auto subnode : node->nodes) {
                name += ".";
                name += subnode->token;
            }

            return name.substr(1);
        };

        // Read global names first
        for (auto& node : ast->nodes) {
            if (node->is_token) continue;
            
            if (node->name == "ImportNames") {
                for (auto& name : node->nodes) {
                    if (name->name == "NAME") {
                        names.Insert(name->token);
                    } else if (name->name == "ImportNameAs") {
                        if (name->nodes[1]->name == "NAMESPACE") {
                            names.Insert(namespace_to_string(name->nodes[1]));
                        } else {
                            names.Insert(name->nodes[1]->token);
                        }
                    } else if (name->name == "NAMESPACE") {
                        names.Insert(namespace_to_string(name));
                    }
                }
            } else if (node->name == "Function" || node->name == "FunctionDefinition") {
                for (auto& subnode : node->nodes) {
                    if (subnode->name == "NAME") {
                        names.Insert(subnode->token);
                        break;
                    }
                }
            } else if (node->name == "VariableAutoTypeDefinition" || node->name == "VariableTypeDefinition") {
                for (auto& subnode : node->nodes) {
                    if (subnode->name == "NAME") {
                        names.Insert(subnode->token);
                        break;
                    } else if (subnode->name == "NameList") {
                        for (auto& name : subnode->nodes) {
                            names.Insert(name->token);
                        }
                        break;
                    }
                }
            }
        }

        auto names_set = names.GetAllNames();
        for (auto& name : names_set) {
            Print("$\n", name);
        }
    }

}