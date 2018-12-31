#!/bin/sh

if [ "${SSH_DEPLOY_PRIVATE_KEY}a" = "a" ]
then
	echo "SSH private key is not available. Aborting!"
	exit 1
fi

eval $(ssh-agent -s)

echo -e $SSH_DEPLOY_PRIVATE_KEY | ssh-add -