#!/bin/sh

echo "[Bootstraping in current directory]"

echo Calling aclocal
aclocal

echo Calling autoconf
autoconf

echo Calling automake
automake
echo ""

# If we don't have any parameters then don't
# do a recursive bootstrap
if [ $# -eq 0 ]
then
   exit 0
fi

echo "[Booststraping in lib directory]"
cd lib
./bootstrap.sh
cd ..
echo ""

echo "[Booststraping in simple directory]"
cd simple
./bootstrap.sh
cd ..
echo ""

