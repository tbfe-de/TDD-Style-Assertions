/* TDD_Asserter.hpp (package: assert_tddstyle)
 * ===============================================================
 * Header file for TTD-style assertions (class Asserter)
 * ===============================================================
 */
#ifndef TDDSTYLE_ASSERTER_H
#define TDDSTYLE_ASSERTER_H

#include <iosfwd> // class std::ostream
#include <string> // class std::string
#include <tuple> // class std::tuple

namespace assert_tddstyle {
//////////////////////////////////////////////////////////////////

class Asserter {
protected:
    //~Asserter() =default; // <--- disallow heap de-allocation
    using cstring = char const*;
    static cstring constexpr EMPTY_ = "";
    cstring file_ = EMPTY_;
    int line_ = 0;
    cstring func_ = EMPTY_;
    cstring code_ = EMPTY_;
    cstring expect_ = EMPTY_;
public:
    // non-copyable, non-movable
    Asserter()                              =default;
    Asserter(Asserter const&)               =delete;
    Asserter(Asserter&&)                    =delete;
    Asserter& operator=(Asserter const&)    =delete;
    Asserter& operator=(Asserter&&)         =delete;

    auto& file(cstring value) { file_ = value; return *this; }
    auto& line(int value) { line_ = value; return *this; }
    auto& func(cstring value) { func_ = value; return *this; }
    auto& expect(cstring value) { expect_ = value; return *this; }
    auto& code(cstring value) { code_ = value; return *this; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    static bool abortive; // configure in `Asserter.cpp`
                          // may be changed at runtime
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    struct Report {
        static std::ostream& X(); // output stream for reports
                                  // configure in `Asserter.cpp`
        static void show_location(Asserter const& asserter,
                                  bool pass_fail = false);
        static void show_assertion(Asserter const& asserter,
                                   Asserter::cstring op = "",
                                   bool pass_fail = false);
        static void show_diffs(Asserter const& asserter,
                               std::string const& actual,
                               bool pass_fail = false);
        static bool open(Asserter const& asserter,
                         std::string const& actual);
        static void body(Asserter const& asserter,
                         std::string const& actual,
                         Asserter::cstring op = "",
                         bool pass_fail = false);
        static void close(Asserter const& asserter,
                          bool pass_fail = false);
    }; // end nested struct
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

};


//////////////////////////////////////////////////////////////////
} // end namespace

#endif // include guard
