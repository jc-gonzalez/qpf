/******************************************************************************
 * File:    main.cpp
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.QPF.main
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
 *   
 *
 * Created by:
 *   J C Gonzalez
 *
 * Status:
 *   Prototype
 *
 * Dependencies:
 *   none
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

#include "app.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    App a(argc, argv);

    QPF::MainWindow w;
    w.show();

    return a.exec();
}
