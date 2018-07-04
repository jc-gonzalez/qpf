#include "test_DirWatcher.h"

#include <iostream>
#include <fstream>  

namespace TestDirWatcher {

TEST_F(TestDirWatcher, Test_watch) {
    std::string dwPath1("/tmp/dirwatcher.dir1");
    mkdir(dwPath1.c_str(), 0755);
    DirWatcher dw(dwPath1);
    
    std::string dwPath2("/tmp/dirwatcher.dir2");
    mkdir(dwPath2.c_str(), 0755);
    dw.watch(dwPath2);
    /*
    std::string dwPath3("/tmp/dirwatcher.dir3");
    EXPECT_EXIT({ dw.watch(dwPath3); },
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "inotify_add_watch");*/
    rmdir(dwPath2.c_str());
}

TEST_F(TestDirWatcher, Test_nextEvent) {
    std::string dwPath1("/tmp/dirwatcher.dir1");
    std::string baseName1("test.txt");
    std::string file1(dwPath1 + "/" + baseName1);

    DirWatcher * dw = new DirWatcher(dwPath1);        
    DirWatcher::DirWatchEvent event;

    std::ofstream *outfile = new std::ofstream(file1);
    *outfile << "my text here!\n";
    outfile->close();
    delete outfile;
    
    std::string name1, name2, name3;
    std::vector<std::string> pths;
    for (int i = 0; i < 300; i += 3) {
        name1 = dwPath1 + "/test_" + std::to_string(i) + ".txt";
        outfile = new std::ofstream(name1);
        *outfile << "my text here!\n";
        outfile->close();
        delete outfile;
        pths.push_back(name1);

        name2 = dwPath1 + "/test_" + std::to_string(i + 1) + ".hlnk.txt";
        link(name1.c_str(), name2.c_str());
        pths.push_back(name2);
        
        name3 = dwPath1 + "/test_" + std::to_string(i + 2) + ".slnk.txt";
        symlink(name1.c_str(), name3.c_str());        
        pths.push_back(name3);
    }

    sleep(1);

    while (dw->nextEvent(event)) {
        EXPECT_EQ(event.path, dwPath1);
        std::cerr << "event: { name: " << event.name
                  << ", path: " << event.path
                  << ", isDir: " << (event.isDir ? 'T' : 'F') << '\n';
        unlink((event.path + "/" + event.name).c_str());
    }
    
    dw->stop();
    delete dw;
    dw = nullptr;
    
    rmdir(dwPath1.c_str());
}

}           
