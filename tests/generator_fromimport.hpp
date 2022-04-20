#ifndef MARTIN_TEST_GENERATOR_FROMIMPORT
#define MARTIN_TEST_GENERATOR_FROMIMPORT

#include "testing.hpp"

#include <generators/fromimport.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_fromimport : public Test {
    public:
        std::string GetName() const override {
            return "Generator(FromImport)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("import a", TreeNodeBase::Type::Misc_FromImport, "import", true, error);
            SUBTEST_GENERATOR("import a, b", TreeNodeBase::Type::Misc_FromImport, "import", true, error);
            SUBTEST_GENERATOR("from a import b", TreeNodeBase::Type::Misc_FromImport, "from", true, error);
            SUBTEST_GENERATOR("from a import b, c", TreeNodeBase::Type::Misc_FromImport, "from", true, error);
            SUBTEST_GENERATOR("from a, b import c, d", TreeNodeBase::Type::Misc_FromImport, "from", false, error);

            SUBTEST_GENERATOR("import a as A", TreeNodeBase::Type::Misc_FromImport, "import", true, error);
            SUBTEST_GENERATOR("import a as A, b as B", TreeNodeBase::Type::Misc_FromImport, "import", true, error);
            SUBTEST_GENERATOR("from a import c as C", TreeNodeBase::Type::Misc_FromImport, "from", true, error);
            SUBTEST_GENERATOR("from a import b as B, c as C", TreeNodeBase::Type::Misc_FromImport, "from", true, error);

            return true;
        }
    };
}
#endif