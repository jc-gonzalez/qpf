#include "test_tools.h"

//#define CheckResultOf(s,r) do {                                         \
//    ev.clear();                                                         \
//    ev.set(std::string( #s ));                                          \
//    EXPECT_EQ(ev.getValue(), r);                                        \
//    } while (0)

namespace Testtools {

TEST_F(Testtools, Test_maxmin) {
    EXPECT_EQ(max<int>(3, 5), 5);
    EXPECT_EQ(min<int>(-3, -5), -5);

    EXPECT_EQ(max<float>(3.0f, 5.0f), 5.0f);
    EXPECT_EQ(min<float>(-3.0f, -5.0f), -5.0f);

    EXPECT_EQ(max<double>(3.0, 5.0), 5.0);
    EXPECT_EQ(min<double>(-3.0, -5.0), -5.0);
}

TEST_F(Testtools, Test_waitForHeartBeat) {
    time_t t1 = time(0);
    waitForHeartBeat(0, 500000);
    time_t t2 = time(0);
    EXPECT_LE(t2 - t1, 1);
}

TEST_F(Testtools, Test_getYMD) {
    std::string dateString("20180511T123456");
    int year, month, day;
    getYMD(const_cast<char*>(dateString.c_str()), year, month, day);
    EXPECT_EQ(year,  2018);
    EXPECT_EQ(month, 5);
    EXPECT_EQ(day,   11);    
}

TEST_F(Testtools, Test_sessionTag) {
    EXPECT_EQ(sessionTag(), timeTag());
}

TEST_F(Testtools, Test_setSessionTag) {
    setSessionTag("my-tag");
    EXPECT_EQ(sessionTag(), std::string("my-tag"));
}

TEST_F(Testtools, Test_preciseTimeTag) {
    std::string tag  = timeTag();
    std::string ptag = preciseTimeTag();
    EXPECT_EQ(tag, ptag.substr(0,15));
}

TEST_F(Testtools, Test_tagToTimestamp) {
    EXPECT_EQ(tagToTimestamp(""), std::string("2001-01-01 00:00:00"));
    EXPECT_EQ(tagToTimestamp(std::string("20180511T123456")),
              std::string("2018-05-11 12:34:56"));
}

TEST_F(Testtools, Test_waitUntilNextSecond) {
    time_t t1 = time(0);
    waitUntilNextSecond();
    time_t t2 = time(0);
    EXPECT_LE(t2 - t1, 1);
}

TEST_F(Testtools, Test_mkTmpFileName) {
    char fileIdTpl[] = "/tmp/newFile_XXXXXX";
    std::string tmpFileName;
    
    mkTmpFileName(fileIdTpl, tmpFileName, false);
    std::cerr << tmpFileName << '\n';
    
    struct stat sb1;
    EXPECT_NE(stat(tmpFileName.c_str(), &sb1), -1);
    
    mkTmpFileName(fileIdTpl, tmpFileName);
    std::cerr << tmpFileName << '\n';

    struct stat sb2;
    EXPECT_EQ(stat(tmpFileName.c_str(), &sb2), -1);
}

TEST_F(Testtools, Test_rm) {
    EXPECT_EQ(mkdir("/tmp/folder1", 0755), 0);
    
    char fileIdTpl[] = "/tmp/folder1/newFile_XXXXXX";
    std::string tmpFileName;
    mkTmpFileName(fileIdTpl, tmpFileName, false);

    EXPECT_EQ(rm(const_cast<char*>(tmpFileName.c_str())), true);
    
    rmdir("/tmp/folder1");
}

TEST_F(Testtools, Test_getLoadAvgs) {
    double loadavg[3];
    int res = getloadavg(loadavg, 3);
    if (res == 0) {
        std::vector<double> v({0., 0., 0.});
        EXPECT_EQ(getLoadAvgs(), v);
    } else {
        std::vector<double> v {loadavg[0], loadavg[1], loadavg[2]};
        EXPECT_EQ(getLoadAvgs(), v);
    }
}

TEST_F(Testtools, Test_scanMemoryInfo) {
    MemData memData;
    bool res = scanMemoryInfo(memData);

    EXPECT_EQ(memData.usedMem, memData.totalMem  - memData.freeMem);
    EXPECT_LE(memData.usedSwap, memData.totalSwap);
}

TEST_F(Testtools, Test_SysInfo) {
    double period;
    SysInfo sysInfo;
    sysInfo.update();
    int nCpus = sysInfo.cpuCount;
    EXPECT_GT(nCpus, 0);
    sysInfo.computeStats();
}

}   
