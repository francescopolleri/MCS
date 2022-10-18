#!/bin/bash
echo " " > fileInput
for pl in $*
do
    grep -A6 "// $pl" SolarSystData.h | grep -v "// $pl" >> fileInput
    echo " " >> fileInput
done
