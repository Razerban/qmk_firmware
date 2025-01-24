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
if ! qmk compile -kb converter/ibm_5140 -km default 1>/dev/null;
then
  exit 1
fi
make clean >/dev/null 2>&1
echo "#    Building custom firmware              #"
if ! qmk compile -kb converter/ibm_5140 -km razerban 1>/dev/null;
then
  exit 1
fi
make clean >/dev/null 2>&1
echo "#    Building VIA firmware                 #"
if ! qmk compile -kb converter/ibm_5140 -km via 1>/dev/null;
then
  exit 1
fi
echo -e "############################################\n"

echo "############################################"
echo "#### Building IBM Pingmaster firmware   ####"
echo "############################################"
make clean >/dev/null 2>&1
echo "#    Building default firmware             #"
if ! qmk compile -kb converter/ibm_pingmaster -km default 1>/dev/null;
then
  exit 1
fi
make clean >/dev/null 2>&1
echo "#    Building custom firmware              #"
if ! qmk compile -kb converter/ibm_pingmaster -km razerban 1>/dev/null;
then
  exit 1
fi
echo -e "############################################\n"

echo "############################################"
echo "#### Building C.ITOH firmware           ####"
echo "############################################"
make clean >/dev/null 2>&1
echo "#    Building default firmware             #"
if ! qmk compile -kb converter/citoh -km default 1>/dev/null;
then
  exit 1
fi
make clean >/dev/null 2>&1
echo "#    Building VIA firmware                 #"
if ! qmk compile -kb converter/citoh -km via 1>/dev/null;
then
  exit 1
fi
echo -e "############################################\n"

echo "############################################"
echo "#### Building Andromeda firmware        ####"
echo "############################################"
make clean >/dev/null 2>&1
echo "#    Building default firmware             #"
if ! qmk compile -kb razerban/andromeda -km default 1>/dev/null;
then
  exit 1
fi
make clean >/dev/null 2>&1
echo "#    Building VIA firmware                 #"
if ! qmk compile -kb razerban/andromeda -km via 1>/dev/null;
then
  exit 1
fi
echo -e "############################################\n"

make clean >/dev/null 2>&1
