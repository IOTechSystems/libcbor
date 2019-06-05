#!/bin/sh
set -x -e
ARCH=$1
SYSTEM=$2
export VER=`cat scripts/VERSION`
ALPINE=""

build_dist()
{
  DIST=$1
  mkdir -p build/${DIST}
  docker build --tag libcbor-${DIST}:${VER} --file scripts/Dockerfile.${DIST} .
  docker run --rm -e UID=`id -u $USER` -e GID=`id -g $USER` -v "$(pwd)"/build/${DIST}:/build libcbor-${DIST}:${VER}
  docker rmi libcbor-${DIST}:${VER}
}

if [ "$SYSTEM" = "alpine-3.9" -o "$SYSTEM" = "all"  ]
then
  build_dist alpine-3.9
fi

