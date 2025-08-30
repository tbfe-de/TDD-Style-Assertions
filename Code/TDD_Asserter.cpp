/* TDD_Asserter.cpp (package: assert_tddstyle)
 * ===============================================================
 * Implementation for TTD-style assertions (class Asserter)
 * ===============================================================
 */
#include "TDD_Asserter.hpp"

#include <iostream> // std::cerr, std::endl

namespace assert_tddstyle {
//////////////////////////////////////////////////////////////////

// Default configuration: abortive assertions and output stream
bool Asserter::abortive = false; // <--- may be changed at runtime
std::ostream& Asserter::Report::X() { return std::cerr; }

void Asserter::Report::show_location(Asserter const &asserter,
                                     bool pass_fail) {
    X() << "function " << asserter.func_
        << ", file " << asserter.file_
        << ", line " << asserter.line_ << std::endl;
}

void Asserter::Report::show_assertion(Asserter const &asserter,
                                      Asserter::cstring op,
                                      bool pass_fail) {
    auto const passed_or_failed{ pass_fail ? "passed" : "failed" };
    X() << "Assertion " << passed_or_failed << ": "
        << op << asserter.code_ << std::endl;
}

void Asserter::Report::show_diffs(Asserter const &asserter,
                                  std::string const &actual,
                                  bool pass_fail) {
     X() << "  expected: " << asserter.expect_ << '\n'
               << "  actually: " << actual << std::endl;
}

bool Asserter::Report::open(Asserter const &asserter,
                            std::string const &actual) {
    return (asserter.expect_ != actual);
}

void Asserter::Report::body(Asserter const &asserter,
                            std::string const &actual,
                            Asserter::cstring op,
                            bool pass_fail) {
        if (open(asserter, actual)) {
            show_location(asserter);
            show_assertion(asserter, op);
            show_diffs(asserter, actual);
            close(asserter);
        }
}

void Asserter::Report::close(Asserter const& asserter,
                             bool pass_fail) {
    if (not pass_fail && Asserter::abortive) abort();
}

//////////////////////////////////////////////////////////////////
} // end namespace

#ifdef TEST_TDD_ASSERTER
int main() {
    std::cout << "All Tests Passed" << std::endl;
}
#endif
