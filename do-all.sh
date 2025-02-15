#/bin/bash
BUILD_TYPE="Debug Release"
CONTAINER_TYPE="Host Alpine Ubuntu Debian Fedora"

for build in $BUILD_TYPE; do
  for container in $CONTAINER_TYPE; do
    if ./configure.sh $build $container && make && make test && make package; then
      echo "Build $build on $container succeeded"
    else
      echo "Build $build on $container failed"
      exit 1
    fi
  done
done