#$ -S /bin/bash -cwd
#####
#
##$ qsub -N 'ptsim' -o "stdout.%J.%I" -e "stderr.%J.%I" \
#                 ./SGEExec.sh 
#
#     where
#         -N  <Job name>
#         -o  stdout file path (Directory)
#         -e  stderr file path (Directory)
#
#
#   $ qconf -sel         list of host nodes
#   $ qconf -ss          submit host nodes info
#   $ qconf -se <host>  host nodes info
#   $ qhost      host information
#   $ qstat     list of current working jobs ( $ watch qstat )
#   $ qdel   <JOBID>
#  
####################
#  Execution
#---
#
export NBEAM=1000
export MY_JOB_ID=${JOB_ID}
export MY_TASK_ID=${SGE_TASK_ID}
#
/usr/bin/time ./bin/$G4SYSTEM/PTSdemo Sample1Grid.mac
#
####################
