/******************************************************************************
 * File:    dbtreemodel.cpp
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.libQPF.dbtreemodel
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

#include "dbtreemodel.h"
#include <iostream>
#include "dbmng.h"
#include <QDebug>

namespace QPF {

DBTreeBoldHeaderDelegate::DBTreeBoldHeaderDelegate(QObject *parent)
    : QStyledItemDelegate(parent),
      isCustomFilter(false)
{
}

void DBTreeBoldHeaderDelegate::setCustomFilter(bool b)
{
    isCustomFilter = b;
}


void DBTreeBoldHeaderDelegate::paint(QPainter* painter,
                                     const QStyleOptionViewItem& option,
                                     const QModelIndex& index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    if (!isCustomFilter) {
        bool shouldBeBold = (! index.parent().isValid());
        opt.font.setBold(shouldBeBold);
    }
    QStyledItemDelegate::paint(painter, opt, index);
}

DBTreeModel::DBTreeModel(QString q, QStringList hdr) :
    queryString(q),
    headerLabels(hdr),
    rowsFromQuery(-1),
    lastRetrievedId(0),
    skippedColumns(-1),
    boldHeader(false),
    initialSkippedColumns(-1),
    getGroupId([](QSqlQuery & q){return q.value(0).toString();}),
    isCustomFilter(false)
{
    refresh();
}

void DBTreeModel::setHeaders(QStringList & hdr)
{
    int i = 0;
    for (QString & s: hdr) {
        setHeaderData(i, Qt::Horizontal, s);
        ++i;
    }
}

void DBTreeModel::defineHeaders(QStringList hdr)
{
    headerLabels = hdr;
    if (initialHeaders.size() < 1) { initialHeaders = hdr; }
}

void DBTreeModel::defineQuery(QString q)
{
    queryString = q;
    if (initialQuery.isEmpty()) { initialQuery = q; }
}

void DBTreeModel::setBoldHeader(bool b)
{
}

void DBTreeModel::setCustomFilter(bool b)
{
    isCustomFilter = b;
}

void DBTreeModel::restart()
{
    defineQuery(initialQuery);
    defineHeaders(initialHeaders);
    skipColumns(initialSkippedColumns);
    refresh();
}

void DBTreeModel::skipColumns(int n)
{
    if (initialSkippedColumns < 0) {
        initialSkippedColumns = n;
    }
    skippedColumns = n;
}

void DBTreeModel::refresh()
{
    if (! queryString.isEmpty()) {
        QString qryStr(queryString);
        if (lastRetrievedId > 0) { 
            qryStr.replace("@WHERE@", QString(" WHERE p.id > %1").arg(lastRetrievedId));  
        } else {
            qryStr.replace("@WHERE@", "");
        }
        std::cerr << qryStr.toStdString() << '\n';
        execQuery(qryStr, DBManager::getDB());
    }
}

void traverse(QAbstractItemModel* model, QModelIndex parent = QModelIndex()) 
{
	for (int r = 0; r < model->rowCount(parent); ++r) {
		QModelIndex index = model->index(r, 0, parent);
		QVariant name = model->data(index);
		std::cerr << name.toString().toStdString() << '\n';
		// here is your applicable code
		if (model->hasChildren(index)) { traverse(model, index); }
	}

}

void DBTreeModel::execQuery(QString & qry, QSqlDatabase & db)
{
    // Perform query
    QSqlQuery q(qry, db);
    QSqlRecord rec = q.record();
    
    int numOfRecordsRetrieved = q.size();
    if (numOfRecordsRetrieved < 1) { return; }
    
    int fldCount = rec.count();

    std::cerr << "Num. of records retrieved: " << numOfRecordsRetrieved << '\n';
    
    //if ((q.size() == rowsFromQuery) && (!isCustomFilter)) { return; }

    //clear();

    if (headerLabels.count() < 1) {
        for (int i = 0; i < rec.count(); ++i) {
            headerLabels << rec.fieldName(i);
        }
    }

/*
    if (isCustomFilter) {
        while (q.next()) {
            row.clear();
            for (int i = 0; i < fldCount; ++i) {
                row << new QStandardItem(q.value(i).toString());
            }
            root->appendRow(row);
            rowsFromQuery++;
        }
        setHeaders(headerLabels);
        return;
    }
*/  

    // Create root item
    QStandardItem * root = invisibleRootItem();
    QStandardItem * parent;
    QModelIndex rootIdx;
    QModelIndex parentIdx;

    QList<QStandardItem *> rowItems;
    
    QString prevGrpName("");
    int numOfParentRows = rowCount(rootIdx);
    int grp = 0;
    int chld = 0;

    rowsFromQuery = 0;
    uint internal_id;

    // Loop over all the results from the query
    while (q.next()) {
        
        QString id = q.value(0).toString();
        
        internal_id = q.value(fldCount - 1).toUInt();
        if (internal_id > lastRetrievedId) {
            lastRetrievedId = internal_id;
            std::cerr << "Last retrieved ID set to " << lastRetrievedId << '\n';
        }
        
        // Iterate on root items looking for id
        for (grp = 0; grp < numOfParentRows; ++grp) {
            QModelIndex grpIdx = index(grp, 0, rootIdx);
            QString grpId = data(grpIdx).toString();
            if (grpId == id) {
                // Add new child to parent found
                parent = itemFromIndex(grpIdx);
                for (int i = 0; i < fldCount; ++i) { rowItems << new QStandardItem(q.value(i).toString()); }
                    
                chld = rowCount(grpIdx);
                
                beginInsertRows(grpIdx, chld, chld);
                parent->appendRow(rowItems);
                endInsertRows();
                
                rowItems.clear();
                std::cerr << "Appending additional child '" << q.value(0).toString().toStdString() << "'\n";
                break;
            }
        }
        if (grp == numOfParentRows) {
            // Final encountered, exit this loop
            q.previous();
            break;
        }
    }
    
    // Loop over rest of the results from the query
    while (q.next()) {
        
        QString grpName = q.value(0).toString();
        internal_id = q.value(fldCount - 1).toUInt();
        if (internal_id > lastRetrievedId) {
            lastRetrievedId = internal_id;
            std::cerr << "Last retrieved ID set to " << lastRetrievedId << '\n';
        }

        // Is it the in same group in the results
        if (prevGrpName != grpName) {
            // NO: A new group must be created in the model 
            parent = new QStandardItem(grpName);
            parent->setFlags(parent->flags() & ~Qt::ItemIsSelectable);
            rowItems << parent;
            for (int i = 1; i < fldCount; ++i) rowItems << 0; 
            parentIdx = indexFromItem(parent);
            std::cerr << "Appending new parent '" << grpName.toStdString() << "'\n";
                
            beginInsertRows(rootIdx, grp, grp);
            root->appendRow(rowItems);
            endInsertRows();

            rowItems.clear();
            prevGrpName = grpName;
            ++grp;
            chld = 0;
        }

        for (int i = 0; i < fldCount; ++i) { rowItems << new QStandardItem(q.value(i).toString()); }
        std::cerr << "Appending new child '" << q.value(0).toString().toStdString() << "'\n";
        
        beginInsertRows(parentIdx, chld, chld);
        parent->appendRow(rowItems);
        endInsertRows();

        rowItems.clear();
        ++chld;
    }
    
    // Finally, add headers if needed
    setHeaders(headerLabels);
}

}


