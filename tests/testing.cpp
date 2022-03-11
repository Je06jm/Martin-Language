#include "testing.hpp"
#include <vector>
#include <logging.hpp>

#include <stdint.h>
#include <memory>

MARTIN_TESTING_INCLUDES

namespace Martin {
    std::vector<std::shared_ptr<Test>> tests;

#define TEST_VECTOR tests

    void Init() {
        MARTIN_TESTING_INITS
    }
}

int main() {
    Martin::Init();
    uint32_t passed = 0;
    uint32_t failed = 0;
    bool success;

    Martin::Print("Found $ test.\n", Martin::tests.size());

    for (auto test : Martin::tests) {
        Martin::Print("Running '$' test...", test->GetName());
        try {
            success = test->RunTest();
        } catch (...) {
            success = false;
        }

        if (success) {
            Martin::Print("\033[0;32mOK\n");
            passed++;
        } else {
            Martin::Print("\033[0;31mFAIL\n");
            failed++;
        }
    }

    Martin::Print("Passed $ tests, and failed $ tests\n", passed, failed);

    return 0;
}