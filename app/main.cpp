#define DEBUG_PRINT

#include <unicode.hpp>

#include <values.hpp>
#include <tuple.hpp>

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>

#include <tokens.hpp>
#include <parse.hpp>
#include <logging.hpp>
#include <project.hpp>

Martin::UnicodeType input_unicode_type = Martin::UnicodeType_8Bits;

int main(int argc, char** argv) {
    argc--; argv++;

    if (argc < 1) {
        Martin::Warning("No file provided\n");
        return 0;
    }

    //auto project = Martin::Project::CreateEmpty();
    //project->SaveToFile(argv[0]);

    auto project = Martin::Project::LoadFromFile(argv[0]);

    project->LoadProject("examples/");

    return 0;
    
}