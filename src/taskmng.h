/******************************************************************************
 * File:    taskmng.h
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.libQPF.TaskManager
 *
 * Version: 1.0
 *
 * Date:    2015/07/01
 *
 * Copyright (C) 2015 J C Gonzalez
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

#ifndef TASKMNG_H
#define TASKMNG_H

//============================================================
// Group: External Dependencies
//============================================================

//------------------------------------------------------------
// Topic: System headers
//   none
//------------------------------------------------------------

//------------------------------------------------------------
// Topic: External packages
//   none
//------------------------------------------------------------

//------------------------------------------------------------
// Topic: Project headers
//   - component.h
//------------------------------------------------------------

#include "component.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
namespace QPF {

//==========================================================================
// Class: TaskManager
//==========================================================================
class TaskManager : public Component {

public:
    TaskManager(const char * name = 0);

    struct AgentInfo {
        int idx;
        int runningTasks;
        int failedTasks;
        int finishedTasks;
        int launchedTasks;
        int load;
    };

protected:

    //----------------------------------------------------------------------
    // Method: fromRunningToOperational
    //----------------------------------------------------------------------
    virtual void fromRunningToOperational();

    //----------------------------------------------------------------------
    // Method: fromRunningToOff
    //----------------------------------------------------------------------
    virtual void fromRunningToOff();

protected:

    //----------------------------------------------------------------------
    // Method: processTASK_PROC
    //----------------------------------------------------------------------
    virtual void processTASK_PROC();

    //----------------------------------------------------------------------
    // Method: processTASK_RES
    //----------------------------------------------------------------------
    virtual void processTASK_RES();

private:
    //----------------------------------------------------------------------
    // Method: run
    //----------------------------------------------------------------------
    void exeRule(Message_TASK_PROC * msg);

    //----------------------------------------------------------------------
    // Method: run
    //----------------------------------------------------------------------
    LibComm::Router2RouterPeer::Peer * selectAgent();

    //----------------------------------------------------------------------
    // Method: run
    //----------------------------------------------------------------------
    bool sendTaskAgMsg(Message_TASK_PROC * msg,
                       std::string agName);

    //----------------------------------------------------------------------
    // Method: run
    //----------------------------------------------------------------------
    bool sendTaskRes(Message_TASK_RES * msg);

private:
    std::vector<LibComm::Router2RouterPeer::Peer *> agents;
    std::map<LibComm::Router2RouterPeer::Peer *, AgentInfo> agentInfo;

};

}

#endif  /* TASKMNG_H */
