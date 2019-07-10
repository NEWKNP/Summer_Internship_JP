#!/bin/bash
#####
#
##$ bsub -q s -J 'ptsim[1-100]' -o "stdout.%J.%I" -e "stderr.%J.%I" \
#                 ./LSBExec.sh  Sample1Grid.mac  1000
#                              (macorofile)     (Number of Beam).   
#
#     where
#         -q  <queue>
#         -J  <Job name[task numbers]>
#         -o  stdout file name  (%J is a job number, %I is an index number)
#         -e  stderr file name
#
#   $ bqueues 　list of batch queues
#   $ lshosts   list of host nodes
#   $ lsinfo    information
#   $ lsload    load status
#   $ bjobs     list of current working jobs
#   $ bstatus -J <Job name>
#   $ bkill   -J <Jobs name>
#  
####################
#  Execution
#---
export  MY_JOB_ID=${LS_JOBPID}
export  MY_TASK_ID=${LSB_JOBINDEX}
#
export NBEAM=$2
#
/usr/bin/time ./bin/$G4SYSTEM/PTSdemo $1
#
####################
