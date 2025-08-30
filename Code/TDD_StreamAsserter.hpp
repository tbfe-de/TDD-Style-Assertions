/* TDD_StreamAsserter.hpp (package: assert_tddstyle)
 * ===============================================================
 * Header file for TTD-style assertions (class StreamAsserter)
 * ===============================================================
 */
#ifndef TDDSTYLE_STREAM_ASSERTER_H
#define TDDSTYLE_STREAM_ASSERTER_H

#include "TDD_Asserter.hpp"

#include <iostream>
#include <sstream>

namespace assert_tddstyle {
//////////////////////////////////////////////////////////////////

class StreamAsserter : public Asserter {
public:
    StreamAsserter() =default;
    ~StreamAsserter() =default; // <--- makes objects possible
    auto& file(cstring value) { Asserter::file(value); return *this; }
    auto& line(int value) { Asserter::line(value); return *this; }
    auto& func(cstring value) { Asserter::func(value); return *this; }
    auto& expect(cstring const value) { Asserter::expect(value); return *this; }
    auto& code(cstring const value) { Asserter::code(value); return *this; }
    template<typename Streamable>
    void do_it(Streamable const& expr) const;
};

template<typename Streamable>
void StreamAsserter::do_it(Streamable const& expr) const {
    std::ostringstream os{};
    os.copyfmt(Report::X());
    os << expr;
    bool const pass = (os.str() == expect_);
    Report::body(*this, os.str(), "... << ", pass);
}

//////////////////////////////////////////////////////////////////
} // end namespace

#endif // include guard
