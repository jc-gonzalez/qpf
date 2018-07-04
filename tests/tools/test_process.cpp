#include "test_process.h"

//#define CheckResultOf(s,r) do {                                         \
//    ev.clear();                                                         \
//    ev.set(std::string( #s ));                                          \
//    EXPECT_EQ(ev.getValue(), r);                                        \
//    } while (0)

namespace Testprocess {

TEST_F(Testprocess, Test_sample1) {

    procxx::process ping( "ping", "www.google.com", "-c", "2" );
    ping.exec();

    std::string line;
    while( std::getline( ping.output(), line ) )
    {
        std::cout << line << std::endl;
        if( !ping.running() || !procxx::running(ping.id()) || !running(ping) )
        {
            std::cout << "not running any more" << std::endl;
            break;
        }
    }

    ping.wait();
    std::cout << "exit code: " << ping.code() << std::endl;

    EXPECT_EQ(ping.killed(), true);
    EXPECT_EQ(ping.stopped(), false);
    
    SUCCEED();
}


TEST_F(Testprocess, Test_sample2) {

    // construct a child process that runs `cat`
    procxx::process cat{"cat"};
    
    // construct a child process that runs `wc -c`
    procxx::process wc{"wc", "-c"};
    
    // set up the pipeline and execute the child processes
    (cat | wc).exec();
    
    // write "hello world" to the standard input of the cat child process
    cat << "hello world";
    
    // close the write end (stdin) of the cat child
    cat.close(procxx::pipe_t::write_end());
    
    // read from the `wc -c` process's stdout, line by line
    std::string line;
    while (std::getline(wc.output(), line)) {
        std::cout << line << std::endl;
    }

    SUCCEED();
}

TEST_F(Testprocess, Test_sample3) {

    // OPTION 1: same limits for all processes in the pipeline
    {
        procxx::process cat{"cat"};
        procxx::process wc{"wc", "-c"};
        
        procxx::process::limits_t limits;
        limits.cpu_time(3);         // 3 second execution time limit
        limits.memory(1024*1024*1); // 1 MB memory usage limit
        (cat | wc).limit(limits).exec();
    }
    
    // OPTION 2: individual limits for each process
    {
        procxx::process cat{"cat"};
        procxx::process wc{"wc", "-c"};
        
        procxx::process::limits_t limits_wc;
        limits_wc.cpu_time(3);         // 3 second execution time limit
        limits_wc.memory(1024*1024*1); // 1 MB memory usage limit
        wc.limit(limits_wc);
        
        procxx::process::limits_t limits_cat;
        limits_cat.cpu_time(1);  // 1 second execution time limit
        limits_cat.memory(1024); // 1 KB memory usage limit
        cat.limit(limits_cat);
        
        (cat | wc).exec();
    }
    
    SUCCEED();
}
    
}           
