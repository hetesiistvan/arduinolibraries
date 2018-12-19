#!/bin/bash

BASE_IMAGE=registry.gitlab.com/hetesiistvan/arduino-arduinoci/arduinobuild:latest

pull_base_image() {
	if [ ! -z $CI_PROJECT_PATH ]; then
		# Build started from Gitlab, taking the credential from there
		DOCKER_USER=gitlab-ci-token
		DOCKER_PASSWD=${CI_JOB_TOKEN}
	else
		# Started a local build
		if [ -z $GITLAB_REGISTRY_TOKEN ]; then
			GITLAB_REGISTRY_TOKEN=`cat gitlab_registry_token`
		fi
		DOCKER_USER=gitlab+deploy-token-33202
		DOCKER_PASSWD=${GITLAB_REGISTRY_TOKEN}
	fi
	docker login -u ${DOCKER_USER} -p ${DOCKER_PASSWD} registry.gitlab.com

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
