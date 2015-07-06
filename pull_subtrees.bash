#!/bin/bash
# Author: Wolfgang C. Strack
# This script pulls all subtrees that were merged into the current git
# repository using the merge_git_repo.bash script method of merging
# subtrees.

##### Initialize some stuff ##############################################
usageMessage="Usage: $0 # no args"
remoteNames=()

##### Functions ##########################################################
pullSubtrees ()
{
	echo
	for remote in ${remoteNames[@]}; do
		git pull --no-edit -s subtree $remote master
		echo
	done
}

##### Main ###############################################################
if [ $# -ne 0 ]; then
	echo $usageMessage
	exit 1
fi

remoteNames=($(git remote | grep -v origin))
pullSubtrees