#include "test_RWC.h"

#include "filetools.h"

namespace TestRWC {

TEST_F(TestRWC, Test_get_and_post) {
    std::string user("user");
    std::string pwd("pwd");
    long authType = 1L;

    std::string url("https://httpbin.org/get");
    std::string localFile("/tmp/get.json");
    std::string localFileContent;
    std::string result;

    RWC rwc;

    // Get
    rwc.get(url, localFile, result);
    std::cerr << "Response from GET (get)[" << url << "]:\n" << result << '\n';
    EXPECT_NE(result.find("HTTP/1.1 200 OK"), std::string::npos);

    FileTools::storeFileIntoString(localFile, localFileContent);
    
    // Get content
    std::string content;    
    
    rwc.setAuth(user, pwd, authType);

    rwc.getContent(url, content, result);
    std::cerr << "Response from GET (getContent)[" << url << "]:\n" << result << '\n';
    EXPECT_NE(result.find("HTTP/1.1 200 OK"), std::string::npos);

    // Post
    url = "https://httpbin.org/post";
    std::string contentType("application/json");
    
    rwc.post(url, localFile, result, contentType);
    std::cerr << "Response from POST (post)[" << url << "]:\n" << result << '\n';
    EXPECT_NE(result.find("HTTP/1.1 200 OK"), std::string::npos);

    // Post content
    rwc.setAuth(user, pwd, authType);

    rwc.postContent(url, content, result, contentType);
    std::cerr << "Response from POST (postContent)[" << url << "]:\n" << result << '\n';
    EXPECT_NE(result.find("HTTP/1.1 200 OK"), std::string::npos);
}

TEST_F(TestRWC, Test_setAuth) {
    RWC rwc;
    std::string user("user");
    std::string pwd("pwd");
    long authType = 1L;
    rwc.setAuth(user, pwd, authType);
    SUCCEED();
}

}           
