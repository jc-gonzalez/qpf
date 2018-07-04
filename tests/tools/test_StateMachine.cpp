#include "test_StateMachine.h"

//#define CheckResultOf(s,r) do {                                         \
//    ev.clear();                                                         \
//    ev.set(std::string( #s ));                                          \
//    EXPECT_EQ(ev.getValue(), r);                                        \
//    } while (0)

namespace TestStateMachine {

TEST_F(TestStateMachine, Test_StateMachine) {
    EXPECT_EQ(sm.getState(), OFF);
    EXPECT_EQ(sm.getStateName(sm.getState()), sm.getStateName(OFF));
    EXPECT_EQ(sm.getStateIdx("OFF"), OFF);

    bool isValid = sm.transitTo(INITIALISED);

    EXPECT_EQ(isValid, true);
    EXPECT_EQ(sm.getState(), INITIALISED);
    EXPECT_EQ(sm.getStateName(sm.getState()), sm.getStateName(INITIALISED));
    EXPECT_EQ(sm.getStateIdx("INITIALISED"), INITIALISED);
    EXPECT_EQ(sm.getLastTransition(), std::string("OFF => INITIALISED"));

    isValid = sm.transitTo(OPERATIONAL);

    EXPECT_EQ(isValid, false);
    EXPECT_EQ(sm.getState(), INITIALISED);
    EXPECT_EQ(sm.getLastTransition(), std::string("INITIALISED => OPERATIONAL"));
}

}           
