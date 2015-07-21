# src
This repository contains the development of the src directory of  CMSSW_7_0_4 for the timing detector of the CT-PPS project. To have the codes please do the following:

cmsrel CMSSW_7_0_4

cd src

cmsenv

cd ../

git clone https://github.com/MyEtesami/src.git

Then you have to compile the codes from src directory by

cd src/

scramv1 b -j 8
