// -*- C++ -*-
#include "test_Alert.h"

//#define CheckResultOf(s,r) do {                                         \
//    ev.clear();                                                         \
//    ev.set(std::string( #s ));                                          \
//    EXPECT_EQ(ev.getValue(), r);                                        \
//    } while (0)

namespace TestAlert {

TEST_F(TestAlert, Test_TimeStamp) {
    std::string tsStr(a.timeStampString());

    Alert::TimeStampType ts1 = a.getTimeStamp();
    
    char buf[80];
    strftime(buf, 80, "%Y-%m-%d %X", &ts1);
    std::string ascTimeStr(buf);

    Alert::TimeStampType ts2 = ts1;
    ts2.tm_hour = 12;
    a.setTimeStamp(ts2);
    std::string tsStr2(a.timeStampString());
    strftime(buf, 80, "%Y-%m-%d %X", &ts2);
    std::string ascTimeStr2(buf);
    
    std::cerr << tsStr << " - " << ascTimeStr << '\n';
    std::cerr << tsStr2 << " - " << ascTimeStr2 << '\n';

    EXPECT_EQ(tsStr, ascTimeStr);
    EXPECT_EQ(tsStr2, ascTimeStr2);            
}

TEST_F(TestAlert, Test_Group) {
    EXPECT_EQ(a.getGroup(), Alert::Undefined);
    a.setGroup(Alert::Diagnostics);
    EXPECT_EQ(a.getGroup(), Alert::Diagnostics);
}

TEST_F(TestAlert, Test_Severity) {
    EXPECT_EQ(a.getSeverity(), Alert::Fatal);
    a.setSeverity(Alert::Warning);
    EXPECT_EQ(a.getSeverity(), Alert::Warning);    
}

TEST_F(TestAlert, Test_Type) {    
    EXPECT_EQ(a.getType(), Alert::General);
    a.setType(Alert::OutOfRange);
    EXPECT_EQ(a.getType(), Alert::OutOfRange);    
}

TEST_F(TestAlert, Test_Origin) {
    EXPECT_EQ(a.getOrigin(), std::string("the-origin"));
    std::string newOrigin("Another-origin");
    a.setOrigin(newOrigin);
    EXPECT_EQ(a.getOrigin(), newOrigin);        
}

TEST_F(TestAlert, Test_Messages) {
    Alert::Messages curr;
    curr = a.getMessages();
    EXPECT_EQ(curr, msgs);
    Alert::Messages newmsgs({"This is a new list", "of messages"});
    a.setMessages(newmsgs);
    EXPECT_EQ(a.getMessages(), newmsgs);    
}

TEST_F(TestAlert, Test_Var) {
    Alert::VariableHdl w = a.getVar();
    EXPECT_EQ(v.name, w->name);
    v.name = "newName";
    a.setVar(&v);
    EXPECT_EQ(a.getVar()->name, std::string("newName"));
}

TEST_F(TestAlert, Test_File) {
    std::string aFile("/tmp/miFile.dat");
    a.setFile(aFile);
    EXPECT_EQ(a.getFile(), aFile);
}

TEST_F(TestAlert, Test_createNewVar) {
    a.setVar(Alert::createNewVar("name1", 15, 1, 8));
    EXPECT_EQ(a.getVar()->type, Alert::Int);
    a.setVar(Alert::createNewVar("name2", 15.0f, -1.0f, 1.0f));
    EXPECT_EQ(a.getVar()->type, Alert::Float);
    a.setVar(Alert::createNewVar("name3", -55.0, -10.0, +10.0));
    EXPECT_EQ(a.getVar()->type, Alert::Double);
}

TEST_F(TestAlert, Test_now) {
    time_t t1 = time(0);
    Alert::TimeStampType tss = Alert::now();
    time_t t2 = mktime(&tss);
    EXPECT_LT(t2 - t1, 3);
}

TEST_F(TestAlert, Test_here) {
    EXPECT_EQ(Alert::here("thisFile.c", 523),
              std::string("thisFile.c:523"));
}

TEST_F(TestAlert, Test_what) {
    std::string diag(msgs.at(0) + " (" + v.name + ": " +
                     std::to_string(v.x.i) + ", allowed range [" +
                     std::to_string(v.ll.i) + ":" +
                     std::to_string(v.ul.i) + "])");
    EXPECT_EQ(a.what(), diag);
    
    a.setVar(Alert::createNewVar("name2", 15.2f, -1.3f, 1.4f));
    diag = std::string("Message line 1 (name2: 15.2, allowed range [-1.3:1.4])");
    EXPECT_EQ(a.what(), diag);

    a.setVar(Alert::createNewVar("name3", -55.5, -10.6, 10.7));
    diag = std::string("Message line 1 (name3: -55.5, allowed range [-10.6:10.7])");
    EXPECT_EQ(a.what(), diag);
}

TEST_F(TestAlert, Test_varAsTuple) {
    std::string vt("ROW( '" + v.name +
                   "', (" + std::to_string(v.x.i) + ", 0, 0), "
                   + "(" + std::to_string(v.ll.i) + ", 0, 0), "
                   + "(" + std::to_string(v.ul.i) + ", 0, 0), 'INT')");
    EXPECT_EQ(a.varAsTuple(), vt);
    vt = std::string("ROW( 'name2', (0, 15.2, 0), (0, -1.3, 0), "
                     "(0, 1.4, 0), 'FLOAT')");
    a.setVar(Alert::createNewVar("name2", 15.2f, -1.3f, 1.4f));
    EXPECT_EQ(a.varAsTuple(), vt);
    vt = std::string("ROW( 'name3', (0, 0, -55.5), (0, 0, -10.6), "
                     "(0, 0, 10.7), 'DOUBLE')");
    a.setVar(Alert::createNewVar("name3", -55.5, -10.6, 10.7));
    EXPECT_EQ(a.varAsTuple(), vt);
}

TEST_F(TestAlert, Test_allMessages) {
    std::string allmsgs = (msgs.at(0) + ":" + msgs.at(1) + ":" + msgs.at(2));
    EXPECT_EQ(a.allMessages(":"), allmsgs);
}

TEST_F(TestAlert, Test_info) {
    std::string info = ("2018-05-11 01:02:03 [Undefined::Fatal] General the-origin: "
                        "Message line 1 (varName: 27, allowed range [10:20])");
    EXPECT_EQ(info, a.info());
}

TEST_F(TestAlert, Test_dump) {
    std::string info = ("2018-05-11 01:02:03 [Undefined::Fatal] General the-origin: "
                        "Message line 1|Message line 2|Message line 3");
    EXPECT_EQ(info, a.dump());    
}

}           
