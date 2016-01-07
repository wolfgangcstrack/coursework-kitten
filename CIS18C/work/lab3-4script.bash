#!/bin/bash
# Wolfgang C. Strack
# CIS18C
# This script is for lab3-4 and copies old files from
# a source directory into a destination directory.
echo "This script copies old files from a source directory to a destination directory."
echo

read -p "Please enter a source directory or hit enter to use current directory: " temp
source=${temp:-'./'}

while [ ! -d $source ] # keep prompting until a valid directory is entered
do
	echo "$source is not a directory"
	read -p "Please enter a source directory or hit enter to use current directory: " temp
	source=${temp:-'.'}
done

echo

read -p "Please enter the destination directory or hit enter to use the directory name \"old\": " temp
destination=${temp:-'./old'}

if [ -d $destination ] # use existing directory or make a new one
then
	echo Using existing directory $destination
else
	mkdir $destination
	echo Using new directory $destination
fi

echo

read -p "In the format mo/dd/yyyy hh:mm, please enter the day and time: " day vtime
epochtime=`date -d "$day $vtime" +%s`
echo

filecount=0
totalfiles=`ls $source | wc -l`
for file in `ls $source` # putting just $source does not seem to iterate through the files
do
	filetime=`stat -c %Y $file`
	if (( filetime < epochtime )) # if file is older than the time given
	then
		echo "Copying $file into $destination"
		cp -r $file $destination
		(( filecount++ ))
	fi
done

echo

(( percent = filecount * 100 / totalfiles ))
echo "$filecount files copied out of $totalfiles: $percent%"

# echo "Files in source directory:"
# ls $source

# read -p "Please choose a file: " filechosen
# stat -c "Epoch time for $filechosen: +%Y seconds" $filechosen

# echo "Copying $filechosen into $destination"
# cp $filechosen $destination