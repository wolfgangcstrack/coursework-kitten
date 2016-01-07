#!/bin/bash
# by Wolfgang C. Strack
# lab1-2 Module 2: bash shell script
# 19 April 2015
read -p "Please enter the filename: " filename
labdir=/home/distribution/cnguyen/cis18c/labs/Strack_WolfgangC_7355
cp $filename $labdir
echo "$filename has been copied to $labdir"
chmod 707 $labdir/$filename
stat --printf "Access: (%a/%A)\nChange: %z\n" $labdir/$filename
