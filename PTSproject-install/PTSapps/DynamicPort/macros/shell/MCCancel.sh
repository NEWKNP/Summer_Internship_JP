#!/bin/bash
#
#  Syntax  MCCancel  <PatientID> <PlanID> <BeamID>
####################
PATIENTID=$1
PLANID=$2
BEAMID=$3
##
PROCESS=PTSdemo
###################
killall  $PROCESS
