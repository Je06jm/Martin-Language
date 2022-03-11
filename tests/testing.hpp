#ifndef MARTIN_TESTING
#define MARTIN_TESTING

#include <string>

namespace Martin {
    class Test {
    public:
        virtual std::string GetName() const { return "Generic"; }
        virtual bool RunTest() { return false; }
        std::string GetError() const {
            return error;
        }
    protected:
        std::string error = "";
    };
}

#endif