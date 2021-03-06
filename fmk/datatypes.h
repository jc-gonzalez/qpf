/******************************************************************************
 * File:    datatypes.h
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.libQPF.datatypes
 *
 * Version:  2.0
 *
 * Date:    2015/07/01
 *
 * Author:   J C Gonzalez
 *
 * Copyright (C) 2015-2018 Euclid SOC Team @ ESAC
 *_____________________________________________________________________________
 *
 * Topic: General Information
 *
 * Purpose:
 *   Declare Msgdatatypes class
 *
 * Created by:
 *   J C Gonzalez
 *
 * Status:
 *   Prototype
 *
 * Dependencies:
 *   CommNode
 *
 * Files read / modified:
 *   none
 *
 * History:
 *   See <Changelog>
 *
 * About: License Conditions
 *   See <License>
 *
 ******************************************************************************/

#ifndef DATATYPES_H
#define DATATYPES_H

//============================================================
// Group: External Dependencies
//============================================================
#include <iostream>

//------------------------------------------------------------
// Topic: System headers
//   - string
//   - map
//   - set
//------------------------------------------------------------
#include <string>
#include <map>
#include <vector>
#include <set>

//------------------------------------------------------------
// Topic: External packages
//   none
//------------------------------------------------------------

//------------------------------------------------------------
// Topic: Project headers
//   - json/json.h
//------------------------------------------------------------
#include "json/json.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
//namespace QPF {

//============================================================
// Group: Constants
//============================================================

//------------------------------------------------------------
// Topic: Spaces for product files
//------------------------------------------------------------

const std::string ExternalSpace("EXTERNAL");
const std::string UserSpace("USER");
const std::string InboxSpace("INBOX");
const std::string LocalArchSpace("LOCAL_ARCHIVE");
const std::string GatewaySpace("GATEWAY");
const std::string ProcessingSpace("PROCESSING");
const std::string ReprocessingSpace("REPROCESSING");
const std::string ReprocessingUserArea("USER_AREA");
const std::string ReprocessingLocalFolder("LOCAL_FOLDER");
const std::string ReprocessingVOSpace("VOSPACE");

const std::set<std::string> URLSpaces { ExternalSpace,
        UserSpace,
        InboxSpace,
        LocalArchSpace,
        GatewaySpace,
        ProcessingSpace,
        ReprocessingSpace,
        ReprocessingUserArea,
        ReprocessingLocalFolder,
        ReprocessingVOSpace };

//============================================================
// Group: JSON based macros and classes
//============================================================

#include "json/json.h"

typedef Json::Value  json;

#define JSTR(e)  std::string e () { return value[ #e ].asString(); }
#define JINT(e)  int         e () { return value[ #e ].asInt(); }
#define JDLB(e)  double      e () { return value[ #e ].asDouble(); }
#define JBOOL(e) bool        e () { return value[ #e ].asBool(); }

#define JSTRIDX(e) std::string e (int i) { return value[i][ #e ].asString(); }
#define JINTIDX(e) int         e (int i) { return value[i][ #e ].asInt(); }
#define JDLBIDX(e) double      e (int i) { return value[i][ #e ].asDouble(); }

#define JSTRVEC(e) std::vector<std::string> e () {                      \
        json arr = value[ #e ];                                         \
        std::vector<std::string> a;                                     \
        for (int i = 0; i < arr.size(); ++i) {                           \
            a.push_back(arr[i].asString()); }                           \
        return a; }
#define JSTRINTMAP(e) std::map<std::string, int> e () {                 \
        json mp = value[ #e ];                                          \
        std::map<std::string, int> m;                                   \
        Json::Value::iterator it = mp.begin();                          \
        while (it != mp.end()) {                                         \
            m[it.key().asString()] = (int)((*it).asInt()); ++it; }       \
        return m; }
#define JSTRSTRMAP(e) std::map<std::string, std::string> e () {         \
        json mp = value[ #e ];                                          \
        std::map<std::string, std::string> m;                           \
        Json::Value::iterator it = mp.begin();                          \
        while (it != mp.end()) {                                         \
            m[it.key().asString()] = ((*it).asString()); ++it; }         \
        return m; }
#define JSTRGRPMAP(g,e) std::map<std::string, g> e () {                 \
        json mp = value[ #e ];                                          \
        std::map<std::string, g> m;                                     \
        Json::Value::iterator it = mp.begin();                          \
        while (it != mp.end()) {                                         \
            m[it.key().asString()] = g(*it); ++it; }                     \
        return m; }

#define JOBJ(e) json  e () { return value[ #e ]; }

#define JRECORD(e) JRecord e () { return JRecord(value[ #e ]); }

#define SET_GRP(c,e) e = c ( v[ #e ] );
#define SET_GRP2(c,e,f) e.f = c ( v[ #e ][ #f ] );
#define GRP(c,e) c e;

#define DUMPJSTR(e)  std::cerr << #e << ": " << value[ #e ].asString() << std::endl;
#define DUMPJINT(e)  std::cerr << #e << ": " << value[ #e ].asInt() << std::endl;
#define DUMPJDLB(e)  std::cerr << #e << ": " << value[ #e ].asDouble() << std::endl;
#define DUMPJBOOL(e) std::cerr << #e << ": " << std::boolalpha << value[ #e ].asBool() << std::endl;

#define FOREACH(i) for (int i = 0; i < value.size(); ++i)

#define DUMPJSTRIDX(i,e) std::cerr << #e << ": " << value[i][ #e ].asString() << std::endl;
#define DUMPJINTIDX(i,e) std::cerr << #e << ": " << value[i][ #e ].asInt() << std::endl;
#define DUMPJDLBIDX(i,e) std::cerr << #e << ": " << value[i][ #e ].asDouble() << std::endl;

#define DUMPJSTRVEC(e) do {                                             \
        std::cerr << #e << ": [" << std::endl;                             \
        for (int i = 0; i < value[ #e ].size(); ++i) {                   \
            std::cerr << "\t'" << value[ #e ][i].asString() << "'\n"; }    \
        std::cerr << "]" << std::endl; } while(0)
#define DUMPJSTRINTMAP(e) do {                                          \
        json mp = value[ #e ];                                          \
        Json::Value::iterator it = mp.begin();                          \
        std::cerr << #e << ": {" << std::endl;                             \
        while (it != mp.end()) {                                         \
            std::cerr << '\t' << it.key().asString()                      \
                      << ": " << (int)((*it).asInt()) << "\n";             \
            ++it; }                                                      \
        std::cerr << "}" << std::endl; } while(0)
#define DUMPJSTRSTRMAP(e) do {                                          \
        json mp = value[ #e ];                                          \
        Json::Value::iterator it = mp.begin();                          \
        std::cerr << #e << ": {" << std::endl;                             \
        while (it != mp.end()) {                                         \
            std::cerr << '\t' << it.key().asString()                      \
                      << ": '" << ((*it).asString()) << "'\n";             \
            ++it; }                                                      \
        std::cerr << "}" << std::endl; } while(0)
#define DUMPJSTRGRPMAP(g,e) do {                                \
        json mp = value[ #e ];                                  \
        Json::Value::iterator it = mp.begin();                  \
        std::cerr << #e << ": {" << std::endl;                      \
        while (it != mp.end()) {                                  \
            std::cerr << '\t' << it.key().asString() << ":\n";      \
            g(*it).dump();                                       \
            ++it; }                                               \
        std::cerr << "}" << std::endl; } while(0)

class JValue {
public:
    JValue();
    JValue(json val);
    JValue(std::string s);
    JValue operator()(std::string key);
    json & operator[](std::string key);
    std::string str(bool styled = false);
    std::string sortedStr(std::vector<std::string> sortKeys);
    void fromStr(std::string content = std::string());
    json & val();
    int size();
    bool has(const char * key);
protected:
    json value;
};

extern json nullJson;

class JRecord : public JValue {
public:
    JRecord() {}
    JRecord(json v) : JValue(v) {}
    JRecord(std::string s) : JValue(s) {}
    virtual void dump() {}
};

//============================================================
// Group: Basic datatypes
//============================================================

// Running mode of the agent.  If SERVICE, a Docker Swarm is created
enum AgentMode { CONTAINER, SERVICE };

#undef T

#define TLISTOF_USER_AREA_TYPES \
    T(NOMINAL),                              \
    T(LOCAL),                                \
    T(VOSPACE)

#define T(x) UA_ ## x
enum UserAreaId { TLISTOF_USER_AREA_TYPES };
#undef T

#define T(x) std::string( #x )
const std::string UserAreaName[] = { TLISTOF_USER_AREA_TYPES };
#undef T

const std::map<std::string, UserAreaId> UserAreaIdx = { {UserAreaName[UA_NOMINAL], UA_NOMINAL},
                                                        {UserAreaName[UA_LOCAL],   UA_LOCAL},
                                                        {UserAreaName[UA_VOSPACE], UA_VOSPACE} };

//------------------------------------------------------------
// Topic: Elementary types
//------------------------------------------------------------

typedef std::string   ProductType;
typedef std::string   DateTime;
typedef std::string   DateRange;
typedef std::string   URL;
typedef std::string   URLSpace;
typedef unsigned int  ObsId;
typedef std::string   Instrument;
typedef std::string   ObsMode;
typedef unsigned int  Exposure;
typedef std::string   Creator;
typedef std::string   Mission;
typedef std::string   Origin;
typedef std::string   ProcFunction;
typedef std::string   FileType;
typedef std::string   ProductParams;
typedef std::string   ProductId;
typedef std::string   ProductVersion;
typedef std::string   ProductStatus;
typedef unsigned int  ProductSize;
typedef std::string   Signature;
typedef std::string   FileNamePart;

//------------------------------------------------------------
// Topic: Structures
//------------------------------------------------------------

struct ProductMetadata : public JRecord {
    ProductMetadata() {}
    ProductMetadata(json v) : JRecord(v) {}
    virtual void dump() {
        DUMPJSTR(mission);        // %M
        DUMPJSTR(startTime);      // %f
        DUMPJSTR(endTime);        // %t
        DUMPJSTR(regTime);
        DUMPJSTR(timeInterval);   // %D
        DUMPJINT(obsId);
        DUMPJSTR(obsIdStr);
        DUMPJSTR(instrument);     // %I
        DUMPJSTR(obsMode);
        DUMPJINT(expos);
        DUMPJSTR(creator);
        DUMPJSTR(origin);
        DUMPJSTR(procFunc);       // %F
        DUMPJSTR(fileType);
        DUMPJSTR(params);         // %P
        DUMPJSTR(productId);
        DUMPJSTR(productType);    // %T
        DUMPJSTR(productVersion); // %V
        DUMPJSTR(productStatus);
        DUMPJSTR(productSize);
        DUMPJSTR(signature);      // %S
        DUMPJSTR(dirName);
        DUMPJSTR(baseName);
        DUMPJSTR(suffix);
        DUMPJSTR(extension);
        DUMPJSTR(url);
        DUMPJSTR(urlSpace);
        DUMPJINT(procTargetType);
        DUMPJSTR(procTarget);
        DUMPJBOOL(hadNoVersion);
    }
    JSTR(mission);        // %M
    JSTR(startTime);      // %f
    JSTR(endTime);        // %t
    JSTR(regTime);
    JSTR(timeInterval);   // %D
    JINT(obsId);
    JSTR(obsIdStr);
    JSTR(instrument);     // %I
    JSTR(obsMode);
    JINT(expos);
    JSTR(creator);
    JSTR(origin);
    JSTR(procFunc);       // %F
    JSTR(fileType);
    JSTR(params);         // %P
    JSTR(productId);
    JSTR(productType);    // %T
    JSTR(productVersion); // %V
    JSTR(productStatus);
    JSTR(productSize);
    JSTR(signature);      // %S
    JSTR(dirName);
    JSTR(baseName);
    JSTR(suffix);
    JSTR(extension);
    JSTR(url);
    JSTR(urlSpace);
    JINT(procTargetType);
    JSTR(procTarget);
    JBOOL(hadNoVersion);
};

//typedef std::vector<ProductMetadata>           ProductList;
//typedef std::map<ProductType, ProductMetadata> ProductCollection;


struct ProductList : public JRecord {
    ProductList() {}
    ProductList(json v) : JRecord(v) {
        products.clear();
        for (int i = 0; i < value.size(); ++i) {
            products.push_back(ProductMetadata(value[i]));
        }
    }
    ProductMetadata at(int i) {
        return ProductMetadata(value[i]);
    }
    virtual void dump() {
        for (auto & v: products) { v.dump(); }
    }
    std::vector<ProductMetadata> products;
};

struct ProductCollection : public JRecord {
    ProductCollection() {}
    ProductCollection(json v) : JRecord(v) {
        products.clear();
        Json::Value::iterator it = value.begin();
        while (it != value.end()) {
            products[it.key().asString()] = ProductMetadata(*it);
            ++it;
        }
    }
    virtual void dump() {
        for (auto & kv: products) { kv.second.dump(); }
    }
    std::map<ProductType, ProductMetadata> products;
};

typedef std::string                            TaskName;
typedef std::string                            TaskPath;
typedef int                                    TaskExitCode;
typedef json                                   TaskData;

#define TLIST_TASK_STATUS                                       \
    T(SCHEDULED, -2),                                           \
    T(FAILED,    -1),                                           \
    T(FINISHED,   0),                                           \
    T(RUNNING,    1),                                           \
    T(PAUSED,     2),                                           \
    T(STOPPED,    3),                                           \
    T(ABORTED,    4),                                           \
    T(ARCHIVED,   5),                                           \
    T(UNKNOWN_STATE, 6)

#define T(a,b) TASK_ ## a = b
enum TaskStatus { TLIST_TASK_STATUS };
#undef T

extern std::map<TaskStatus, std::string> TaskStatusName;
extern std::map<std::string, TaskStatus> TaskStatusValue;

struct TaskInfo : public JRecord {
    TaskInfo() {}
    TaskInfo(json v) : JRecord(v) {
        SET_GRP(ProductList,inputs);
        SET_GRP(ProductList,outputs);
    }
    virtual void dump() {
        DUMPJSTR(taskName);
        DUMPJSTR(taskRule);
        DUMPJSTR(taskPath);
        DUMPJSTR(taskHost);
        DUMPJSTR(taskAgent);
        DUMPJSTR(taskStart);
        DUMPJSTR(taskEnd);
        DUMPJINT(taskExitCode);
        DUMPJINT(taskStatus);
        DUMPJINT(taskFlags);
        inputs.dump();
        outputs.dump();
        DUMPJSTRSTRMAP(params);
        DUMPJSTR(taskData);
        DUMPJSTR(taskSet);
        DUMPJSTR(taskSession);
    }
    JSTR(taskName);
    JSTR(taskRule);
    JSTR(taskPath);
    JSTR(taskHost);
    JSTR(taskAgent);
    JSTR(taskStart);
    JSTR(taskEnd);
    JINT(taskExitCode);
    JINT(taskStatus);
    JINT(taskFlags);
    GRP(ProductList,inputs);
    GRP(ProductList,outputs);
    JSTRSTRMAP(params);
    JSTR(taskData);
    JSTR(taskSet);
    JSTR(taskSession);
};

struct TaskAgentInfo : public JRecord {
    TaskAgentInfo() {}
    TaskAgentInfo(json v) : JRecord(v) {}
    virtual void restart() {
        value["total"]      = 0;
        value["maxnum"]     = 0;
        value["running"]    = 0;
        value["waiting"]    = 0;
        value["paused"]     = 0;
        value["stopped"]    = 0;
        value["failed"]     = 0;
        value["finished"]   = 0;
        value["uptimesecs"] = 0;
    }
    virtual void dump() {
        DUMPJINT(total);
        DUMPJINT(maxnum);
        DUMPJINT(running);
        DUMPJINT(waiting);
        DUMPJINT(paused);
        DUMPJINT(stopped);
        DUMPJINT(failed);
        DUMPJINT(finished);
        DUMPJINT(load1min);
        DUMPJINT(load5min);
        DUMPJINT(load15min);
        DUMPJINT(uptimesecs);
    }
    JSTR(name);
    JSTR(client);
    JSTR(server);
    JINT(total);
    JINT(maxnum);
    JINT(running);
    JINT(waiting);
    JINT(paused);
    JINT(stopped);
    JINT(failed);
    JINT(finished);
    JINT(load1min);
    JINT(load5min);
    JINT(load15min);
    JINT(uptimesecs);
};

struct TskStatSpectra {
    TskStatSpectra(int r, int s, int p, int st, int fl, int f) :
        running(r), scheduled(s), paused(p),
        stopped(st), failed(fl), finished(f),
        total(r+s+p+st+fl+f) {}
    int    running;
    int    scheduled;
    int    paused;
    int    stopped;
    int    failed;
    int    finished;
    int    total;
};

typedef std::vector<std::pair<std::string, TskStatSpectra>> TskStatTable;

int getTskStatSpecValueFromStatus(TskStatSpectra & tss, TaskStatus st);

//== Reprocessing flags and locations

enum Flags {
    NullFlags      = 0x00,
    GenIntermProd  = 0x01,
    OpenIPython    = 0x02,
    OpenJupyterLab = 0x04,
    OpenVOSpace    = 0x08,
};

enum OutputsLocation {
    LocalArch      = 0x100,
    LocalDir       = 0x200,
    VOSpaceFolder  = 0x400,
};        

// Simple definition of macro to avoid "Unused var." messages
#define UNUSED(x) (void)(x)

//}

#endif  /* DATATYPES_H */
