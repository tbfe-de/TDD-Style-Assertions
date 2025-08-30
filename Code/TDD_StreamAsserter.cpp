/* TDD_StreamAsserter.cpp (package: assert_tddstyle)
 * ===============================================================
 * Implementation for TTD-style assertions (class StreamAsserter)
 * ===============================================================
 */
#include "TDD_StreamAsserter.hpp"

#include <iostream>
#include <sstream>
#include <string>

namespace assert_tddstyle {
//////////////////////////////////////////////////////////////////

/*empty*/

//////////////////////////////////////////////////////////////////
} // end namespace

#ifdef TEST_TDD_STREAM_ASSERTER
#include "assert_streamed.h"
#include <iostream>

auto sayHello() -> std::string { return "Hello"; }
int main() {
    assert_streamed("Hellox", sayHello());
    std::cout << "All Tests Passed" << std::endl;
}
#endif
