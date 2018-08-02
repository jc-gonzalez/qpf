/******************************************************************************
 * File:    productsmodel.cpp
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.libQPF.productsmodel
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
 *   Provides object implementation for some declarations
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

#include "productsmodel.h"
#include <iostream>
namespace QPF {

ProductsModel::ProductsModel(std::vector<std::string> & pTypes, 
                             int siz)
{
    stringWithProductTypes = "";
    for (auto & s: pTypes) {
        std::string ss(s + "                                ");
        stringWithProductTypes += ss.substr(0, siz);
    }
    singleProdTypeLen = siz;

    defineQuery(QString::fromStdString(
                "SELECT  "
                "    left(p.signature, 7) AS ObsId_Exp,  "
                "    concat(left(p.signature, 7), '.', "
                "                cast(position(cast(p.instrument_id as char) "
		        "                              in ' VNS') as char), '.', "
                "                to_char(position(p.product_type in '" + 
                stringWithProductTypes + "') / " + 
                std::to_string(singleProdTypeLen) + ", 'FM00MI'), '.', "
                "                p.product_version) as idx, "
                "    p.product_id as ID,  "
                "    p.product_type as Type,  "
                "    p.product_version as Version,  "
                "    p.product_size as Size,  "
                "    p.product_status_id as Status,  "
                "    p.creator_id as Creator,  "
                "    p.obsmode_id as ObsMode,  "
                "    p.start_time as Start,  "
                "    p.end_time as End,  "
                "    p.registration_time as RegTime,  "
                "    p.url as URL, "
                "    p.id as internal_id "
                "FROM products_info p  "
                "@WHERE@ "
                "ORDER BY idx;"
		));

    defineHeaders({"Signature", "Idx",
                   "Product Id", "Type", "Version",
                   "Size", "Status", "Creator", "Obs.Mode",
                   "Start", "End", "Reg.Time", "URL", "IntID"});

   // skipColumns(1);

    refresh();
}

}
