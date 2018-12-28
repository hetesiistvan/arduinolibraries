#!/bin/sh

set -e

BASE_REMOTE_IMAGE=registry.gitlab.com/hetesiistvan/arduino-arduinoci/arduinobuild:latest
USE_BASE_REMOTE_IMAGE=false

select_image_source() {
	# In case of CI build we always pull the needed image
	# But in case of local build we take the locally available image and don't pull that
	# unless the --remote-image command line parameter is specified
	if [ ! -z $CI_PROJECT_PATH ]; then
		echo "CI build, pulling remote image"
		USE_BASE_REMOTE_IMAGE=true
	fi
	if [ "--remote-base-image" = "$2" ]; then
		echo "Local build using remote image"
		USE_BASE_REMOTE_IMAGE=true
	fi
}

prepare_base_image() {
	if [ $USE_BASE_REMOTE_IMAGE = "true" ]; then
		pull_base_image
	else
		echo "Using local image"
	fi
}

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

	docker pull $BASE_REMOTE_IMAGE

	if [ -z $CI_PROJECT_PATH ]; then
		docker logout
	fi
}

prepare_dockerfile() {
	if [ $USE_BASE_REMOTE_IMAGE = "true" ]; then
		BASE_IMAGE_TAG=$BASE_REMOTE_IMAGE
	else
		BASE_IMAGE_TAG=arduinobuild:latest
	fi

	sed -e s!@image@!$BASE_IMAGE_TAG! Dockerfile.template > Dockerfile
}

build_image() {
	prepare_base_image
	prepare_dockerfile

	if [ -z $CI_PROJECT_PATH ]; then
		# Local build
		LIBRARY_IMAGE_TAG="arduinolibraries:latest"
	else
		# Gitlab build
		LIBRARY_IMAGE_TAG="$CONTAINER_IMAGE/arduinolibraries:$CI_COMMIT_SHA"
	fi

	docker build --tag ${LIBRARY_IMAGE_TAG} .
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
		case `uname -s` in
			Linux)
				ARDUINO_HOME_DIRECTORY=~/Arduino/libraries
			;;
			Darwin)
				ARDUINO_HOME_DIRECTORY=~/Documents/Arduino/libraries
			;;
			*)
				echo "Not supported OS version. Aborting!"
				exit 1
			;;
		esac

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

select_image_source $@

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
	create-desktop-links)
		create_desktop_links
	;;
	*)
		echo "Invalid parameter. Aborting!"
		exit 1
	;;
esac
