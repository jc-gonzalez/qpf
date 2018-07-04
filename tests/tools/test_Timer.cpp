#include "test_Timer.h"

//#define CheckResultOf(s,r) do {                                         \
//    ev.clear();                                                         \
//    ev.set(std::string( #s ));                                          \
//    EXPECT_EQ(ev.getValue(), r);                                        \
//    } while (0)

namespace TestTimer {

TEST_F(TestTimer, Test_Timer) {
    class StoreTimes {
    public:
        StoreTimes() {}
        void storeInitialTime() { t1 = time(0); }
        void storeFinalTime() { t2 = time(0); }
        time_t difference() { return t2 - t1; }
    private:
        time_t t1, t2;
    };
    
    StoreTimes t;
    t.storeInitialTime();

    // sync
    Timer * timer = new Timer(1500, false, &StoreTimes::storeFinalTime, &t);

    EXPECT_LE(t.difference(), 2);

    delete timer;
    t.storeInitialTime();

    // asynbc
    timer = new Timer(1500, true, &StoreTimes::storeFinalTime, &t);

    sleep(2);
    EXPECT_LE(t.difference(), 2);    
}
    
}           
