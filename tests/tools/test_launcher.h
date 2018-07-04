#ifndef TEST_Launcher_H
#define TEST_Launcher_H

#include "launcher.h"
#include "gtest/gtest.h"

//using namespace Launcher;

namespace TestLauncher {

class TestLauncher : public ::testing::Test {

protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    // You can do set-up work for each test here.
    TestLauncher() {}

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~TestLauncher() {}

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp() {}

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown() {}

    // Objects declared here can be used by all tests in the test case for Foo.
    // Launcher::obj ev;
};

class TestLauncherExit : public TestLauncher {

protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    // You can do set-up work for each test here.
    TestLauncherExit() {}

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~TestLauncherExit() {}

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

#endif // TEST_Launcher_H
