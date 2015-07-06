#!/bin/bash
# Author: Wolfgang C. Strack
# This script adds a subtree in a subdirectory of the git repository that
# this script is run in.

##### Initialize some stuff ##############################################
usageMessage="Usage: $0 repo_name repo_remote_path"

##### Functions ##########################################################
addSubtree ()
{
	git remote add -f $1 $2 # add subtree remote shortcut
	git subtree --prefix $1 add $1 --squash
}

##### Main ###############################################################
if [ $# -ne 2 ]; then # check number of args
	echo $usageMessage
	exit 1
fi

if [ ! -d '.git' ]; then # check if current dir is a git repo
	echo "Error, current repository is not a git repository"
	exit 2
fi

addSubtree $@
