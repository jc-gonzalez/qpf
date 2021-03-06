/******************************************************************************
 * File:    taskmng.h
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.libQPF.TaskManager
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
 *   Declare TaskManager class
 *
 * Created by:
 *   J C Gonzalez
 *
 * Status:
 *   Prototype
 *
 * Dependencies:
 *   Component
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

#ifndef TSKMNG_H
#define TSKMNG_H

//============================================================
// Group: External Dependencies
//============================================================

//------------------------------------------------------------
// Topic: System headers
//   - list
//------------------------------------------------------------
#include <list>
#include <thread>
#include <mutex>

//------------------------------------------------------------
// Topic: External packages
//   none
//------------------------------------------------------------

//------------------------------------------------------------
// Topic: Project headers
//   - component.h
//   - tools.h
//   - message.h
//------------------------------------------------------------
#include "component.h"
#include "tools.h"
#include "message.h"
#include "httpserver.h"
#include "hostinfo.h"
#include "procinfo.h"

//==========================================================================
// Class: TaskManager
//==========================================================================
class TskMng : public Component {

public:
    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
    TskMng(const char * name, const char * addr = 0, Synchronizer * s = 0);

    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
    TskMng(std::string name, std::string addr = std::string(), Synchronizer * s = 0);

public:
    //----------------------------------------------------------------------
    // Method: initializeTaskStatusSpectra
    // Initialize status per agent from initial values in DB
    //----------------------------------------------------------------------
    void initializeTaskStatusSpectra(TskStatTable & tssSet);
    
    //----------------------------------------------------------------------
    // Method: runReachIteration
    //----------------------------------------------------------------------
    virtual void runEachIteration();

    //----------------------------------------------------------------------
    // Method: scheduleTask
    // Schedule task for later provision to the requesting agents
    //----------------------------------------------------------------------
    void scheduleTask(TaskInfo & task);
    
    //----------------------------------------------------------------------
    // Method: getTskMsgUpdate
    // Provide an update on the Task Report information
    //----------------------------------------------------------------------
    bool getTskRepUpdate(json & tskRepData);

    //----------------------------------------------------------------------
    // Method: getProcFmkInfoUpdate
    // Provide an update on the ProcessingFrameworkInfo structure
    //----------------------------------------------------------------------
    void getProcFmkInfoUpdate(json & fmkInfoValue);

    //----------------------------------------------------------------------
    // Method: getRunningTasks
    // Get messages from tasks that are still running
    //----------------------------------------------------------------------
    void getRunningTasks(std::map<std::string, MessageString> & tasks);

protected:
    //----------------------------------------------------------------------
    // Method: fromRunningToOperational
    //----------------------------------------------------------------------
    void fromRunningToOperational();

protected:
    //----------------------------------------------------------------------
    // Method: processTskRqstMsg
    //----------------------------------------------------------------------
    void processTskRqstMsg(ScalabilityProtocolRole* c, MessageString & m);

    //----------------------------------------------------------------------
    // Method: processTskRepMsg
    //----------------------------------------------------------------------
    void processTskRepMsg(ScalabilityProtocolRole* c, MessageString & m);

    //----------------------------------------------------------------------
    // Method: processHostMonMsg
    //----------------------------------------------------------------------
    void processHostMonMsg(ScalabilityProtocolRole* c, MessageString & m);


private:
    //----------------------------------------------------------------------
    // Method: execTask
    // Execute the rule requested by Task Orchestrator
    //----------------------------------------------------------------------
    void execContainerTask();

    //----------------------------------------------------------------------
    // Method: selectAgent
    //----------------------------------------------------------------------
    std::string selectAgent();

    //----------------------------------------------------------------------
    // Method: consolidateMonitInfo
    // Consolidates the monitoring info retrieved from the processing hosts
    //----------------------------------------------------------------------
    void consolidateMonitInfo(MessageString & m);

    //----------------------------------------------------------------------
    // Method: convertTaskStatusToSpectra
    // Convert set of status for an agent to a spectra tuple
    //----------------------------------------------------------------------
    TaskStatusSpectra convertTaskStatusToSpectra(std::string & agName);

    //----------------------------------------------------------------------
    // Method: sendTaskAgMsg
    //----------------------------------------------------------------------
    bool sendTaskAgMsg(MessageString & m,
                       std::string agName);

private:
    typedef std::pair<std::string, TaskStatus>  TaskStatusPerAgent;
    std::vector<std::string>         agents;
    std::map<std::string, AgentInfo> agentInfo;

    std::list<TaskInfo> serviceTasks;
    std::list<TaskInfo> containerTasks;

    typedef std::map<std::string, TaskInfo>  RuleTagInputs;

    std::vector<std::string> rqstAgents;

    std::map<std::string, TaskStatus> taskRegistry;

    std::map<TaskStatus, int> containerTaskStatus;
    std::map<TaskStatus, int> serviceTaskStatus;

    std::map<TaskStatusPerAgent, int> containerTaskStatusPerAgent;
    std::map<std::string, MessageString> containerTaskLastMessage;

    HttpServer * httpSrv;

    std::mutex mtxHostInfo;

    bool sendingPeriodicFmkInfo;

    std::mutex mtxTskRegMsg;

    bool sendingTskRegInfo;
    std::map<std::string, std::string> tskRegMsgs;
};

#endif // TSKMNG_H
