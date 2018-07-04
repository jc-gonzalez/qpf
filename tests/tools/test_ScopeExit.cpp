#include "test_ScopeExit.h"

//#define CheckResultOf(s,r) do {                                         \
//    ev.clear();                                                         \
//    ev.set(std::string( #s ));                                          \
//    EXPECT_EQ(ev.getValue(), r);                                        \
//    } while (0)

namespace TestScopeExit {

TEST_F(TestScopeExit, Test_ScopeExit) {
    int a = 1;
    {
        ScopeExit reset_a([&a] { a = 1; });
        a += 10;
        EXPECT_EQ(a, 11);
    }
    EXPECT_EQ(a, 1);

    int * pa = new int(42);
    {
        ScopeExit delete_pa([&pa] { delete pa; pa = nullptr; });
        *pa /= 2;
        EXPECT_EQ(*pa, 21);
    }
    EXPECT_EQ(pa, nullptr);
}
    
}           
