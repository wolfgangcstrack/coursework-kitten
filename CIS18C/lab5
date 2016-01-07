#!/bin/bash
# Author: Wolfgang C. Strack
# CIS18C Lab5-6 module 5 script
usage="Usage: $0 [-v] sourceDir [destinationDir]"

if [ $# -lt 1 ]; then # less than 1 or greater than 2 args
	echo $usage
	exit 1
fi

# read the command line options
while getopts v temp; do
	shift
	case $temp in
		v)
			option=$temp
			;;
		*)
			echo $usage
			exit 1
	esac
done

#read the command line arguments
sourceDir=$1;shift
destinationDir=$1;shift

# if there are more arguments, print usage message and exit
if [ $# -gt 0 ]; then
	echo $usage
	exit 1
fi

argFlag=1
# check if sourceDir is valid directory
if [ ! -d "$sourceDir" ]; then
	echo $sourceDir not a directory
	argFlag=0
fi
# check if destinationDir is valid directory
if [ ! -z "$destinationDir" -a ! -d "$destinationDir" ]; then
		echo $destinationDir not a directory
		argFlag=0
fi
# if either was an invalid directory, exit
if (( argFlag == 0 )); then
	exit 2
fi

# get name of new tar file to be created
date=`date +%Y-%m-%d`
tarfile="$sourceDir$date.tgz"

# set destinationDir if it isn't null
destinationDir=${destinationDir:-'.'}

# finally, call the tar command with the appropriate options/arguments
if [ "$option" == 'v' ]; then
	tar -vczf $destinationDir/$tarfile $sourceDir
else
	tar -czf $destinationDir/$tarfile $sourceDir
fi

exit 0