#!/bin/bash

BASE_IMAGE=registry.gitlab.com/hetesiistvan/arduino-arduinoci/arduinobuild:latest

pull_base_image() {
	if [ -z $GITLAB_REGISTRY_TOKEN ]; then
		GITLAB_REGISTRY_TOKEN=`cat gitlab_registry_token`
	fi
	docker login -u gitlab+deploy-token-33202 -p ${GITLAB_REGISTRY_TOKEN} registry.gitlab.com
	docker pull $BASE_IMAGE
	docker logout
}

build_image() {
	pull_base_image
}

case $1 in
	build)
		build_image
	;;
	*)
		echo "Invalid parameter. Aborting!"
		exit 1
	;;
esac
