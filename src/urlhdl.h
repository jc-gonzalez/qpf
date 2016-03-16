/******************************************************************************
 * File:    urlhdl.h
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.libQPF.URLHandler
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
 *   Declare URLHandler class
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

#ifndef URLHANDLER_H
#define URLHANDLER_H

//============================================================
// Group: External Dependencies
//============================================================

//------------------------------------------------------------
// Topic: System headers
//   none
//------------------------------------------------------------

//------------------------------------------------------------
// Topic: External packages
//  - propref.h
//------------------------------------------------------------
#include "propdef.h"

//------------------------------------------------------------
// Topic: Project headers
//   - cfg.h
//   - datatypes.h
//------------------------------------------------------------
#include "datatypes.h"
#include "cfginfo.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
namespace QPF {

//==========================================================================
// Class: URLHandler
//==========================================================================
class URLHandler {

public:
    URLHandler();

    PropertyRef(URLHandler, ProductMetadata, product, Product);

public:

    //----------------------------------------------------------------------
    // Method: fromExternal2Inbox
    //----------------------------------------------------------------------
    ProductMetadata & fromExternal2Inbox();

    //----------------------------------------------------------------------
    // Method: fromOutbox2External
    //----------------------------------------------------------------------
    ProductMetadata & fromOutbox2External();

    //----------------------------------------------------------------------
    // Method: fromFolder2Inbox
    //----------------------------------------------------------------------
    ProductMetadata & fromFolder2Inbox();

    //----------------------------------------------------------------------
    // Method: fromInbox2Local
    //----------------------------------------------------------------------
    ProductMetadata & fromInbox2LocalArch();

    //----------------------------------------------------------------------
    // Method: fromLocal2Gateway
    //----------------------------------------------------------------------
    ProductMetadata & fromLocalArch2Gateway();

     //----------------------------------------------------------------------
    // Method: fromGateway2Processing
    //----------------------------------------------------------------------
    ProductMetadata & fromGateway2Processing();

    //----------------------------------------------------------------------
    // Method: fromProcessing2Gateway
    //----------------------------------------------------------------------
    ProductMetadata & fromProcessing2Gateway();

     //----------------------------------------------------------------------
    // Method: fromGateway2Local
    //----------------------------------------------------------------------
    ProductMetadata & fromGateway2LocalArch();

    //----------------------------------------------------------------------
    // Method: relocate
    //----------------------------------------------------------------------
    int relocate(std::string & sFrom, std::string & sTo,
                 LocalArchiveMethod method = LINK, int msTimeOut = 0);

    //----------------------------------------------------------------------
    // Method: copyfile
    //----------------------------------------------------------------------
    int copyfile(std::string & sFrom, std::string & sTo);

    //----------------------------------------------------------------------
    // Method: rcopyfile
    //----------------------------------------------------------------------
    int rcopyfile(std::string & sFrom, std::string & sTo);

    //----------------------------------------------------------------------
    // Method: needsRemoteProcessing
    //----------------------------------------------------------------------
    bool needsRemoteProcessing();

    //----------------------------------------------------------------------
    // Method: setProcElemRunDir
    //----------------------------------------------------------------------
    void setProcElemRunDir(std::string wkDir, std::string tskDir);

private:
    std::string workDir;
    std::string intTaskDir;
    std::string taskExchgDir;
};

}

#endif  /* URLHANDLER_H */
