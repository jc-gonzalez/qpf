#include "test_Log.h"

//#define CheckResultOf(s,r) do {                                         \
//    ev.clear();                                                         \
//    ev.set(std::string( #s ));                                          \
//    EXPECT_EQ(ev.getValue(), r);                                        \
//    } while (0)

bool existsGetLastLine(std::string file, std::string & lastLine)
{
    std::ifstream iFile(file);
    if (!iFile.good()) return false;
    while (!iFile.eof()) {
        std::getline(iFile, lastLine);
    }
    return true;
}

std::string tail(std::string const& source, size_t const length) {
  if (length >= source.size()) { return source; }
  return source.substr(source.size() - length);
} // tail

namespace TestLog {

TEST_F(TestLog, Test_log) {
    Log::log(Log::System, Log::DEBUG, "Message # 1");

    std::string file("/qpf/run/SYSTEM.log");
    std::string lastLine;
    
    EXPECT_EQ(existsGetLastLine(file, lastLine), true);
    EXPECT_EQ(tail(lastLine), 
}

TEST_F(TestLog, Test_getLastLogMsgs) {
    
}

TEST_F(TestLog, Test_defineLogSystem) {
    
}

TEST_F(TestLog, Test_defineSizeOfLogBuffer) {
    
}

TEST_F(TestLog, Test_getTimeTag) {
    
}

TEST_F(TestLog, Test_setConsoleOutput) {
    
}

TEST_F(TestLog, Test_setQuietExit) {
    
}

TEST_F(TestLog, Test_setLogBaseDir) {
    
}

TEST_F(TestLog, Test_getLogFileName) {
    
}

TEST_F(TestLog, Test_getLogBaseDir) {
    
}

TEST_F(TestLog, Test_setMinLogLevel) {
    
}

TEST_F(TestLog, Test_getMinLogLevel) {
    
}

}           
