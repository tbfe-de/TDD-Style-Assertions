/* main.cpp
 * ===============================================================
 * Testing the modular counter system
 * ===============================================================
*/
#include "ICounter.h"
#include "Counters.h"
#include "CounterCombos.h"

#include "assert_tddstyle.h"

#include <functional>

void test_singleCounter() {
    using namespace counter_kit;
    using namespace counter_kit::combos;

    { // Test with silent terminator :::::::::::::::::::::::::::::
    Counter<uint16_t, 3> c{};       assert_streamed("0/3", c);
    c.count_up();                   assert_streamed("1/3", c);
    c.count_up(2);                  assert_streamed("0/3", c);
    c.count_up(5);                  assert_streamed("2/3", c);
    } // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    { // Test with noisy terminator ::::::::::::::::::::::::::::::
    auto& noisy = ThrowingTerminator::singleton();
    Counter <uint16_t, 3> c{noisy}; assert_streamed("0/3", c);
    c.count_up();                   assert_streamed("1/3", c);
    c.count_up();                   assert_streamed("2/3", c);
    assert_throws(<std::overflow_error>("terminal rollover"),
                                        [&]{ c.count_up(); });
    } // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::

}

void test_DayOfWeek() {
    using namespace counter_kit;

    { // Test with sunday last :::::::::::::::::::::::::::::::::::
    DayOfWeek<DayOfWeek_Sunday::Last> dow{};
    assert_streamed("Mon",                      dow);
    assert_streamed("Tue",     dow.count_up(),  dow);
    assert_streamed("Wed",     dow.count_up(),  dow);
    assert_streamed("Thu",     dow.count_up(),  dow);
    assert_streamed("Fri",     dow.count_up(),  dow);
    assert_streamed("Sat",     dow.count_up(),  dow);
    assert_streamed("Sun",     dow.count_up(),  dow);
    assert_streamed("Mon",     dow.count_up(),  dow);
    } // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    { // Test with sunday first ::::::::::::::::::::::::::::::::::
    DayOfWeek<DayOfWeek_Sunday::First> dow{};
    assert_streamed("Sun",                       dow);
    assert_streamed("Tue",     dow.count_up(2),  dow);
    assert_streamed("Sun",     dow.count_up(5),  dow);
    assert_streamed("Sun",     dow.count_up(7),  dow);
    assert_streamed("Mon",     dow.count_up(),   dow);
    assert_streamed("Tue",     dow.count_up(),   dow);
    } // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::
}

void test_Three8BitCounterCombo() {
    using namespace counter_kit;
    using namespace counter_kit::combos;

    // Test with silent terminator
    // TBD

    // Test with throwing terminator
    // TBD
}

void test_WeekDayAndTime() {
#if 0
    using namespace counter_kit;
    using namespace counter_kit::combos;

    // TBD (always silent terminator)
#endif
}

void test_EuropeanClock() { // 00:00::59..23:59::59 - 100% logical
#if 0
    using namespace counter_kit;
    using namespace counter_kit::combos;

    // TBD (always silent terminator)
#endif
}

void test_AmericanClock() { // have fun with the 12am/pm confusion
#if 0
    using namespace counter_kit;
    using namespace counter_kit::combos;

    // TBD (always silent terminator)
#endif
}

void test_MetricDistanceMeasurement() {
#if 0
    using namespace counter_kit;
    using namespace counter_kit::combos;

    // TBD (64 bit last stage, hopefully never overflows)
#endif
}

void test_ImperialDistanceMeasurement() {
    using counter_kit::combos::ImperialDistance::Measurement;

    Measurement m{};

    auto tick_eighths = [&m](auto s) { m.count_up(s); return m; };
    assert_streamed(u8"0mi 0yd 0ft 0in", m);
    assert_streamed(u8"0mi 0yd 0ft ¾in", tick_eighths(6));
    assert_streamed(u8"0mi 0yd 0ft ⅞in", tick_eighths(1));
    assert_streamed(u8"0mi 0yd 0ft 1in", tick_eighths(1));
    assert_streamed(u8"0mi 0yd 0ft 1¼in", tick_eighths(2));
    assert_streamed(u8"0mi 0yd 0ft 1½in", tick_eighths(2));

    auto tick_inches = [&m](auto s) { m.count_up(8*s); return m; };
    assert_streamed(u8"0mi 0yd 0ft 3½in", tick_inches(2));
    // ...
    // TBD: add more tests stepping inches
    //
    // TBD: add more such functions like above for stepping feet,
    // yards, miles
    //
    auto tick_feet = [&m](auto s) { m.count_up(8*8*s); return m; };
    //
    // TBD: diligently add many more tests, especially testing
    // rollovers; BUT do NOT use the multiplied limit constants
    // directly, as otherwise the counters might use bad limits
    // and still pass the tests!
    // GENERALLY have someone else write the tests, not those who
    // wrote the code to be tested!

}

#ifdef TEST_COUNTERS_AND_COMBOS

#include <iostream>

int main() {
    test_singleCounter();
    test_DayOfWeek();
    test_Three8BitCounterCombo();
    test_WeekDayAndTime();
    test_EuropeanClock();
    test_AmericanClock();
    test_ImperialDistanceMeasurement();
    test_MetricDistanceMeasurement();

    std::cout << "All (other) tests passed" << std::endl;
}

#endif // TEST_COUNTERS_AND_COMBOS
