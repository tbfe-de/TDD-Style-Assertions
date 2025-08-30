/* TDD_ThrowsAsserter.hpp (package: assert_tddstyle)
 * ===============================================================
 * Header file for TTD-style assertions (class ThrowAsserter)
 * ===============================================================
 */
#ifndef TDDSTYLE_THROW_ASSERTER_H
#define TDDSTYLE_THROW_ASSERTER_H

#include "TDD_Asserter.hpp"

#include <string>
#include <tuple>

namespace assert_tddstyle {
//////////////////////////////////////////////////////////////////

class ThrowAsserter : public Asserter {
protected:
    using Asserter::cstring;
    using Asserter::EMPTY_;
    auto exwhat_split() const -> std::tuple<std::string, std::string>;
public:
    ThrowAsserter() : Asserter{} {/*empty*/}
    auto& file(cstring value) { Asserter::file(value); return *this; }
    auto& line(int value) { Asserter::line(value); return *this; }
    auto& func(cstring value) { Asserter::func(value); return *this; }
    auto& expect(cstring const value) { Asserter::expect(value); return *this; }
    auto& code(cstring const value) { Asserter::code(value); return *this; }
    template<typename ExpectedException>
    auto do_it(char const* expected_what) const {
        return [this](std::function<void()> code) {
            try {
                code();
                Report::body(*this, "nothing thrown", "(not throwing) ");
            }
            catch(ExpectedException const& ex) {
                auto [caught, what] = exwhat_split();
                std::string const actual = caught + R"((")" + ex.what() + R"("))";
                // using raw string literals ----------^^....................^^---
                // to put `what()`-string content in parentheses and quotes
                // the classic way were:      ... + "(\"" + ex.what() + "\")";
                bool const pass = (what == ex.what());
                Report::body(*this, actual, "(throws wrong) ", pass);
            }
        };
    }
};

//////////////////////////////////////////////////////////////////
} // end namespace

#endif // include guard
