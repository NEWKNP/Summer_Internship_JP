#!/bin/sh
#
#  Syntax  MergeGDDFile <StartNum>  <EndNum>
#
STARTNUM=$1
ENDNUM=$2
NSLOT=`expr $ENDNUM - $STARTNUM`
NSLOT=`expr $NSLOT + 1`
#
#
numa=${STARTNUM}
echo "Merge dose.gdd_${STARTNUM}"
cp  aaa.gdd_${STARTNUM} merge.gdd

numa=`expr $numa + 1`
while [ ${numa} -ne ${NSLOT} ]
do
   cp merge.gdd tmp.gdd
   rm merge.gdd 
   mergegdd -i1  tmp.gdd -i2 dose.gdd_${numa} -o merge.gdd 
   numa=`expr $numa + 1` 
   echo "Merge dose.gdd_${numa}"
done

exit 0
