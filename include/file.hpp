#ifndef MARTIN_FILE
#define MARTIN_FILE

#include <peglib.h>
#include <string>
#include <unordered_map>

namespace Martin {

    class File {
    public:
        typedef std::pair<std::shared_ptr<peg::Ast>, bool> Definition;

        /*
         * Fix these as there can be aliases
         * std::unordered_map<std::string, Definition> imports;
         * std::unordered_map<std::string, std::unordered_map<std::string, Definition>> fromimports;
        */

        std::unordered_map<std::string, Definition> typedefs;
        std::unordered_map<std::string, Definition> unions;
        std::unordered_map<std::string, Definition> structs;
        std::unordered_map<std::string, Definition> enums;
        std::unordered_map<std::string, Definition> interfaces;
        
        std::unordered_map<std::string, Definition> variables;
        std::unordered_map<std::string, Definition> functions;
        std::unordered_map<std::string, Definition> classes;

        static std::shared_ptr<File> ReadFile(const std::string& path);
    
    private:
        std::string code;
    };

}

#endif