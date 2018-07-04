#include "test_PCRegEx.h"

namespace TestPCRegEx {

std::string euclidFilenameRegEx("([A-Z]+)_([A-Z0-9]+)_"
                                "([^_]+)_([0-9]+T[\\.0-9]+Z)"
                                "[_]*([0-9]*\\.*[0-9]*)");
    
TEST_F(TestPCRegEx, Test_create) {
    PCRegEx * re1 = new PCRegEx;
    EXPECT_NE(re1, nullptr);
    EXPECT_EQ(re1->set(euclidFilenameRegEx), true);
    delete re1;
    
    PCRegEx * re2 = new PCRegEx(euclidFilenameRegEx);
    EXPECT_NE(re2, nullptr);
    delete re2;
}
    
TEST_F(TestPCRegEx, Test_match) {
    PCRegEx re(euclidFilenameRegEx);

    std::vector<std::string> mre;
    
    std::string s("E_V_Anything_987654T12345678.90Zand the rest");
    EXPECT_EQ(re.match(s), true);
    re.get(mre);
    EXPECT_EQ(mre.size(), 6);
    for (auto & g : mre) {
        std::cerr << "(" << g << ")\n";
    }
    EXPECT_EQ(mre.at(0), std::string("E_V_Anything_987654T12345678.90Z"));
    EXPECT_EQ(mre.at(1), std::string("E"));
    EXPECT_EQ(mre.at(2), std::string("V"));
    EXPECT_EQ(mre.at(3), std::string("Anything"));
    EXPECT_EQ(mre.at(4), std::string("987654T12345678.90Z"));
    EXPECT_EQ(mre.at(5), std::string(""));

    s = "E_V_Anything_ThisDoesNotMatch";
    EXPECT_EQ(re.match(s), false);
}
    
TEST_F(TestPCRegEx, Test_badRegEx) {
    PCRegEx * re = new PCRegEx;
    EXPECT_NE(re, nullptr);
    EXPECT_EQ(re->set("([a-z]+"), false);
    delete re;
}
    
}           
