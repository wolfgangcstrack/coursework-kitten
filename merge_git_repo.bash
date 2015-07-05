#!/bin/bash
# Author: Wolfgang C. Strack
# This script merges a git repository as a subdirectory of the current git
# repository that the script is in

##### Initialize some stuff ##############################################
usageMessage="Usage: $0 repo_name repo_remote_path"

##### Functions ##########################################################
mergeRepo ()
{
	git remote add -f $1 $2
	git merge -s ours --no-commit $1/master
	git read-tree --prefix=$1/ -u $1/master
	git commit -m "Merge git repo '$1' into subdirectory '$1/'"
}

##### Main ###############################################################
if [ $# -ne 2 ]; then # check number of args
	echo $usageMessage
	exit 1
fi

if [ ! -d '.git' ]; then # check if current dir is a git repo
	echo "Error, current repository is not a git repository."
	exit 2
fi

mergeRepo $@
