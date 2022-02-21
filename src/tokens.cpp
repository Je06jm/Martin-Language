#include <tokens.hpp>

#include <iostream>
#include <stdint.h>
#include <cstring>

#include "strhelper.hpp"

namespace Martin {
    unsigned int line_number = 1;

    enum class NumberType {
        Decimal,
        Hexidecimal,
        Octal,
        Binary
    };

    class NewLineToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::Ignore;
        }

        void Process(std::string& in) override {
            in.erase(0, 1);

            line_number++;
        }
    };

    class WhiteSpaceToken : public TokenType {
        Type GetType() const override {
            return Type::Ignore;
        }

        void Process(std::string& in) override {
            in.erase(0, 1);
        }
    };

    class FloatingSingleToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::FloatingSingle;
        }

        void Process(std::string& in) override {
            size_t index = in.find("f");
            std::string float_str = in.substr(0, index);
            in.erase(0, index+1);
            value = std::stof(float_str);
        }

        std::shared_ptr<void> GetData() override {
            return std::make_shared<float>(value);
        }
    private:
        float value = 0.0f;
    };

    class FloatingDoubleToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::FloatingDouble;
        }

        void Process(std::string& in) override {
            size_t index = in.find_first_not_of("1234567890.");
            std::string double_str = in.substr(0, index);
            in.erase(0, index);
            value = std::stod(double_str);
        }

        std::shared_ptr<void> GetData() override {
            return std::make_shared<double>(value);
        }
    private:
        double value = 0.0f;
    };

    class UIntegerToken : public TokenType {
    public:
        Type GetType() const override { return Type::UInteger; }

        void Process(std::string& in) override {
            NumberType type = NumberType::Decimal;
            char c;

            in.erase(0, 1);
            
            if (in.length() >= 2) {
                switch (in[1]) {
                    case 'x':
                    case 'X':
                        type = NumberType::Hexidecimal;
                        in.erase(0, 2);
                        break;
                    case 'o':
                    case 'O':
                        type = NumberType::Octal;
                        in.erase(0, 2);
                        break;
                    case 'b':
                    case 'B':
                        type = NumberType::Binary;
                        in.erase(0, 2);
                        break;
                }
            }

            while (true) {
                if (in.length() >= 1) {
                    c = in[0];

                    switch (type) {
                        case NumberType::Hexidecimal:
                            if (c != '_') {
                                value *= 16;
                                if ((c >= '0') && (c < '9'))
                                    value += c - '0';
                            
                                else if ((c >= 'a') && (c <= 'f'))
                                    value += c - 'a' + 10;
                            
                                else if ((c >= 'A') && (c <= 'F'))
                                    value += c - 'A' + 10;
                                
                                else
                                    return;
                            }
                            
                            break;
                        
                        case NumberType::Octal:
                            if (c != '_') {
                                value *= 8;
                                if ((c >= '0') && (c <= '7'))
                                    value += c - '0';
                                
                                else
                                    return;
                            }
                            
                            break;
                        
                        case NumberType::Decimal:
                            if (c != '_') {
                                value *= 10;
                                if ((c >= '0') && (c <= '9'))
                                    value += c - '0';
                                
                                else
                                    return;
                            }

                            break;
                            
                        case NumberType::Binary:
                            if (c != '_') {
                                value *= 2;
                                if ((c == '0') || (c == '1'))
                                    value += c - '0';
                                
                                else
                                    return;
                            }
                            
                            break;
                    }

                    in.erase(0, 1);
                    
                } else {
                    break;
                }
            }

        }
    
        std::shared_ptr<void> GetData() override { return std::make_shared<uintmax_t>(value); }
    private:
        uintmax_t value = 0;
    };

    class IntegerToken : public TokenType {
    public:
        Type GetType() const override { return Type::Integer; }

        void Process(std::string& in) override {
            char c;

            bool negative = false;

            if (in[0] == '-') {
                negative = true;
                in.erase(0, 1);
            }

            while (true) {
                if (in.length() >= 1) {
                    c = in[0];

                    if (c != '_') {
                        if ((c >= '0') && (c <= '9')) {
                            value *= 10;
                            value += c - '0';
                        } else
                            break;
                    }

                    in.erase(0, 1);
                    
                } else {
                    break;
                }
            }

            if (negative)
                value = -value;
        }
    
        std::shared_ptr<void> GetData() override { return std::make_shared<intmax_t>(value); }
    private:
        intmax_t value = 0;
    };

    class BooleanToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::Boolean;
        }

        void Process(std::string& in) override {
            if (in[0] == 't') {
                value = true;
                in.erase(0, std::strlen("true"));
            } else {
                value = false;
                in.erase(0, std::strlen("false"));
            }
        }

    private:
        bool value = false;
    };

    class String8Token : public TokenType {
    public:
        Type GetType() const override {
            return Type::String8;
        }

        void Process(std::string& in) override {
            in.erase(0, 1);
            value = StrHelper::Process(in, UnicodeType_8Bits);
        }

        std::shared_ptr<void> GetData() override {
            return value;
        }
    
    private:
        std::shared_ptr<uint8_t[]> value;
    };

    class String16Token : public TokenType {
    public:
        Type GetType() const override {
            return Type::String16;
        }

        void Process(std::string& in) override {
            in.erase(0, 2);
            value = StrHelper::Process(in, UnicodeType_16Bits);
        }

        std::shared_ptr<void> GetData() override {
            return value;
        }
    
    private:
        std::shared_ptr<uint8_t[]> value;
    };

    class String32Token : public TokenType {
    public:
        Type GetType() const override {
            return Type::String32;
        }

        void Process(std::string& in) override {
            in.erase(0, 2);
            value = StrHelper::Process(in, UnicodeType_32Bits);
        }

        std::shared_ptr<void> GetData() override {
            return value;
        }
    
    private:
        std::shared_ptr<uint8_t[]> value;
    };

    class String16lToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::String16l;
        }

        void Process(std::string& in) override {
            in.erase(0, 3);
            value = StrHelper::Process(in, UnicodeType_16BitsLittle);
        }

        std::shared_ptr<void> GetData() override {
            return value;
        }
    
    private:
        std::shared_ptr<uint8_t[]> value;
    };

    class String32lToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::String32l;
        }

        void Process(std::string& in) override {
            in.erase(0, 3);
            value = StrHelper::Process(in, UnicodeType_32BitsLittle);
        }

        std::shared_ptr<void> GetData() override {
            return value;
        }
    
    private:
        std::shared_ptr<uint8_t[]> value;
    };

    class String16bToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::String16b;
        }

        void Process(std::string& in) override {
            in.erase(0, 3);
            value = StrHelper::Process(in, UnicodeType_16BitsBig);
        }

        std::shared_ptr<void> GetData() override {
            return value;
        }
    
    private:
        std::shared_ptr<uint8_t[]> value;
    };

    class String32bToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::String32b;
        }

        void Process(std::string& in) override {
            in.erase(0, 3);
            value = StrHelper::Process(in, UnicodeType_32BitsBig);
        }

        std::shared_ptr<void> GetData() override {
            return value;
        }
    
    private:
        std::shared_ptr<uint8_t[]> value;
    };

    class KWFromToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_From;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("from "));
        }
    };

    class KWImportToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Import;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("import "));
        }
    };

    class KWAsToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_As;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("as "));
        }
    };

    class KWStructToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Struct;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("struct "));
        }
    };

    class KWUnionToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Union;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("union "));
        }
    };

    class KWEnumToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Enum;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("enum "));
        }
    };

    class KWTypedefToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Typedef;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("typedef "));
        }
    };

    class KWLetToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Let;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("let "));
        }
    };

    class KWSetToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Set;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("set "));
        }
    };

    class KWConstToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Const;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("const "));
        }
    };

    class KWConstExprToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_ConstExpr;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("constexpr "));
        }
    };

    class KWArrayToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Array;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("array "));
        }
    };

    class KWReferenceToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Reference;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("reference "));
        }
    };

    class KWSharedToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Shared;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("shared "));
        }
    };

    class KWPointerToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Pointer;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("pointer "));
        }
    };

    class KWExternToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Extern;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("extern "));
        }
    };

    class KWUnsafeToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Unsafe;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("unsafe "));
        }
    };

    class KWFuncToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Func;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("func "));
        }
    };

    class KWClassToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Class;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("class "));
        }
    };

    class KWPublicToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Public;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("public "));
        }
    };

    class KWProtectedToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Protected;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("protected "));
        }
    };

    class KWPrivateToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Private;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("private "));
        }
    };

    class KWVirtualToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Virtual;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("Virtual "));
        }
    };

    class KWOverrideToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Override;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("Override "));
        }
    };

    class KWStaticToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Static;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("static "));
        }
    };

    class KWSuperToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Super;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("super "));
        }
    };

    class KWIfToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_If;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("if "));
        }
    };

    class KWElifToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Elif;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("elif "));
        }
    };

    class KWElseToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Else;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("else "));
        }
    };

    class KWForToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_For;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("for "));
        }
    };

    class KWForEachToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_ForEach;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("foreach "));
        }
    };

    class KWWhileToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_While;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("while "));
        }
    };

    class KWContinueToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Continue;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("continue "));
        }
    };

    class KWBreakToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Break;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("break "));
        }
    };

    class KWMatchToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Match;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("match "));
        }
    };

    class KWReturnToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Return;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("return "));
        }
    };

    class KWLambdaToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Lambda;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("lambda "));
        }
    };

    class KWAndToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_And;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("and "));
        }
    };

    class KWOrToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Or;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("Or "));
        }
    };

    class KWNotToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::KW_Not;
        }

        void Process(std::string& in) override {
            in.erase(0, std::strlen("not "));
        }
    };

    class IdentifierToken : public TokenType {
    public:
        Type GetType() const override {
            return Type::Identifier;
        }

        void Process(std::string& in) override {
            size_t i = 0;
            std::string id = "";

            for (; i < in.length(); i++) {
                if ((in[i] >= 'a') && (in[i] <= 'z'))
                    id += in[i];
                
                else if ((in[i] >= 'A') && (in[i] <= 'A'))
                    id += in[i];
                
                else if ((in[i] >= '0') && (in[i] <= '9'))
                    id += in[i];
                
                else if (in[i] == '_')
                    id += in[i];
                
                else
                    break;
            }

            uint8_t* str = new uint8_t[i + 1];
            memcpy(str, in.c_str(), i);
            str[i] = '\0';
            in.erase(0, i);

            value = std::shared_ptr<uint8_t[]>(str);
        }

        std::shared_ptr<void> GetData() override {
            return value;
        }
    
    private:
        std::shared_ptr<uint8_t[]> value;
    };

    class FloatingSinglePattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            bool period = false;
            bool before = false;
            bool after = false;
            bool found_f = false;

            for (size_t i = 0; i < in.length(); i++) {
                if ((in[i] >= '0') && (in[i] <= '9')) {
                    if (period)
                        after = true;
                    
                    else
                        before = true;
                } else if (in[i] == '.')
                    period = true;

                else if (in[i] == 'f')
                    found_f = true;
                
                else
                    break;
            }

            return period && before && after && found_f;
        }

        Token CreateToken() const override {
            return Token(new FloatingSingleToken);
        }
    };

    class FloatingDoublePattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            bool period = false;
            bool before = false;
            bool after = false;

            for (size_t i = 0; i < in.length(); i++) {
                if ((in[i] >= '0') && (in[i] <= '9')) {
                    if (period)
                        after = true;
                    
                    else
                        before = true;
                } else if (in[i] == '.')
                    period = true;
                
                else
                    break;
            }

            return period && before && after;
        }

        Token CreateToken() const override {
            return Token(new FloatingDoubleToken);
        }
    };

    class NewLinePattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return in[0] == '\n';
        }

        Token CreateToken() const override {
            return Token(new NewLineToken);
        }
    };

    class WhiteSpacePattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return (in[0] == ' ') || (in[0] == '\t') || (in[0] == '\r');
        }

        Token CreateToken() const override {
            return Token(new WhiteSpaceToken);
        }
    };

    class UIntegerPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            char c = in[0];
            
            if (c != 'u')
                return false;
            
            c = in[1];

            if ((c >= '0') && (c <= '9')) {
                if (in.length() >= 3) {
                    switch (in[2]) {
                        case 'x':
                        case 'X':
                            if (in.length() >= 4) {
                                c = in[3];
                                if (((c >= '0') && (c <= '9')) ||
                                    ((c >= 'a') && (c <= 'f')) ||
                                    ((c >= 'A') && (c <= 'F')))
                                    return true;
                            }
                            // TODO error
                        case 'o':
                        case 'O':
                            if (in.length() >= 4) {
                                c = in[3];
                                if ((c >= '0') && (c <= '7'))
                                    return true;
                            }
                            // TODO error
                        case 'b':
                        case 'B':
                            if (in.length() >= 4) {
                                c = in[3];
                                if ((c == '0') || (c == '1'))
                                    return true;
                            }
                            // TODO error
                    }
                }

                return true;
            }

            return false;
        };

        Token CreateToken() const {
            return Token(new UIntegerToken);
        }
    };

    class IntegerPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            char c = in[0];
            size_t index = 0;

            if (c == '-')
                index++;

            if ((c >= '0') && (c <= '9')) {
                if (in.length() >= index + 2) {
                    switch (in[index + 1]) {
                        case 'x':
                        case 'X':
                            if (in.length() >= index + 3) {
                                c = in[index + 2];
                                if (((c >= '0') && (c <= '9')) ||
                                    ((c >= 'a') && (c <= 'f')) ||
                                    ((c >= 'A') && (c <= 'F')))
                                    return true;
                            }
                            // TODO error
                        case 'o':
                        case 'O':
                            if (in.length() >= index + 3) {
                                c = in[index + 2];
                                if ((c >= '0') && (c <= '7'))
                                    return true;
                            }
                            // TODO error
                        case 'b':
                        case 'B':
                            if (in.length() >= index + 3) {
                                c = in[index + 2];
                                if ((c == '0') || (c == '1'))
                                    return true;
                            }
                            // TODO error
                    }
                }

                return true;
            }

            return false;
        };

        Token CreateToken() const {
            return Token(new IntegerToken);
        }
    };

    class BooleanPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            if (StrHelper::IsFirstMatch(in.c_str(), "true"))
                return true;
            
            else if (StrHelper::IsFirstMatch(in.c_str(), "false"))
                return true;
            
            return false;
        }

        Token CreateToken() const override {
            return Token(new BooleanToken);
        }
    };

    class String8Pattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            if (in[0] != '8')
                return false;

            return StrHelper::IsMatch(in.substr(1));
        }

        Token CreateToken() const override {
            return Token(new String8Token);
        }
    };

    class String16Pattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            if ((in[0] != '1') || (in[1] == '6'))
                return false;

            return StrHelper::IsMatch(in.substr(2));
        }

        Token CreateToken() const override {
            return Token(new String16Token);
        }
    };

    class String32Pattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            if ((in[0] != '3') || (in[1] != '2'))
                return false;

            return StrHelper::IsMatch(in.substr(2));
        }

        Token CreateToken() const override {
            return Token(new String32Token);
        }
    };

    class String16lPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            if ((in[0] != '1') || (in[1] != '6') || (in[2] != 'l'))
                return false;

            return StrHelper::IsMatch(in.substr(3));
        }

        Token CreateToken() const override {
            return Token(new String16lToken);
        }
    };

    class String32lPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            if ((in[0] != '3') || (in[1] != '2') || (in[2] != 'l'))
                return false;

            return StrHelper::IsMatch(in.substr(3));
        }

        Token CreateToken() const override {
            return Token(new String32lToken);
        }
    };

    class String16bPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            if ((in[0] != '1') || (in[1] != '6') || (in[2] != 'b'))
                return false;

            return StrHelper::IsMatch(in.substr(3));
        }

        Token CreateToken() const override {
            return Token(new String16bToken);
        }
    };

    class String32bPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            if ((in[0] != '3') || (in[1] != '2') || (in[2] != 'b'))
                return false;

            return StrHelper::IsMatch(in.substr(3));
        }

        Token CreateToken() const override {
            return Token(new String32bToken);
        }
    };

    class IdentifierPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            size_t i = 0;
            char c = in[i];
            while (c == '_') {
                i++;
                if (i >= in.length())
                    return false;
                
                c = in[i];
            }

            if ((in[i] >= 'a') && (in[i] <= 'z'))
                return true;
            
            else if ((in[i] >= 'A') && (in[i]))
                return true;
            
            else if ((in[i] >= '0') && (in[i] <= '9') && (i != 0))
                return true;
            
            return false;
        }

        Token CreateToken() const override {
            return Token(new IdentifierToken);
        }
    };

    class KWFromPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "from ");
        }

        Token CreateToken() const override {
            return Token(new KWFromToken);
        }
    };

    class KWImportPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "import ");
        }

        Token CreateToken() const override {
            return Token(new KWImportToken);
        }
    };

    class KWAsPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "as ");
        }

        Token CreateToken() const override {
            return Token(new KWAsToken);
        }
    };

    class KWStructPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "struct ");
        }

        Token CreateToken() const override {
            return Token(new KWStructToken);
        }
    };

    class KWUnionPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "union ");
        }

        Token CreateToken() const override {
            return Token(new KWUnionToken);
        }
    };

    class KWEnumPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "enum ");
        }

        Token CreateToken() const override {
            return Token(new KWEnumToken);
        }
    };

    class KWTypedefPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "typedef ");
        }

        Token CreateToken() const override {
            return Token(new KWTypedefToken);
        }
    };

    class KWLetPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "let ");
        }

        Token CreateToken() const override {
            return Token(new KWLetToken);
        }
    };

    class KWSetPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "set ");
        }

        Token CreateToken() const override {
            return Token(new KWSetToken);
        }
    };

    class KWConstPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "const ");
        }

        Token CreateToken() const override {
            return Token(new KWConstToken);
        }
    };

    class KWConstExprPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "constexpr ");
        }

        Token CreateToken() const override {
            return Token(new KWConstExprToken);
        }
    };

    class KWArrayPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "array ");
        }

        Token CreateToken() const override {
            return Token(new KWArrayToken);
        }
    };

    class KWReferencePattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "reference ");
        }

        Token CreateToken() const override {
            return Token(new KWReferenceToken);
        }
    };

    class KWSharedPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "shared ");
        }

        Token CreateToken() const override {
            return Token(new KWSharedToken);
        }
    };

    class KWPointerPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "pointer ");
        }

        Token CreateToken() const override {
            return Token(new KWPointerToken);
        }
    };

    class KWExternPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "extern ");
        }

        Token CreateToken() const override {
            return Token(new KWExternToken);
        }
    };

    class KWUnsafePattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "unsafe ");
        }

        Token CreateToken() const override {
            return Token(new KWUnsafeToken);
        }
    };

    class KWFuncPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "func ");
        }

        Token CreateToken() const override {
            return Token(new KWFuncToken);
        }
    };

    class KWClassPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "class ");
        }

        Token CreateToken() const override {
            return Token(new KWClassToken);
        }
    };

    class KWPublicPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "public ");
        }

        Token CreateToken() const override {
            return Token(new KWPublicToken);
        }
    };

    class KWProtectedPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "protected ");
        }

        Token CreateToken() const override {
            return Token(new KWProtectedToken);
        }
    };

    class KWPrivatePattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "private ");
        }

        Token CreateToken() const override {
            return Token(new KWPrivateToken);
        }
    };

    class KWVirtualPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "virtual ");
        }

        Token CreateToken() const override {
            return Token(new KWVirtualToken);
        }
    };

    class KWOverridePattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "override ");
        }

        Token CreateToken() const override {
            return Token(new KWOverrideToken);
        }
    };

    class KWStaticPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "static ");
        }

        Token CreateToken() const override {
            return Token(new KWStaticToken);
        }
    };

    class KWSuperPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "super ");
        }

        Token CreateToken() const override {
            return Token(new KWSuperToken);
        }
    };
    
    class KWIfPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "if ");
        }

        Token CreateToken() const override {
            return Token(new KWIfToken);
        }
    };
    
    class KWElifPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "elif ");
        }

        Token CreateToken() const override {
            return Token(new KWElifToken);
        }
    };

    class KWElsePattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "else ");
        }

        Token CreateToken() const override {
            return Token(new KWElseToken);
        }
    };

    class KWForPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "for ");
        }

        Token CreateToken() const override {
            return Token(new KWForToken);
        }
    };

    class KWForEachPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "foreach ");
        }

        Token CreateToken() const override {
            return Token(new KWForEachToken);
        }
    };

    class KWWhilePattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "while ");
        }

        Token CreateToken() const override {
            return Token(new KWWhileToken);
        }
    };

    class KWContinuePattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "continue ");
        }

        Token CreateToken() const override {
            return Token(new KWContinueToken);
        }
    };

    class KWBreakPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "break ");
        }

        Token CreateToken() const override {
            return Token(new KWBreakToken);
        }
    };

    class KWMatchPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "match ");
        }

        Token CreateToken() const override {
            return Token(new KWMatchToken);
        }
    };

    class KWReturnPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "return ");
        }

        Token CreateToken() const override {
            return Token(new KWReturnToken);
        }
    };

    class KWLambdaPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "lambda ");
        }

        Token CreateToken() const override {
            return Token(new KWLambdaToken);
        }
    };

    class KWAndPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "and ");
        }

        Token CreateToken() const override {
            return Token(new KWAndToken);
        }
    };

    class KWOrPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "or ");
        }

        Token CreateToken() const override {
            return Token(new KWOrToken);
        }
    };

    class KWNotPattern : public PatternType {
    public:
        bool IsMatch(const std::string& in) const override {
            return StrHelper::IsFirstMatch(in.c_str(), "not ");
        }

        Token CreateToken() const override {
            return Token(new KWNotToken);
        }
    };

    std::vector<Pattern> patterns;

    void InitTokenizer() {
        patterns.push_back(Pattern(new NewLinePattern));
        patterns.push_back(Pattern(new WhiteSpacePattern));
        patterns.push_back(Pattern(new String8Pattern));
        patterns.push_back(Pattern(new String16lPattern));
        patterns.push_back(Pattern(new String32lPattern));
        patterns.push_back(Pattern(new String16bPattern));
        patterns.push_back(Pattern(new String32bPattern));
        patterns.push_back(Pattern(new String16Pattern));
        patterns.push_back(Pattern(new String32Pattern));
        patterns.push_back(Pattern(new FloatingSinglePattern));
        patterns.push_back(Pattern(new FloatingDoublePattern));
        patterns.push_back(Pattern(new UIntegerPattern));
        patterns.push_back(Pattern(new IntegerPattern));
        patterns.push_back(Pattern(new BooleanPattern));
        patterns.push_back(Pattern(new KWFromPattern));
        patterns.push_back(Pattern(new KWImportPattern));
        patterns.push_back(Pattern(new KWAsPattern));
        patterns.push_back(Pattern(new KWStructPattern));
        patterns.push_back(Pattern(new KWUnionPattern));
        patterns.push_back(Pattern(new KWEnumPattern));
        patterns.push_back(Pattern(new KWTypedefPattern));
        patterns.push_back(Pattern(new KWLetPattern));
        patterns.push_back(Pattern(new KWSetPattern));
        patterns.push_back(Pattern(new KWConstPattern));
        patterns.push_back(Pattern(new KWConstExprPattern));
        patterns.push_back(Pattern(new KWArrayPattern));
        patterns.push_back(Pattern(new KWReferencePattern));
        patterns.push_back(Pattern(new KWSharedPattern));
        patterns.push_back(Pattern(new KWPointerPattern));
        patterns.push_back(Pattern(new KWExternPattern));
        patterns.push_back(Pattern(new KWUnsafePattern));
        patterns.push_back(Pattern(new KWFuncPattern));
        patterns.push_back(Pattern(new KWClassPattern));
        patterns.push_back(Pattern(new KWPublicPattern));
        patterns.push_back(Pattern(new KWProtectedPattern));
        patterns.push_back(Pattern(new KWPrivatePattern));
        patterns.push_back(Pattern(new KWVirtualPattern));
        patterns.push_back(Pattern(new KWOverridePattern));
        patterns.push_back(Pattern(new KWStaticPattern));
        patterns.push_back(Pattern(new KWSuperPattern));
        patterns.push_back(Pattern(new KWIfPattern));
        patterns.push_back(Pattern(new KWElifPattern));
        patterns.push_back(Pattern(new KWElsePattern));
        patterns.push_back(Pattern(new KWForPattern));
        patterns.push_back(Pattern(new KWForEachPattern));
        patterns.push_back(Pattern(new KWWhilePattern));
        patterns.push_back(Pattern(new KWContinuePattern));
        patterns.push_back(Pattern(new KWBreakPattern));
        patterns.push_back(Pattern(new KWMatchPattern));
        patterns.push_back(Pattern(new KWReturnPattern));
        patterns.push_back(Pattern(new KWLambdaPattern));
        patterns.push_back(Pattern(new KWAndPattern));
        patterns.push_back(Pattern(new KWOrPattern));
        patterns.push_back(Pattern(new KWNotPattern));
        patterns.push_back(Pattern(new IdentifierPattern));
    }

    std::unique_ptr<std::vector<Token>> Tokenize(std::string input) {
        std::vector<Token> tokens;
        size_t str_length;

        while (input.length() != 0) {
            str_length = input.length();

            for (auto pattern : patterns) {
                if (pattern->IsMatch(input)) {
                    Token t = pattern->CreateToken();
                    if (t != nullptr) {
                        t->SetLineNumber(line_number);
                        t->Process(input);

                        if (t->GetType() != TokenType::Type::Ignore) 
                            tokens.push_back(t);
                        
                        break;
                    }
                }
            }

            if (str_length == input.length()) {
                // TODO error
                std::cerr << "No matching token type for: " << input << "\n";
            }
        }

        return std::make_unique<std::vector<Token>>(tokens);
    }

}