#! /bin/bash
##############################################################################
# File       : ClearForQPF.sh - Cleans up db, data folders and old sessions
# Domain     : QPF.scripts
# Version    : 2.0
# Date       : 2016/12/02
# Copyright (C) 2015-2018 J C Gonzalez
#_____________________________________________________________________________
# Purpose    : Clean old data
# Created by : J C Gonzalez
# Status     : Prototype
# History    : See <Changelog>
###############################################################################

## Clear database
echo "Cleaning up database . . ."
cat <<EOF>/tmp/clean-up-qpfdb.sql
delete from products_info where id>0;
delete from transmissions where id>0;
delete from tasks_info where id>0;
delete from icommands;
delete from alerts;
delete from qpfstates;
delete from task_status_spectra;
EOF

psql -f /tmp/clean-up-qpfdb.sql qpfdb

## Clear archive and inbox
echo "Cleaning up data folders . . ."

pths=""
pths="$pths qpf/data/archive"
pths="$pths qpf/data/gateway"
pths="$pths qpf/data/gateway/in"
pths="$pths qpf/data/gateway/out"
pths="$pths qpf/data/inbox"

size=0
for p in $pths ; do
    sz=$(du -ks $HOME/${p} | cut -f 1)
    rm -rf $HOME/${p}/EUC*
    size=$(($size + $sz))
done

## Remove old run folders
echo "Removing old sessions . . ."
sess=$(ls -d $HOME/qpf/run/20* 2>/dev/null)
for p in $sess ; do
    sz=$(du -ks ${p} | cut -f 1)
    rm -rf ${p}
    size=$(($size + $sz))
done

echo "$size kB recovered."
