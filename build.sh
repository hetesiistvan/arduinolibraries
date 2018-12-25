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
		tag_remote_base_image
	fi

	if [ -z $CI_PROJECT_PATH ]; then
		docker logout
	fi
}

tag_remote_base_image() {
	docker tag $BASE_IMAGE arduinobuild:latest
}

build_image() {
	pull_base_image

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
	if [ -z $CI_PROJECT_PATH ]; then
		# Local build
		LIBRARY_IMAGE_TAG=arduinolibraries:latest
	else
		# CI build
		LIBRARY_IMAGE_TAG=$CONTAINER_IMAGE/arduinolibraries:$CI_COMMIT_SHA
	fi

	mkdir -p build
	find src -name '*.h' -exec basename {} \; | awk '{ print "#include <" $1 ">" }' > build/build-test.ino
	cat << EOF >> build/build-test.ino

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
EOF

	cp -f build-libraries-wrapper.sh build/build-libraries-wrapper.sh

	docker run --rm -v `pwd`/build:/build-test $LIBRARY_IMAGE_TAG ./build-test/build-libraries-wrapper.sh
}

test_unit() {
	echo "To be implemented"
}

create_desktop_links() {
	if [ -z $CI_PROJECT_PATH ]; then
		# This is only available in local development environment
		ARDUINO_HOME_DIRECTORY=~/Arduino/libraries

		cd src
		for DIR_NAME in `ls -1 .`; do
			echo "Creating link for directory: $DIR_NAME"
			[ -L $ARDUINO_HOME_DIRECTORY/$DIR_NAME ] && rm $ARDUINO_HOME_DIRECTORY/$DIR_NAME
			ln -s `pwd`/$DIR_NAME $ARDUINO_HOME_DIRECTORY/$DIR_NAME
		done
	else
		echo "Not supported for CI but only for local development environment."
	fi
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
	tag-remote-base-image)
		tag_remote_base_image
	;;
	create-desktop-links)
		create_desktop_links
	;;
	*)
		echo "Invalid parameter. Aborting!"
		exit 1
	;;
esac
