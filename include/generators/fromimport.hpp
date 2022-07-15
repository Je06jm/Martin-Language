#ifndef MARTIN_GENERATORS_FROMIMPORT
#define MARTIN_GENERATORS_FROMIMPORT

#include <parse.hpp>
#include <vector>
#include "comma.hpp"

namespace Martin {

    class MiscFromImportTreeNode : public TreeNodeBase {
    public:
        MiscFromImportTreeNode(const std::vector<TokenNode>& ids, const std::vector<TokenNode>& imports) : ids(ids), imports(imports) {}

        Type GetType() const override {
            return Type::Misc_FromImport;
        }

        std::string GetName() const override {
            return "fromimport";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$(", GetName());
            if (ids.size() == 0) {
                serial = Format("($)", serial);
            } else if (ids.size() == 1) {
                serial = Format("$($)", serial, *(ids[0]));
            } else {
                serial = Format("$(($", serial, *(ids[0]));
                for (size_t i = 1; i < ids.size(); i++) {
                    serial = Format("$, $", serial, *(ids[i]));
                }
                serial = Format("$)", serial);
            }

            if (imports.size() == 0) {
                serial = Format("$)", serial);
            } else if (imports.size() == 1) {
                serial = Format("$, ($))", serial, *(imports[0]));
            } else {
                serial = Format("$, ($", serial, *(imports[0]));
                for (size_t i = 1; i < imports.size(); i++) {
                    serial = Format("$, $", serial, *(imports[i]));
                }
                serial = Format("$))", serial);
            }
        }

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (ids.size() == 0) return false;
            if ((imports.size() != 0) && (ids.size() != 1)) return false;

            for (auto it : ids) {
                if (it->is_token) {
                    if (it->token->GetType() != TokenType::Type::Identifier) return false;
                } else {
                    switch (it->node->GetType()) {
                        case Type::OP_Dot:
                        case Type::Struct_As:
                            break;
                        
                        default:
                            return false;
                    }
                }
            }

            for (auto it : imports) {
                if (it->is_token) {
                    if (it->token->GetType() != TokenType::Type::Identifier) return false;
                } else {
                    switch (it->node->GetType()) {
                        case Type::OP_Dot:
                        case Type::Struct_As:
                            break;
                        
                        default:
                            return false;
                    }
                }
            }

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;

            for (auto node : ids) {
                if (!node->is_token) {
                    if (node->node->GetType() == type) {
                        list.push_back(node->node);
                    }
                    auto list2 = node->node->GetAllNodesOfType(type);
                    list.insert(list.end(), list2.begin(), list2.end());
                }
            }

            for (auto node : imports) {
                if (!node->is_token) {
                    if (node->node->GetType() == type) {
                        list.push_back(node->node);
                    }
                    auto list2 = node->node->GetAllNodesOfType(type);
                    list.insert(list.end(), list2.begin(), list2.end());
                }
            }

            return list;
        }

        const std::vector<TokenNode> ids;
        const std::vector<TokenNode> imports;
    };

    class MiscFromImportTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (sym->GetType() == TokenType::Type::KW_Import)) {
                TokenNode id = GetIndexOrNull(tree, index+1);

                if (id) {
                    std::vector<TokenNode> ids;
                    std::vector<TokenNode> vimports;

                    if (id->is_token) {
                        ids.push_back(id);
                    } else {
                        if (!id->node->Valid()) return 0;

                        if (id->node->GetType() == TreeNodeBase::Type::Struct_As) {
                            ids.push_back(id);
                        }
                        else if (id->node->GetType() == TreeNodeBase::Type::Struct_Comma) {
                            auto comma = std::static_pointer_cast<StructCommaTreeNode>(id->node);
                            for (auto it : comma->nodes) {
                                ids.push_back(it);
                            }
                        } else return 0;
                    }

                    TreeNode op = TreeNode(new MiscFromImportTreeNode(ids, vimports));

                    op->SetLineNumber(sym->GetLineNumber());

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index, 2);
                    return 2;
                    
                }
            } else if (sym && (sym->GetType() == TokenType::Type::KW_From)) {
                TokenNode id = GetIndexOrNull(tree, index+1);
                Token sym_import = GetIndexOrNullToken(tree, index+2);
                TokenNode imports = GetIndexOrNull(tree, index+3);

                if (id && sym_import && imports && (sym_import->GetType() == TokenType::Type::KW_Import)) {
                    std::vector<TokenNode> ids;
                    std::vector<TokenNode> vimports;

                    if (id->is_token) {
                        ids.push_back(id);
                    } else {
                        if (!id->node->Valid()) return 0;

                        if (id->node->GetType() != TreeNodeBase::Type::Struct_Comma) return 0;

                        auto comma = std::static_pointer_cast<StructCommaTreeNode>(id->node);
                        for (auto it : comma->nodes) {
                            ids.push_back(it);
                        }
                    }

                    if (imports->is_token) {
                        vimports.push_back(imports);
                    } else {
                        if (!imports->node->Valid()) return 0;

                        if (imports->node->GetType() == TreeNodeBase::Type::Struct_As) {
                            vimports.push_back(imports);
                        } else if (imports->node->GetType() == TreeNodeBase::Type::Struct_Comma) {
                            auto comma = std::static_pointer_cast<StructCommaTreeNode>(imports->node);
                            for (auto it : comma->nodes) {
                                vimports.push_back(it);
                            }
                        } else return 0;
                    }

                    TreeNode op = TreeNode(new MiscFromImportTreeNode(ids, vimports));

                    op->SetLineNumber(sym->GetLineNumber());

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index, 4);
                    return 4;
                }
            }
            return 0;
        }
    };

}

#endif