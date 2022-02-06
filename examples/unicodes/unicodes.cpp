#include <nodes/node.hpp>
#include <nodes/numbers.hpp>
#include <nodes/strings.hpp>
#include <unicode.hpp>

#include <stdio.h>
#include <iostream>
#include <string>

UnicodeType input_unicode_type = UnicodeType_8Bits;

extern Node* program;
extern int yyparse();
extern FILE* yyin;
extern FILE* yyout;

void print(String* str) {
    const uint8_t* string;
    bool allocated = false;
    if (str->SubName() == "String8")
        string = str->value;
    
    else if (str->SubName() == "String16") {
        string = unicode_convert(str->value, UnicodeType_16Bits, UnicodeType_8Bits);
        allocated = true;
    } else if (str->SubName() == "String32") {
        string = unicode_convert(str->value, UnicodeType_32Bits, UnicodeType_8Bits);
        allocated = true;
    } else if (str->SubName() == "String16l") {
        string = unicode_convert(str->value, UnicodeType_16BitsLittle, UnicodeType_8Bits);
        allocated = true;
    } else if (str->SubName() == "String32l") {
        string = unicode_convert(str->value, UnicodeType_32BitsLittle, UnicodeType_8Bits);
        allocated = true;
    } else if (str->SubName() == "String16b") {
        string = unicode_convert(str->value, UnicodeType_16BitsBig, UnicodeType_8Bits);
        allocated = true;
    } else if (str->SubName() == "String32b") {
        string = unicode_convert(str->value, UnicodeType_32BitsBig, UnicodeType_8Bits);
        allocated = true;
    }

    std::cout << (const char*)string;

    if (allocated)
        delete[] string;
}

int main(int argc, const char** argv) {
    argc--; argv++;

    FILE* file;
    if (argc == 1)
        file = fopen(argv[0], "r");
    
    else {
        std::cout << "Expected file\n";
        return 0;
    }

    if (file == NULL) {
        std::cout << "Invalid file\n";
        return 0;
    }

    input_unicode_type = UnicodeType_8Bits;

    yyin = file;
    yyout = stdout;

    yyparse();

    fclose(file);

    std::cout << program->Name() << "\n";
    String* num = (String*)program;
    std::cout << num->SubName() << "\n";

    print(num);

    delete program;

    return 0;
}