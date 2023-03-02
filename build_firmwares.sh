#!/bin/bash

echo "############################################"
echo "#### Updating submodules                ####"
echo -e "############################################\n"
make git-submodule >/dev/null 2>&1

echo "############################################"
echo "#### Building IBM 5140 firmware         ####"
echo "############################################"
make clean >/dev/null 2>&1
echo "#    Building default firmware             #"
if ! make converter/ibm_5140:default 1>/dev/null;
then
  exit 1
fi
make clean >/dev/null 2>&1
echo "#    Building custom firmware              #"
if ! make converter/ibm_5140:razerban 1>/dev/null;
then
  exit 1
fi
make clean >/dev/null 2>&1
echo "#    Building VIA firmware                 #"
if ! make converter/ibm_5140:via 1>/dev/null;
then
  exit 1
fi
echo -e "############################################\n"

echo "############################################"
echo "#### Building IBM Pingmaster firmware   ####"
echo "############################################"
make clean >/dev/null 2>&1
echo "#    Building default firmware             #"
if ! make converter/ibm_pingmaster:default 1>/dev/null;
then
  exit 1
fi
make clean >/dev/null 2>&1
echo "#    Building custom firmware              #"
if ! make converter/ibm_pingmaster:razerban 1>/dev/null;
then
  exit 1
fi
echo -e "############################################\n"

echo "############################################"
echo "#### Building C.ITOH firmware           ####"
echo "############################################"
make clean >/dev/null 2>&1
echo "#    Building default firmware             #"
if ! make converter/citoh:default 1>/dev/null;
then
  exit 1
fi
make clean >/dev/null 2>&1
echo "#    Building VIA firmware                 #"
if ! make converter/citoh:via 1>/dev/null;
then
  exit 1
fi
echo -e "############################################\n"

echo "############################################"
echo "#### Building Andromeda firmware        ####"
echo "############################################"
make clean >/dev/null 2>&1
echo "#    Building default firmware             #"
if ! make razerban/andromeda:default 1>/dev/null;
then
  exit 1
fi
make clean >/dev/null 2>&1
echo "#    Building VIA firmware                 #"
if ! make razerban/andromeda:via 1>/dev/null;
then
  exit 1
fi
echo -e "############################################\n"

make clean >/dev/null 2>&1
