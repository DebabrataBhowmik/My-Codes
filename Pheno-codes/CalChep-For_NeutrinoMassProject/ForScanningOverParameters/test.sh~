#!/bin/bash

Lambda=$1

mnu=2
vev=100
ynu=10

a=10.0
b=20.0
c=30.0
d=40.0

#vs=$((a/b))
#vs=$(( (a*b) / (c*d) ))
echo $vs

div=`echo 2*$a*$c / $b | bc -l`

echo $div

#if [ $div -gt 10 ]
#then
 #   echo "div is greater than 10"
#fi

if (( $(echo "$div > 10.0" |bc -l) )); then
    echo "div is greater than 10"
fi

mchi=100.0
vs=10.0

ychi=`echo "sqrt(2)"* $mchi / $vs | bc -l`
echo $ychi

lams=`echo $mchi*$mchi / 2 / $vs / $vs | bc -l`
echo $lams
