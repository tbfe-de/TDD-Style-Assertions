/* assert_streamed.h (header for package assert_tddstyle)
 * ===============================================================
 * Header file for TTD-style assertions (macro assert_streamed)
 * ===============================================================
 */
#ifndef TDD_ASSERT_STREAMED_H
#define TDD_ASSERT_STREAMED_H

#include "TDD_StreamAsserter.hpp"

#ifdef NDEBUG ////////////////////////////////////////////////////
#define assert_streamed(expect_arg, ...) ((void)0)
#else ////////////////////////////////////////////////////////////
#define assert_streamed(expect_arg, ...)\
    do {\
        assert_tddstyle::StreamAsserter asserter{};\
        asserter.file(__FILE__)\
                .line(__LINE__)\
                .func(__func__)\
                .expect(expect_arg)\
                .code(#__VA_ARGS__)\
                .do_it((__VA_ARGS__));\
    } while(0)
#endif // NDEBUG /////////////////////////////////////////////////

#endif // include guard
