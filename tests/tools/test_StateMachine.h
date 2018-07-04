#ifndef TEST_STATEMACHINE_H
#define TEST_STATEMACHINE_H

#include "sm.h"
#include "gtest/gtest.h"

//using namespace StateMachine;

static const int ERROR        = -1;
static const int OFF          =  0;
static const int INITIALISED  =  1;
static const int RUNNING      =  2;
static const int OPERATIONAL  =  3;

namespace TestStateMachine {

class TestStateMachine : public ::testing::Test {
    
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    class MyStateMachine : public StateMachine {
    public:
        MyStateMachine() {
            defineState(ERROR,        "ERROR");
            defineState(OFF,          "OFF");
            defineState(INITIALISED,  "INITIALISED");
            defineState(RUNNING,      "RUNNING");
            defineState(OPERATIONAL,  "OPERATIONAL");
            
            defineValidTransition(ERROR,        OFF);
            defineValidTransition(OFF,          INITIALISED);
            defineValidTransition(INITIALISED,  RUNNING);
            defineValidTransition(INITIALISED,  OFF);
            defineValidTransition(INITIALISED,  ERROR);
            defineValidTransition(RUNNING,      OPERATIONAL);
            defineValidTransition(RUNNING,      OFF);
            defineValidTransition(RUNNING,      ERROR);
            defineValidTransition(OPERATIONAL,  RUNNING);
            defineValidTransition(OPERATIONAL,  OFF);
            defineValidTransition(OPERATIONAL,  ERROR);
        
            setState(OFF);
        }

        std::string getLastTransition() { return lastTransit; }       
    protected:
        virtual void afterTransition(int fromState, int toState) {
            lastTransit = (getStateName(fromState) + " => " +
                           getStateName(toState));
            StateMachine::afterTransition(fromState, toState);
        }
    private:
        std::string lastTransit;
    };
            
    // You can do set-up work for each test here.
    TestStateMachine() {}

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~TestStateMachine() {}

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp() {}

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown() {}

    // Objects declared here can be used by all tests in the test case for Foo.
    // StateMachine::obj ev;

    // Valid Manager states
    MyStateMachine sm;
    
};

class TestStateMachineExit : public TestStateMachine {

protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    // You can do set-up work for each test here.
    TestStateMachineExit() {}

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~TestStateMachineExit() {}

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

#endif // TEST_STATEMACHINE_H
