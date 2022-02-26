#ifndef MARTIN_TOKENS
#define MARTIN_TOKENS

#include <string>
#include <vector>
#include <memory>

namespace Martin {

    class TokenType {
    public:
        enum class Type {
            Ignore,
            FloatingSingle,
            FloatingDouble,
            UInteger,
            Integer,
            Boolean,
            String8,
            String16,
            String32,
            String16l,
            String16b,
            String32l,
            String32b,
            Identifier,
            KW_From,
            KW_Import,
            KW_As,
            KW_Struct,
            KW_Union,
            KW_Enum,
            KW_Typedef,
            KW_Let,
            KW_Set,
            KW_Const,
            KW_Constexpr,
            KW_Array,
            KW_Reference,
            KW_Shared,
            KW_Pointer,
            KW_Extern,
            KW_Unsafe,
            KW_Func,
            KW_Class,
            KW_Public,
            KW_Protected,
            KW_Private,
            KW_Virtual,
            KW_Override,
            KW_Static,
            KW_Super,
            KW_If,
            KW_Elif,
            KW_Else,
            KW_For,
            KW_Foreach,
            KW_While,
            KW_Continue,
            KW_Break,
            KW_Match,
            KW_Return,
            KW_Lambda,
            KW_And,
            KW_Or,
            KW_Not,
            SYM_Comma,
            SYM_Period,
            SYM_OpenCurly,
            SYM_CloseCurly,
            SYM_OpenBracket,
            SYM_CloseBracket,
            SYM_OpenParentheses,
            SYM_CloseParentheses,
            SYM_SemiColon,
            SYM_Colon,
            SYM_Arrow,
            SYM_AssignAdd,
            SYM_AssignSub,
            SYM_AssignMul,
            SYM_AssignDiv,
            SYM_AssignMod,
            SYM_AssignPow,
            SYM_AssignBitAnd,
            SYM_AssignBitOr,
            SYM_AssignBitXOr,
            SYM_AssignBitShiftLeft,
            SYM_AssignBitShiftRight,
            SYM_Add,
            SYM_Sub,
            SYM_Mul,
            SYM_Div,
            SYM_Mod,
            SYM_Pow,
            SYM_BitAnd,
            SYM_BitOr,
            SYM_BitXOr,
            SYM_BitNot,
            SYM_BitShiftLeft,
            SYM_BitShiftRight,
            SYM_TypeAssign,
            SYM_Assign,
            SYM_Equals,
            SYM_NotEquals,
            SYM_LessThanEquals,
            SYM_GreaterThanEquals,
            SYM_LessThan,
            SYM_GreaterThan
        };

        virtual ~TokenType() {};
        
        virtual Type GetType() const = 0;

        virtual void Process(std::string& in) = 0;
        virtual std::shared_ptr<void> GetData() {
            return nullptr;
        };

#ifdef MARTIN_DEBUG
        virtual std::string GetName() const {
            return "Unknown";
        }
#endif

        void SetLineNumber(unsigned int number) { if (lineno == 0) lineno = number; }
        unsigned int GetLineNumber() const { return lineno; }
    private:
        unsigned int lineno = 0;
    };

    typedef std::shared_ptr<TokenType> Token;

    class PatternType {
    public:
        virtual ~PatternType() {};
        enum class Type {
            Integer,
            UInteger
        };

        virtual bool IsMatch(const std::string& in) const = 0;
        virtual Token CreateToken() const = 0;
    };

    typedef std::shared_ptr<PatternType> Pattern;
    typedef std::shared_ptr<std::vector<Token>> TokenList;
    
    class Tokenizer {
    public:
        Tokenizer();

        TokenList TokenizeString(std::string input);

    private:
        std::vector<Pattern> patterns;
    };

    void InitTokenizer();
    std::unique_ptr<std::vector<Token>> Tokenize(std::string input);

}

#endif