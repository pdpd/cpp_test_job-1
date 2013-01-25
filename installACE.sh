#!/bin/bash
FILE=ACE-6.1.7.tar.gz
PWD=`pwd`
ACE_ROOT=$PWD/ACE_wrappers
INSTALL_PREFIX=/usr/local
LD_LIBRARY_PATH=$ACE_ROOT/lib:$LD_LIBRARY_PATH
export ACE_ROOT
export LD_LIBRARY_PATH
export INSTALL_PREFIX


wget http://download.dre.vanderbilt.edu/previous_versions/$FILE -O $FILE
tar -xvf $FILE

echo '#include "ace/config-linux.h"' >$ACE_ROOT/ace/config.h
echo 'include $(ACE_ROOT)/include/makeinclude/platform_linux.GNU' > $ACE_ROOT/include/makeinclude/platform_macros.GNU
cd $ACE_ROOT
make
make install
make clean
cd $PWD

