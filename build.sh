#!/bin/sh

BASE_IMAGE=registry.gitlab.com/hetesiistvan/arduino-arduinoci/arduinobuild:latest

pull_base_image() {
	if [ -z $CI_PROJECT_PATH ]; then
		# Started a local build
		if [ -z $GITLAB_REGISTRY_TOKEN ]; then
			GITLAB_REGISTRY_TOKEN=`cat gitlab_registry_token`
		fi
		DOCKER_USER=gitlab+deploy-token-33202
		DOCKER_PASSWD=${GITLAB_REGISTRY_TOKEN}

		docker login -u ${DOCKER_USER} -p ${DOCKER_PASSWD} registry.gitlab.com
	fi

	docker pull $BASE_IMAGE

	if [ ! -z $CI_PROJECT_PATH ]; then
		# In case of CI build we need to tag the pulled image in order to have a reference
		# what can be used with the Dockerfile
		tag_remote_image
	fi

	if [ -z $CI_PROJECT_PATH ]; then
		docker logout
	fi
}

tag_remote_image() {
	docker tag $BASE_IMAGE arduinobuild:latest
}

build_image() {
	pull_base_image

	# What a nice up-to-date check :)
	rm -rf build
	mkdir build
	cp -r CommandHandler build/
	cp -r Drivers build/
	cp -r FlowUtils build/
	cp -r Logger build/
	cp -r SerialInputHandler build/
	cp -r Utils build/

	if [ -z $CI_PROJECT_PATH ]; then
		# Local build
		CONTAINER_TAGS="arduinolibraries --tag arduinolibraries:latest"
	else
		# Gitlab build
		CONTAINER_TAGS="$CONTAINER_IMAGE/arduinolibraries:$CI_COMMIT_SHA"
	fi

	docker build --tag ${CONTAINER_TAGS} .
}

build_libraries() {
	echo "To be implemented"
}

test_unit() {
	echo "To be implemented"
}

case $1 in
	build-image)
		build_image
	;;
	build-libraries)
		build_libraries
	;;
	test-unit)
		test_unit
	;;
	tag-remote-image)
		tag_remote_image
	;;
	*)
		echo "Invalid parameter. Aborting!"
		exit 1
	;;
esac
