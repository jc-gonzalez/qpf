#include "test_filetools.h"

namespace TestFiletools {

TEST_F(TestFiletools, Test_generateTmpFile) {
    std::string tmpFile = FileTools::generateTmpFile();
    std::cerr << tmpFile << '\n';
}

TEST_F(TestFiletools, Test_storeFileIntoString) {
    std::string loadAvg;
    std::string iFile("/etc/fstab");
    FileTools::storeFileIntoString(iFile, loadAvg);
    EXPECT_EQ(loadAvg.empty(), false);
}

TEST_F(TestFiletools, Test_copyfile) {
    std::string sFrom("/etc/fstab");
    std::string sTo("/tmp/etc-fstab");
    int res = FileTools::copyfile(sFrom, sTo);
    EXPECT_EQ(res, 0);
    
    std::string contentFrom, contentTo;
    FileTools::storeFileIntoString(sFrom, contentFrom);
    FileTools::storeFileIntoString(sTo, contentTo);
    EXPECT_EQ(contentFrom, contentTo);    
}

TEST_F(TestFiletools, Test_rcopyfile) {
    std::string sFrom("/etc/fstab");
    std::string sTo("/tmp/etc-fstab");
    std::string remoteHost("127.0.0.1");
    int res = 0;
    
    res = FileTools::rcopyfile(sFrom, sTo, remoteHost, false);
    EXPECT_EQ(res, 0);
    
    std::string contentFrom, contentTo;
    FileTools::storeFileIntoString(sFrom, contentFrom);
    FileTools::storeFileIntoString(sTo, contentTo);
    EXPECT_EQ(contentFrom, contentTo);    

    sFrom = "/tmp/etc-fstab";
    sTo = "/tmp/etc-fstab-copy";
    res = FileTools::rcopyfile(sFrom, sTo, remoteHost, true);
    EXPECT_EQ(res, 0);

    FileTools::storeFileIntoString(sFrom, contentFrom);
    FileTools::storeFileIntoString(sTo, contentTo);
    EXPECT_EQ(contentFrom, contentTo);        
}

TEST_F(TestFiletools, Test_runlink) {
    std::string sFile1("/tmp/etc-fstab");
    std::string sFile2("/tmp/etc-fstab-copy");
    std::string remoteHost("127.0.0.1");
    
    EXPECT_EQ(FileTools::runlink(sFile1, remoteHost), 0);
    EXPECT_EQ(FileTools::runlink(sFile2, remoteHost), 0);
}

}   
