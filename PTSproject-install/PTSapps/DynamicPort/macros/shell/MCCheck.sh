#!/bin/bash
#
#  Syntax  MCCheck  <PatientID> <PlanID> <BeamID> <FILENAME> <FLGPERC>
####################
PATIENTID=$1
PLANID=$2
BEAMID=$3
if [ $# -gt 3 ]; then
 FILENAME=$4
else
 FILENAME=evmon.out
fi
if [ $# -gt 4 ]; then
 FLGPERC=$5;
else
 FLGPERC=0;
fi
#
##################
baseDir=`printenv DICOM_DATA_DIR`
if [ -z "${baseDir}" ]; then
   baseDir=/Users/Montecarlo
fi
beamFile=${baseDir}/${PATIENTID}/${PLANID}/${BEAMID}/${FILENAME}
###################
LINE=`cat $beamFile`
set -- $LINE
if [ $FLGPERC -eq 1 ]; then
  EVNO100=`expr $1 \* 100`
  PERC=`expr $EVNO100 / $2`
  echo ${PERC}
else 
  echo $1
fi






