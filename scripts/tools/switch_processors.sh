#!/bin/bash

act=$1

BINPATH=${HOME}/qpf/bin
CURDIR=$(pwd)

case $act in
    qdt)
        for i in VIS NISP; do
            qla=QLA_${i}_Processor
            cd ${BINPATH}/${qla}
            ln -sf ../QDT/driver.py .
            for j in common config tools HKTM_qla NISP_qla VIS_qla ; do
                ln -sf ../QDT/$j .
            done
            #
            le1=LE1_${i}_Processor
            cd ${BINPATH}/${le1}
            ln -sf convert${i}2QLA.py driver.py
            ln -sf sample-${i}-emu.cfg.json sample.cfg.json
        done
        ;;
    qdtfake)
        for i in VIS NISP; do
            qla=QLA_${i}_Processor
            cd ${BINPATH}/${qla}
            ln -sf driver-${i}-fake.py driver.py
            #
            le1=LE1_${i}_Processor
            cd ${BINPATH}/${le1}
            ln -sf driver-${i}-fake.py driver.py
            ln -sf sample-${i}-fake.cfg.json sample.cfg.json
        done
        ;;
    *)
        ;;
esac

cd ${CURDIR}

