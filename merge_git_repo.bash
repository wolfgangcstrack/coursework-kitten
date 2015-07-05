#!/bin/bash
# Author: Wolfgang C. Strack
# This script takes arguments for a repository to merge to the current repository that this script
# is in. I decided to automate this task since I do it frequently when merging other repositories
# to coursework-kitten, which is intended to hold all git repositories of code from the courses I
# have taken in the past.

##### Initialize some stuff ##############################################
usageMessage="Usage: $0 repo_name repo_remote_path"
hideDir=".HIDE_ALL_FILES"

##### Functions ##########################################################
checkArgs () # takes the $@ variable as an argument
{
	if [ $# -ne 2 ]; then
		echo $usageMessage
		exit 1
	fi
}

hideFiles ()
{
	mkdir $hideDir
	mv -t $hideDir * .* 2> /dev/null
}

unhideFiles ()
{
	mv -t ./ $hideDir/* $hideDir/.* 2> /dev/null
	rmdir $hideDir
	ls -alF --color=tty
}

mergeRepo ()
{
	git remote add $1 $2
	git fetch $1
	git merge $1/master
}

moveRepoToDir ()
{
	mkdir $1
	for file in $(ls -a); do
		if [ "$file" != "$hideDir" ]; then
			mv -t $1/ $file
		fi
	done
}

##### Main ###############################################################
checkArgs $@
hideFiles # hides files in current directory to ensure no files are overwritten
mergeRepo $@
moveRepoToDir $1
unhideFiles
