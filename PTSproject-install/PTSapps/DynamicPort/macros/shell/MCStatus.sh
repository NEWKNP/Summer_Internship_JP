#!/bin/bash
#
#  Syntax  MCCheck  <PatientID> <PlanID> <BeamID>
####################
PATIENTID=$1
PLANID=$2
BEAMID=$3
##
PROCESS=PTSdemo
###################
nAlive=`ps -ef | grep "$PROCESS" | grep -v grep | wc -l`
echo $nAlive
#






