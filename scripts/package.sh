#!/bin/sh
set -x -e
ARCH=$1
TYPE=$2
IMAGE_ARCH=$ARCH
export VER=`cat scripts/VERSION`

build_apk()
{
  DIST=$1
  mkdir -p apk/${DIST}
  cp build/${DIST}/libcbor-${VER}-Linux.tar.gz apk/${DIST}/.
  cp scripts/APKBUILD apk/${DIST}/.
  cp scripts/VERSION apk/${DIST}/.
  if [ "$ARCH" = "aarch64" ]
  then
    IMAGE_ARCH="arm64"
  elif [ "$ARCH" = "armhf" ]
  then
    IMAGE_ARCH="arm"
  fi
  docker pull docker.iotechsys.com/services/iotech-apk-builder-${IMAGE_ARCH}:0.2.0
  docker run --rm -e UID=`id -u ${USER}` -e GID=`id -g ${USER}` -v "$(pwd)"/apk/${DIST}:/home/packager/build docker.iotechsys.com/services/iotech-apk-builder-${IMAGE_ARCH}:0.2.0
  docker rmi docker.iotechsys.com/services/iotech-apk-builder-${IMAGE_ARCH}:0.2.0
}

if [ "$TYPE" = "alpine-3.8" -o "$TYPE" = "all"  ]
then
  build_apk alpine-3.8
fi

if [ "$TYPE" = "alpine-3.9" -o "$TYPE" = "all"  ]
then
  build_apk alpine-3.9
fi