#!/bin/sh

set -e

ARDUINO_IDE_VERSION=1.8.8

calculate_image_tags() {
	if [ -z $CI_PROJECT_PATH ]; then
		# Local build
		BUILD_IMAGE_TAG="arduinobuild:latest"
	else
		# Gitlab build
		BUILD_IMAGE_TAG="$CONTAINER_IMAGE/arduinobuild:$CI_COMMIT_SHA"

		# Print the build ID - ATM only for investigation
		echo "Build ID: $CI_PIPELINE_IID"
	fi
}

prepare_image_content() {
	echo "Preparing image content"
	IMAGE_DIR=build/image
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
	prepare_image_content

	docker build --tag ${BUILD_IMAGE_TAG} .
}

test_image() {
	mkdir -p build/test
	cp -f build-test.ino build/test/build-test.ino
	cp -f build-test-wrapper.sh build/test/build-test-wrapper.sh

	docker run --rm -v `pwd`/build/test:/build $BUILD_IMAGE_TAG ./build/build-test-wrapper.sh
}

usage() {
	echo "Usage:"
	echo "  build.sh build-image"
	echo "  build.sh test-image"
}

case $1 in
	build-image)
		calculate_image_tags $@
		build_image
	;;
	test-image)
		calculate_image_tags $@
		test_image
	;;
	*)
		echo "Invalid parameter given. Aborting!"
		usage
		exit 1
	;;
esac
