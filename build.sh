#!/bin/sh

if [ -z $CI_PROJECT_PATH ]; then
	# Local build
	CONTAINER_TAGS="arduinobuild"
else
	# Gitlab build
	CONTAINER_TAGS="--tag $CONTAINER_IMAGE/arduinobuild:$CI_COMMIT_SHA --tag $CONTAINER_IMAGE/arduinobuild:latest"
fi

case $1 in
	build_image)
		docker build --tag ${CONTAINER_TAGS} .
	;;
	*)
		echo "Invalid parameter given. Aborting!"
		exit 1
	;;
esac
