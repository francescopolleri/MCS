#!/bin/bash
echo " " > fileInput

for cost in AU RADS RADM RADE
do
   grep "DOUBLE $cost" effemeridi.h | awk '{print $4}' >> fileInput
done

echo " " >> fileInput

for pl in Sun Mercury Venus Earth Moon Mars Jupiter Saturn Uranus Neptune Pluto
do
    grep "/\* $pl" effemeridi.h | awk '{print $1}' >>fileInput
    grep -A6 "// $pl" effemeridi.h | grep -v "// $pl" >> fileInput
    echo " " >> fileInput
done

