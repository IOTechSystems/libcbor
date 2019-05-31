#!/bin/sh
set -x -e
sed -e 's/-flto//' -i CMakeLists.txt
cmake -DCMAKE_BUILD_TYPE=Release -DCBOR_CUSTOM_ALLOC=ON .
make
make package
cp *.tar.gz /build/.
chown -R $UID:$GID /build
