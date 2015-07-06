#!/bin/bash
# Author: Wolfgang C. Strack
# This script pulls all subtrees that were merged into the current git
# repository and is coupled with the 'add_subtree.bash' script.

##### Initialize some stuff ##############################################
usageMessage="Usage: $0 # no args"
remoteNames=()

##### Functions ##########################################################
pullSubtrees ()
{
	echo

	for remote in ${remoteNames[@]}; do # for each subtree
		git fetch $remote master
		git subtree --prefix $remote pull $remote master --squash
		
		echo;echo

		if [[ $? != 0 ]]; then
			"Pull failed"
			exit 2;
		fi
		
		git add -A # resolve merge conflicts
		git commit
		
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