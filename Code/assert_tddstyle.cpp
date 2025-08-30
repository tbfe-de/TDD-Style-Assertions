/* assert_tddstyle.h (header for package assert_tddstyle)
 * ===============================================================
 * Header file for TTD-style assertions
 * ===============================================================
 */
#include "assert_tddstyle.h"

#ifdef TEST_TDDSTYLE_ASSERT

template <typename T>
auto notnullptr(T* p) {
    if (!p) throw std::invalid_argument{"null pointer"};
    return p;
}

int main() {
    int a = 6, b = 7;
    int* p = &a;
    assert_streamed("13", a+b);
    assert_streamed("-1", a-b);
    assert_streamed("42", a*b);
    assert_streamed("0.85714", a/b);
    assert_throws(<std::invalid_argument>("null pointer"),
                  [&]{ notnullptr("hello, world"); });
    assert_throws(<std::invalid_argument>("null pointer"),
                  [&]{ notnullptr(p); });
    assert_throws(<std::invalid_argument>("null pointer"),
                  [&]{ notnullptr(p = nullptr); });
}

#endif // TEST_TDDSTYLE_ASSERT
