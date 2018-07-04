#include "test_launcher.h"

namespace TestLauncher {

TEST_F(TestLauncher, Test_Launchers) {
    std::string prg("echo");
    std::vector<std::string> args {"'This is the argument'", "'and also this'"};

    Launcher l;

    bool result = l.exec();
    EXPECT_EQ(result, false);

    l.create(prg, args);
    result = l.exec();
    EXPECT_EQ(result, true);

    IPythonLauncher * fakeIpython = new IPythonLauncher("echo", "/tmp");
    EXPECT_NE(fakeIpython, nullptr);
    delete fakeIpython;
    
    JupyterLauncher * fakeJup = new JupyterLauncher("echo", "/tmp");
    EXPECT_NE(fakeJup, nullptr);
    delete fakeJup;
}

}           
