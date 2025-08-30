/* assert_throws.h (header for package assert_tddstyle)V
 * ===============================================================
 * Header file for TTD-style assertions (macro assert_throws)
 * ===============================================================
 */
#ifndef TDD_ASSERT_THROWS_H
#define TDD_ASSERT_THROWS_H

#include "TDD_ThrowAsserter.hpp"

#define ASSERT_TDDSTYLE_H
#ifdef NDEBUG ////////////////////////////////////////////////////
#define assert_throws(exwhat, ...) ((void)0)
#else ////////////////////////////////////////////////////////////
#define assert_throws(whatex, ...)\
    assert_tddstyle::ThrowAsserter{}\
                    .func(__func__)\
                    .file(__FILE__)\
                    .line(__LINE__)\
                    .expect(#whatex)\
                    .code(#__VA_ARGS__)\
                    .do_it whatex(__VA_ARGS__)
#endif // NDEBUG /////////////////////////////////////////////////
#endif // include guard
