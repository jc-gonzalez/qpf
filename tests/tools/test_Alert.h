#ifndef TEST_ALERT_H
#define TEST_ALERT_H

#include "alert.h"
#include "gtest/gtest.h"

//using namespace Alert;

namespace TestAlert {

class TestAlert : public ::testing::Test {

protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    // You can do set-up work for each test here.
    TestAlert() {}

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~TestAlert() {}

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp() {
        ts =
            {
             .tm_sec   =   3,        /* seconds */
             .tm_min   =   2,        /* minutes */
             .tm_hour  =   1,        /* hours */
             .tm_mday  =  11,        /* day of the month */
             .tm_mon   =   4,        /* month, 0-based */
             .tm_year  = 118,        /* year since 1900 */
             .tm_wday  =   5,        /* day of the week, 0-based */
             .tm_yday  = 100,        /* day in the year, 0-based*/
             .tm_isdst =   1,        /* daylight saving time */
             };
                          
        v = Alert::Variable("varName");
        v.x.i = 27;
        v.ll.i = 10;
        v.ul.i = 20;
        v.type = Alert::Int;
        
        Alert::VariableHdl pv = &v;

        msgs = Alert::Messages({"Message line 1",
                                "Message line 2",
                                "Message line 3"});
           
        a = Alert(ts, Alert::Undefined, Alert::Fatal, Alert::General,
                  "the-origin", msgs, pv);
    }

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown() {}

    // Objects declared here can be used by all tests in the test case for Foo.
    Alert a;
    Alert::Variable v;
    Alert::TimeStampType ts;
    Alert::Messages msgs;
};

class TestAlertExit : public TestAlert {

protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    // You can do set-up work for each test here.
    TestAlertExit() {}

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~TestAlertExit() {}

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp() {}

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown() {}

    // Objects declared here can be used by all tests in the test case for Foo.
};

}

#endif // TEST_ALERT_H
