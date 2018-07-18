#include "test_Bus.h"

//#define CheckResultOf(s,r) do {                                         \
//    ev.clear();                                                         \
//    ev.set(std::string( #s ));                                          \
//    EXPECT_EQ(ev.getValue(), r);                                        \
//    } while (0)

namespace TestBus {

TEST_F(TestBus, Test_connectTo) {
    std::string name("bus");
    std::string source("127.0.0.1");
    std::string target("127.0.0.1");
    int cls = 42;
    /*
    Bus x(42, source);

    EXPECT_EQ(x.getClass(), cls);
    EXPECT_EQ(x.getClassName(), "42");
    EXPECT_EQ(x.getName(), name);
    */
}

}           
