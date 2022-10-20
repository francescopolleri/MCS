#!/bin/bash
echo " " > fileInput1
for pl in $*
do
    grep "// $pl" SolarSysData.h | awk '{print $2}' >> fileInput1
    grep "/\* $pl" SolarSysData.h | awk '{print $1}' >> fileInput1
    grep -A6 "// $pl" SolarSysData.h | grep -v "// $pl" >> fileInput1
    echo " " >> fileInput1
done

