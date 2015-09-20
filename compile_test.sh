#! /bin/bash
set -e
#This script will attempt to compile with C++11, cross compile to windows with C++11, cross compile to windows with C++03, compile with C++03
make clean
make TESTCPP11=1
make clean
make CROSS=i686-pc-mingw32- TESTCPP11=1
make clean
make CROSS=i686-pc-mingw32-
mv platform_folders.out platform_folders.exe
make clean
make
