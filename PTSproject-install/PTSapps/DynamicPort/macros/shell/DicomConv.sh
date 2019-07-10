#!/bin/bash -l
#
#  Syntax  DicomConv.sh <PatientID>  <PlanID>  <BeamID> 
#
#---
##OUTPUTROOT=${beamDir}/aaa.root
##OUTREFDOSE=${beamDir}/refdose.dat
##GRIDDATAOUT=${beamDir}/grid.dat
#---
baseDir=`printenv DICOM_DATA_DIR`
if [ -z "${baseDir}" ]; then
   baseDir=/Users/Montecarlo
fi
#
convExecDir=${baseDir}/${PATIENTID}/${PLANID}/${BEAMID}
tmpRawDATA=raw.data
#
cd ${convExecDir}
pwd
TH3ToRTDose.exe ${OUTPUTROOT} ${tmpRawDATA} 
#
######
chmod u+x dcmPix.sh
./dcmPix.sh
######
exit
