#!/bin/bash
#
#  Syntax  DicomSetEnv  <PatientID>  <PlanID>  <BeamID>  <NBEAM> 
#
####################
PATIENTID=$1
PLANID=$2
BEAMID=$3
BEAMON=$4
#
baseDir=`printenv DICOM_DATA_DIR`
if [ -z "${baseDir}" ]; then
   baseDir=/Users/Montecarlo
fi
#
# Check data directory
#
if [ ! -d ${baseDir}/${PATIENTID} ]; then
   echo "NO PATIENT ID DIRECTORY"
   echo ${baseDir}/${PATIENTID}
   return 0
fi
if [ ! -d ${baseDir}/${PATIENTID}/${PLANID} ]; then
   echo "NO PLAN ID DIRECTORY"
   echo ${baseDir}/${PATIENTID}/${PLANID}
   return 0
fi
if [ ! -d ${baseDir}/${PATIENTID}/${PLANID}/${BEAMID} ]; then
   echo "NO BEAM ID DIRECTORY"
   echo ${baseDir}/${PATIENTID}/${PLANID}/${BEAMID}
   return 0
fi
####
patientDir=${baseDir}/${PATIENTID}
planDir=${baseDir}/${PATIENTID}/${PLANID}
beamDir=${baseDir}/${PATIENTID}/${PLANID}/${BEAMID}
####
#
export PATIENTID
export PLANID
export BEAMID
export BEAMON
export DICOMDATA=${patientDir}/DICOM.dat
export DICOMWELDATA=${patientDir}/CT2WEL.dat
export DICOMRTPDATA=${planDir}/RTPlan.dat
export DICOMRTSDATA=${planDir}/RTS.dat
##
export OUTPUTROOT=${beamDir}/aaa.root
export OUTPUTGDD=${beamDir}/aaa.gdd
export OUTREFDOSE=${beamDir}/refdose.dat
export EVMONFILE=${beamDir}/evmon.out
export MLCDATAOUT=${beamDir}/mlc.dat
export BOLUSDATAOUT=${beamDir}/bolus.dat
export PTCDATAOUT=${beamDir}/ptc.dat
export GRIDDATAOUT=${beamDir}/grid.dat
####export RTDOSESHOUT=${beamDir}/rtdose.sh
export IAEAFILE=${beamDir}/IAEAphsp
#
#######
printenv DICOMRTPDATA
printenv DICOMDATA
printenv OUTPUTROOT
printenv BEAMON
#

