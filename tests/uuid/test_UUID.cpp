#include "test_UUID.h"

//#define CheckResultOf(s,r) do {                                         \
//    ev.clear();                                                         \
//    ev.set(std::string( #s ));                                          \
//    EXPECT_EQ(ev.getValue(), r);                                        \
//    } while (0)

namespace TestUUID {

TEST_F(TestUUID, Test_UUID) {
    UUID u;
    EXPECT_EQ(u.is_null(), true);

    u.generate();
    EXPECT_EQ(u.is_null(), false);
     
    u.clear();
    EXPECT_EQ(u.is_null(), true);
}

TEST_F(TestUUID, Test_copy_compare) {
    // bool compare(const UUID & uu2);
    UUID u1;
    u1.generate();
    EXPECT_EQ(u1.is_null(), false);

    UUID u2;
    u2.generate();
    EXPECT_EQ(u1.is_null(), false);

    u2.copy(u1);
    EXPECT_EQ(u1.compare(u2), true);
    EXPECT_EQ(u1.asString(), u2.asString());
}
    
TEST_F(TestUUID, Test_generate_random) {
    // void generate_random();
    UUID u;
    EXPECT_EQ(u.is_null(), true);

    u.generate_random();
    EXPECT_EQ(u.is_null(), false);
}
    
TEST_F(TestUUID, Test_generate_time) {
    // void generate_time();
    UUID u;
    EXPECT_EQ(u.is_null(), true);

    u.generate_time();
    EXPECT_EQ(u.is_null(), false);
}
    
TEST_F(TestUUID, Test_generate_time_safe) {
    // bool generate_time_safe();
    UUID u;
    EXPECT_EQ(u.is_null(), true);

    u.generate_time_safe();
    EXPECT_EQ(u.is_null(), false);
}
    
TEST_F(TestUUID, Test_parse_unparse) {
    UUID u;
    EXPECT_EQ(u.is_null(), true);

    u.generate_random();
    std::string uuidLoStr(u.asLowerString());
    std::string uuidUpStr(u.asUpperString());

    char cUuidStr[256];
    char cUuidLoStr[256];
    char cUuidUpStr[256];

    u.unparse(cUuidStr);
    u.unparse_lower(cUuidLoStr);
    u.unparse_upper(cUuidUpStr);
    
    EXPECT_STREQ(cUuidStr, cUuidLoStr);
    
    EXPECT_STREQ(cUuidLoStr, uuidLoStr.c_str());
    EXPECT_STREQ(cUuidUpStr, uuidUpStr.c_str());

    UUID u1;
    u1.parse(cUuidLoStr);

    UUID u2;
    u2.parse(uuidUpStr);
    
    EXPECT_EQ(u1.compare(u2), true);
}
    
TEST_F(TestUUID, Test_time) {
    // time_t time(struct timeval *ret_tv);
    UUID u;
    u.generate();
    
    struct timeval tm;
    time_t t = u.time(&tm);
    int uuidType = u.type();
    int uuidVar = u.variant();
}

}   
