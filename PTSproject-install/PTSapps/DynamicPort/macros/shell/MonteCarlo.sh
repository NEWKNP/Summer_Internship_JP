#!/bin/bash -l
#
#  Syntax  MonteCarlo  <PatientID>  <PlanID>  <BeamID>  <NBEAM>
#
####################
# WORKING DIRECTORY
#----
##
ptsimExecPath=`printenv PTSIM_EXEC_PATH`
if [ -z "${ptsimExecPath}" ]; then
  ptsimExecPath=/Users/aso/work/PTSproject-install/PTSapps/DynamicPort
fi
####################
cd ${ptsimExecPath}
####################
# SETUP PARAMETERS
#---
##
. ./DicomUnsetEnv.sh
. ./DicomSetEnv.sh $1 $2 $3 $4
#
####################
#  Execution
#---
./bin/PTSdemo DicomExec.mac
#
# PTSIM status
if [ "$?" -ne 0 ]; then
 exit
fi
#---
#
./DicomConv.sh
#
echo FINISH
#
exit 0
