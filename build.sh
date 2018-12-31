#!/bin/sh

set -e

BASE_IMAGE_REPO_URL=registry.gitlab.com/hetesiistvan/arduino-arduinoci/
USE_BASE_REMOTE_IMAGE=false

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
	BASE_IMAGE_TAG_PROPERTY=`read_build_property "BASE_IMAGE_TAG"`
	BASE_IMAGE_TAG=$BASE_IMAGE_TAG_PROPERTY

	# In case of CI build we always pull the needed image
	# But in case of local build we take the locally available image and don't pull that
	# unless the --remote-image command line parameter is specified
	if [ ! -z $CI_PROJECT_PATH ]; then
		echo "CI build, pulling remote image"
		USE_BASE_REMOTE_IMAGE=true

		BASE_IMAGE_TAG=${BASE_IMAGE_REPO_URL}${BASE_IMAGE_TAG_PROPERTY}

		# By CI build we tag the image with the build number
		LIBRARY_IMAGE_TAG=$CONTAINER_IMAGE_CI:`build_version`

		# Print the build ID - ATM only for investigation
		echo "Build ID: $CI_PIPELINE_IID"
	else {
		# Local build
		LIBRARY_IMAGE_TAG=arduinolibraries:latest
	}
	fi
	if [ "--remote-base-image" = "$2" ]; then
		echo "Local build using remote image"
		USE_BASE_REMOTE_IMAGE=true

		BASE_IMAGE_TAG=${BASE_IMAGE_REPO_URL}${BASE_IMAGE_TAG_PROPERTY}
	fi

	echo "Using base image: $BASE_IMAGE_TAG"
	echo "Using library image: $LIBRARY_IMAGE_TAG"
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

	docker pull $BASE_IMAGE_TAG

	if [ -z $CI_PROJECT_PATH ]; then
		docker logout
	fi
}

prepare_dockerfile() {
	sed -e s!@image@!$BASE_IMAGE_TAG! Dockerfile.template > Dockerfile
}

build_image() {
	calculate_image_tags $@
	prepare_base_image
	prepare_dockerfile

	docker build --tag ${LIBRARY_IMAGE_TAG} .
}

build_libraries() {
	calculate_image_tags $@

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
	calculate_image_tags $@
	echo "To be implemented"
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

usage() {
	echo "Usage:"
	echo "  build.sh build-image [--remote-library-image]"
	echo "  build.sh build-libraries"
	echo "  build.sh test-unit"
	echo "  build.sh build-version"
	echo "  build.sh push-version-tag"
	echo "  build.sh create-desktop-links"
}

case $1 in
	build-image)
		build_image $@
	;;
	build-libraries)
		build_libraries $@
	;;
	test-unit)
		test_unit $@
	;;
	build-version)
		build_version
	;;
	push-version-tag)
		push_version_tag
	;;
	create-desktop-links)
		create_desktop_links
	;;
	*)
		echo "Invalid parameter. Aborting!"
		usage
		exit 1
	;;
esac
