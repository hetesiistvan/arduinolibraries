#!/bin/sh

build_image() {
	if [ -z $CI_PROJECT_PATH ]; then
		# Local build
		CONTAINER_TAGS="arduinobuild"
	else
		# Gitlab build
		CONTAINER_TAGS="$CONTAINER_IMAGE/arduinobuild:$CI_COMMIT_SHA --tag $CONTAINER_IMAGE/arduinobuild:latest"
	fi

	docker build --tag ${CONTAINER_TAGS} .
}

test_image() {
	if [ -z $CI_PROJECT_PATH ]; then
		# Local test
		CONTAINER_TAG="arduinobuild"
	else
		# Gitlab test
		CONTAINER_TAG="$CONTAINER_IMAGE/arduinobuild:$CI_COMMIT_SHA"
	fi
	echo "To be implemented"
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
