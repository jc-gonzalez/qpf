#include "test_VOSpaceHandler.h"
//#include "rwc-stub.h"

#include <iostream>
#include <fstream>  

namespace TestVOSpaceHandler {
/*
TEST_F(TestVOSpaceHandler, Test_setVOSpaceUrl) {

    RWC * rwcStubHdl = new RWC;
    std::string url("https://vospace.esac.esa.int/vospaece/");

    VOSpaceHandler * vosHdl = new VOSpaceHandler(rwcStubHdl, url);
    EXPECT_NE(vosHdl, nullptr);

    vosHdl->setVOSpaceUrl(url);
    
    delete vosHdl;
}

TEST_F(TestVOSpaceHandler, Test_setAuth) {
    
    RWC * rwcStubHdl = new RWC;
    std::string url("https://vospace.esac.esa.int/vospace/");
    
    VOSpaceHandler * vosHdl = new VOSpaceHandler(rwcStubHdl, url);
    EXPECT_NE(vosHdl, nullptr);

    std::string user("eucops"), pwd("Eu314_clid");
    vosHdl->setAuth(user, pwd);
    
    delete vosHdl;
}

TEST_F(TestVOSpaceHandler, Test_uploadAndDownload) {
    
    std::string url("https://vospace.esac.esa.int/vospace/");
    std::string user("eucops"), pwd("Eu314_clid");
    std::string folder("tests");
    std::string fileName1("file1-test.txt");
    std::string fileName2("file2-test.txt");
    std::string content("This is the file content");

    std::ofstream upfile(fileName2);
    std::string content2("This is another different file content");

    std::string retrieved;
    std::string retrieved2;

    RWC * rwcStubHdl = new RWC;

    VOSpaceHandler * vosHdl = new VOSpaceHandler(rwcStubHdl, url);
    EXPECT_NE(vosHdl, nullptr);

    try {
    vosHdl->setAuth(user, pwd);
    } catch(...) { std::cerr << "1) HEY!\n"; exit(1); }

    bool result;

    rwcStubHdl->setResult
        ("HTTP/1.1 200 OK\n"
         "Location: https://vospace.esac.esa.int/vospace/url/THE_JOB_ID");
    rwcStubHdl->setContent
        ("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
         "<uws:job>\n"
         "  <uws:phase>COMPLETED</uws:phase>\n"
         "</uws:job>");
    
    try {
    result = vosHdl->uploadToFile(folder, fileName1, content);
    } catch(...) { std::cerr << "2) HEY!\n"; exit(1); }
    
    EXPECT_EQ(result, true);

    try {
    upfile << content2 << std::endl;
    upfile.close();
    } catch(...) { std::cerr << "3) HEY!\n"; exit(1); }

    try {
    result = vosHdl->uploadFile(folder, fileName2);
    } catch(...) { std::cerr << "4) HEY!\n"; exit(1); }

    EXPECT_EQ(result, true);

    try {
    result = vosHdl->downloadFromFile(folder, fileName1, retrieved);
    } catch(...) { std::cerr << "5) HEY!\n"; exit(1); }

    EXPECT_EQ(result, true);
    EXPECT_EQ(retrieved, content);

    try {
    result = vosHdl->downloadFile(folder, fileName2, fileName2);
    } catch(...) { std::cerr << "6) HEY!\n"; exit(1); }

    EXPECT_EQ(result, true);
    
    try {
    std::ifstream dwnfile(fileName2);
    std::getline(dwnfile, retrieved2);
    dwnfile.close();
    } catch(...) { std::cerr << "7) HEY!\n"; exit(1); }

    EXPECT_EQ(retrieved2, content2);

    delete vosHdl;
}
*/
}           
