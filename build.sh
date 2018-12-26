#!/bin/sh

build_image() {
	if [ -z $CI_PROJECT_PATH ]; then
		# Local build
		BUILD_IMAGE_TAG="arduinobuild:latest"
	else
		# Gitlab build
		BUILD_IMAGE_TAG="$CONTAINER_IMAGE/arduinobuild:$CI_COMMIT_SHA"
	fi

	docker build --tag ${BUILD_IMAGE_TAG} .
}

test_image() {
	if [ -z $CI_PROJECT_PATH ]; then
		# Local test
		BUILD_IMAGE_TAG="arduinobuild:latest"
	else
		# Gitlab test
		BUILD_IMAGE_TAG="$CONTAINER_IMAGE/arduinobuild:$CI_COMMIT_SHA"
	fi

	mkdir -p build
	cp -f build-test.ino build/build-test.ino
	cp -f build-test-wrapper.sh build/build-test-wrapper.sh

	docker run --rm -v `pwd`/build:/build $BUILD_IMAGE_TAG ./build/build-test-wrapper.sh
}

case $1 in
	build-image)
		build_image
	;;
	test-image)
		test_image
	;;
	*)
		echo "Invalid parameter given. Aborting!"
		exit 1
	;;
esac
