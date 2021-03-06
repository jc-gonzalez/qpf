#======================================================================
# CMakeLists.txt
# QPF - Prototype of QLA Processing Framework
# General Project File
#======================================================================
# Author: J C Gonzalez - 2015-2018
# Copyright (C) 2015-2018 Euclid SOC Team at ESAC
#======================================================================
include (../../common.cmake)

#===== Projec dir. =======
project (jsontest)

set (jsontest_src
  main.cpp
)

add_executable(jsontest ${jsontest_src})
target_include_directories (jsontest PUBLIC .
  ${NNMSG_ROOT_DIR}/include
  ${NNCOMM_ROOT_DIR}
  ${FMK_ROOT_DIR}
  ${JSON_ROOT_DIR}
  ${LOG_ROOT_DIR}
  ${STR_ROOT_DIR}
  ${UUID_ROOT_DIR}
  ${INFIX_ROOT_DIR}
  ${PSQLLIBDIR})
target_link_libraries (jsontest
  fmk json nncomm infix str log uuidxx
  nanomsg
  ${UUIDLIB} ${PSQLLIB}
  pthread)
set_target_properties (jsontest PROPERTIES LINKER_LANGUAGE CXX)
install (TARGETS jsontest
         RUNTIME DESTINATION bin
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib)
