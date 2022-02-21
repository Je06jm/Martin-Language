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
            KW_ConstExpr,
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
            KW_ForEach,
            KW_While,
            KW_Continue,
            KW_Break,
            KW_Match,
            KW_Return,
            KW_Lambda,
            KW_And,
            KW_Or,
            KW_Not,
        };

        virtual ~TokenType() {};
        
        virtual Type GetType() const = 0;

        virtual void Process(std::string& in) = 0;
        virtual std::shared_ptr<void> GetData() {
            return nullptr;
        };

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
    
    void InitTokenizer();
    std::unique_ptr<std::vector<Token>> Tokenize(std::string input);

}

#endif