#include <parse.hpp>

namespace Martin {

    class MiscFromImportTreeNode : public TreeNodeBase {
    public:
        MiscFromImportTreeNode(TokenNode id, TokenNode imports) : id(id), imports(imports) {}

        Type GetType() const override {
            return Type::Misc_FromImport;
        }

        std::string GetName() const override {
            return "fromimport";
        }

        void Serialize(std::string& serial) const override {
            if (imports)
                serial = Format("$($, $)", GetName(), *id, *imports);
            else
                serial = Format("$($)", GetName(), *id);
        }

        const TokenNode id;
        const TokenNode imports;
    };

    class MiscFromImportTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (sym->GetType() == TokenType::Type::KW_Import)) {
                TokenNode id = GetIndexOrNull(tree, index+1);

                if (id) {
                    TreeNode op = TreeNode(new MiscFromImportTreeNode(id, nullptr));

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
                    TreeNode op = TreeNode(new MiscFromImportTreeNode(id, imports));

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