#!/bin/bash
##############################################################################
# File       : GenreateCoveragePages.sh - Generate LCOV pages
# Domain     : QPF.scripts
# Version    : 2.0
# Date       : 2017/09/08
# Copyright (C) 2015-2018 J C Gonzalez
#_____________________________________________________________________________
# Purpose    : Drops and recreate qpfdb database
# Created by : J C Gonzalez
# Status     : Prototype
# History    : See <Changelog>
###############################################################################

###### Script variables

#- This script path and name
SCRIPT_PATH="${BASH_SOURCE[0]}";
SCRIPT_NAME=$(basename "${SCRIPT_PATH}")
if [ -h "${SCRIPT_PATH}" ]; then
    while [ -h "${SCRIPT_PATH}" ]; do
        SCRIPT_PATH=$(readlink "${SCRIPT_PATH}")
    done
fi
pushd . > /dev/null
cd $(dirname ${SCRIPT_PATH}) > /dev/null
SCRIPT_PATH=$(pwd)
popd  > /dev/null

# Move to root
curdir=$(pwd)
cd ${SCRIPT_PATH}/..

# Gather test info
./build/tests/unitTestsSet --gtest_color=yes
lcov --directory build --capture --output-file lcov.info
lcov --remove lcov.info \
        '/usr/include/*' \
        '*/mongoose/*' \
        '*/tests/*' \
        '*/gtest/*' \
        '*/nanomsg/*' \
        '*/jsoncpp*' \
        '*json.h' \
        -o lcov-filtered.info
 
# Generate web pages
genhtml lcov-filtered.info -s -f --legend --demangle-cpp --title "QPF UTs - LCov Coverage Report" --output-directory lcov

# Open firefox
firefox lcov/index.html &

# End
cd ${curdir}
