/* TDD_ThrowAsserter.cpp (package: assert_tddstyle)
 * ===============================================================
 * Implementation for TTD-style assertions (class ThrowAsserter)
 * ===============================================================
 */
#include "TDD_ThrowAsserter.hpp"

#include <cstring> // std::strchr

namespace assert_tddstyle {
//////////////////////////////////////////////////////////////////

auto ThrowAsserter::exwhat_split() const
        -> std::tuple<std::string, std::string> {
    auto const p0 = expect_;
    auto const p1 = std::strchr(p0, '<');
    auto const p2 = std::strchr(p1, '>') + 1;
    auto const p3 = std::strchr(p2, '(');
    auto const p4 = std::strchr(p3, ')') + 1;
    return {
        {p1, size_t(p2 - p1)},
        {p3, size_t(p4 - p3)}
    };
}

//////////////////////////////////////////////////////////////////
} // end namespace

#ifdef TEST_TDD_THROW_ASSERTER
#include "assert_throws.h"
#include <iostream>
#include <stdexcept>
int main() {
    assert_throws(<std::runtime_error>("wow"), [] {
                            // throw std::runtime_error("test");
                        });
    std::cout << "All Tests Passed" << std::endl;
}
#endif
