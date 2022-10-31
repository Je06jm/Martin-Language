#ifndef MARTIN_AST_NODE
#define MARTIN_AST_NODE

// Going to switch from llvm-10 to llvm-15
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/ADT/APInt.h>
#include <memory>
#include <cstdint>
#include <string>
#include <cmath>

namespace Martin {
    class ASTNode {
    public:
        ~ASTNode() = default;
        virtual llvm::Value* CodeGen(llvm::LLVMContext& ctx, llvm::IRBuilder<>& builder) = 0;

        static void EvalAST(std::unique_ptr<ASTNode> root) {
            llvm::LLVMContext ctx;
            llvm::IRBuilder<> builder(ctx);
            std::unique_ptr<Module> mod;


        }
    };

    class ASTNumber : public ASTNode {
    private:
        enum class Type {
            UInteger,
            Integer,
            Double
        } type;

        union {
            std::uint64_t unum;
            std::int64_t snum;
            double dnum;
        } data;
    
    public:
        ASTNumber(const std::string_view view) {
            if (view.find(".")) {
                type = Type::Double;
                
                if (view.find("e") != std::string_view::npos) {
                    auto index = view.find("e");
                    data.dnum = std::stod(std::string(view.substr(0, view-1)));

                    double e = std::pow(10, std::stoi(std::string(view.substr(view+2))));

                    if (view[index+1] == '-') {
                        data.dnum *= e;
                    } else {
                        data.dum /= e;
                    }
                } else {
                    data.dnum = std::stod(std::string(view));
                }
            } else if (view.find("u")) {
                type = Type::UInteger;

                auto index = view.find("u");

                data.unum = std::stoull(std::string(view.substr(0, index)));
            } else {
                type = Type::Integer;
                data.snum = std::stoll(std::string(view));
            }
        }

        llvm::Value* CodeGen(llvm::LLVMContext& ctx, llvm::IRBuilder<>& builder) override {
            if (type == Type::Double) {
                return llvm::ConstantFP(llvm::Type(ctx, llvm::Type::TypeID::DoubleTyID), llvm::APFloat(64, data.dnum));
            } else if (type == Type::UInteger) {
                return llvm::ConstantInt(llvm::IntegerType(ctx, 64), llvm::APInt(64, data.unum, false));
            } else {
                return llvm::ConstantInt(llvm::IntegerType(ctx, 64), llvm::APInt(64, data.unum, true));
            }
        }
    };

    class ASTInteger : public ASTNode {
    private:
        enum class Type {
            UInteger,
            Integer
        } type;

        union {
            std::uint64_t unum;
            std::int64_t snum;
        } data;
    
    public:
        ASTInteger(const std::string_view view) {
            if (view.find("u") != std::string_view::npos) {
                type = Type::UInteger;

                auto index = view.find("u");

                data.unum = std::stoull(std::string(view.substr(0, index)));
            } else if (view.find("0x") != std::string_view::npos) {
                type = Type::UInteger;

                data.unum = 0;

                for (size_t i = 2; i < view.size(); i++) {
                    char c = view[i];

                    data.unum *= 16;

                    if (c >= 'a' && c <= 'f') {
                        data.unum += c - 'a' + 10;
                    } else if (c >= 'A' && c <= 'F') {
                        data.unum += c - 'A' + 10;
                    } else {
                        data.unum += c - '0';
                    }
                }
            } else if (view.find("0o") != std::string_view::npos) {
                type = Type::UInteger;

                data.unum = 0;

                for (size_t i = 2; i < view.size(); i++) {
                    data.unum *= 8;
                    data += view[i] - '0';
                }
            } else {
                type = Type::Integer;

                data.snum = std::stoll(std::string(view));
            }
        }

        llvm::Value* CodeGen(llvm::LLVMContext& ctx, llvm::IRBuilder<>& builder) override {
            if (type == Type::UInteger) {
                return llvm::ConstantInt(llvm::IntegerType(ctx, 64), llvm::APInt(64, data.unum, false));
            } else {
                return llvm::ConstantInt(llvm::IntegerType(ctx, 64), llvm::APInt(64, data.unum, true));
            }
        }
    };
};

#endif
