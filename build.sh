#!/bin/sh

set -e

ARDUINO_IDE_VERSION=1.8.8

read_build_property() {
	awk -F '=' "/$1/{ print \$2 }" build.properties
}

build_version() {
	if [ -z $CI_PROJECT_PATH ]; then
		# Local build - This function is intended to be used only with CI build
		echo "-"
		return
	else
		BUILD_VERSION_BASE=`read_build_property "BUILD_VERSION_BASE"`
		BUILD_VERSION=${BUILD_VERSION_BASE}.${CI_PIPELINE_IID}
		echo $BUILD_VERSION
	fi
}

calculate_image_tags() {
	if [ -z $CI_PROJECT_PATH ]; then
		# Local build
		BUILD_IMAGE_TAG="arduinobuild:latest"
	else
		# Gitlab build
		BUILD_IMAGE_TAG=$CONTAINER_IMAGE_CI:`build_version`

		# Print the build ID - ATM only for investigation
		echo "Build ID: $CI_PIPELINE_IID"
	fi

	echo "Build image tag: $BUILD_IMAGE_TAG"
}

prepare_image_content() {
	echo "Preparing image content"
	IMAGE_DIR=build/image
	rm -rf $IMAGE_DIR
	mkdir -p $IMAGE_DIR/opt/arduino-libraries
	mkdir -p $IMAGE_DIR/opt/arduino-utils

	cp -f buildsketch.sh $IMAGE_DIR/opt/arduino-utils/

	echo "Downloading Arduino IDE"
	wget https://www.arduino.cc/download.php?f=/arduino-${ARDUINO_IDE_VERSION}-linux64.tar.xz -q -O arduino-${ARDUINO_IDE_VERSION}-linux64.tar.xz

	xzcat arduino-${ARDUINO_IDE_VERSION}-linux64.tar.xz | tar xf -
	rm arduino-${ARDUINO_IDE_VERSION}-linux64.tar.xz
	mv arduino-${ARDUINO_IDE_VERSION} $IMAGE_DIR/opt/arduino-ide
}

build_image() {
	calculate_image_tags $@
	prepare_image_content

	docker build --tag ${BUILD_IMAGE_TAG} .
}

test_image() {
	calculate_image_tags $@
	mkdir -p build/test
	cp -f build-test.ino build/test/build-test.ino
	cp -f build-test-wrapper.sh build/test/build-test-wrapper.sh

	docker run --rm -v `pwd`/build/test:/build $BUILD_IMAGE_TAG ./build/build-test-wrapper.sh
}

push_version_tag() {
	if [ ! -z $CI_PROJECT_PATH ]; then
		# This can be used only in CI environment

		# Setting up SSH parameters
		source /setup-ssh-key.sh

		VERSION_TAG=`build_version`
		ALREADY_TAGGED=`git tag | grep $VERSION_TAG | wc -l`

		if [ $ALREADY_TAGGED -eq 1 ]; then
			echo "The branch has already the version tag."
			exit 1
		fi

		git remote add gitlab git@gitlab.com:hetesiistvan/arduino-arduinolibraries
		git tag $VERSION_TAG
		git push gitlab $VERSION_TAG
	else
		echo "Not supported in local development environment."
	fi
}

usage() {
	echo "Usage:"
	echo "  build.sh build-image"
	echo "  build.sh test-image"
	echo "  build.sh build-version"
	echo "  build.sh push-version-tag"
}

case $1 in
	build-image)
		build_image $@
	;;
	test-image)
		test_image $@
	;;
	build-version)
		build_version
	;;
	push-version-tag)
		push_version_tag
	;;
	*)
		echo "Invalid parameter given. Aborting!"
		usage
		exit 1
	;;
esac
