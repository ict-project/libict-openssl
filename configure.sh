#!/bin/bash
###################
HOST_USER_ID=$(id -u)
HOST_GROUP_ID=$(id -g)
SCRIPT_DIR="$(dirname $(pwd)/$0)"
BUILD_TYPE="Release"
CONTAINER_TYPE="Host"
CONTAINER_ENABLED="false"
CONTAINER_FILE=""
RUN_PREFIX=""
###################
case $1 in
  d* | D* )
    BUILD_TYPE="Debug"
    ;;
  *)
    ;;
esac
echo "BUILD_TYPE=$BUILD_TYPE" 
###################
case $2 in
  a* | A* )
    CONTAINER_TYPE="alpine:build-base"
    CONTAINER_ENABLED="true"
    CONTAINER_FILE="libict-dev-tools/Dockerfile.alpine.latest"
    ;;
  u* | U* )
    CONTAINER_TYPE="ubuntu:build-essential"
    CONTAINER_ENABLED="true"
    CONTAINER_FILE="libict-dev-tools/Dockerfile.ubuntu.latest"
    ;;
  d* | D* )
    CONTAINER_TYPE="debian:build-essential"
    CONTAINER_ENABLED="true"
    CONTAINER_FILE="libict-dev-tools/Dockerfile.debian.latest"
    ;;
  f* | F* )
    CONTAINER_TYPE="fedora:build-base"
    CONTAINER_ENABLED="true"
    CONTAINER_FILE="libict-dev-tools/Dockerfile.fedora.latest"
    ;;
  *)
    ;;
esac
echo "CONTAINER_TYPE=$CONTAINER_TYPE"
###################
if ! command -v make &> /dev/null
then
    echo "make could not be found!"
    exit 1
fi
if ! command -v cmake &> /dev/null
then
    echo "cmake could not be found!"
    exit 2
fi
if ! command -v git &> /dev/null
then
    echo "git could not be found!"
    exit 3
fi
if $CONTAINER_ENABLED ; then
  if ! command -v docker &> /dev/null
  then
      echo "docker could not be found!"
      exit 4
  fi
fi
###################
if $CONTAINER_ENABLED ; then
  RUN_PREFIX="docker run --rm -v $SCRIPT_DIR:/project -v $SCRIPT_DIR/build:/project/build -w /project $CONTAINER_TYPE "
  docker build --build-arg USER_ID=$HOST_USER_ID --build-arg GROUP_ID=$HOST_GROUP_ID -t $CONTAINER_TYPE -f $CONTAINER_FILE .
fi
echo "RUN_PREFIX=$RUN_PREFIX"
###################
if ! $RUN_PREFIX git submodule foreach 'git submodule init && git submodule update' ; then
  echo "git submodule foreach git submodule update failed! ($?)" 
  exit 11
fi
if ! $RUN_PREFIX git submodule foreach 'test -f configure.sh && ./configure.sh || echo ok' ; then
  echo "git submodule foreach configure.sh failed! ($?)" 
  exit 12
fi
if ! $RUN_PREFIX git submodule foreach 'test -f Makefile && make || echo ok' ; then
  echo "git submodule foreach make failed! ($?)" 
  exit 13
fi
###################
cd "$SCRIPT_DIR"
pwd
rm -Rf build
mkdir build
BUILD_PREFIX_SH="build/prefix.sh"
echo "#!/bin/bash" >> $BUILD_PREFIX_SH
echo "exec $RUN_PREFIX \$@" >> $BUILD_PREFIX_SH
chmod +x $BUILD_PREFIX_SH
###################
CMAKE_COMMAND="cmake -S ./source -B ./build"
if $CONTAINER_ENABLED ; then
  case $CONTAINER_TYPE in
    alpine* )
      $RUN_PREFIX $CMAKE_COMMAND -DCMAKE_EXPORT_COMPILE_COMMANDS=YES -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCPACK_GENERATOR="TZ;TGZ;STGZ;DEB"
      ;;
    ubuntu* )
      $RUN_PREFIX $CMAKE_COMMAND -DCMAKE_EXPORT_COMPILE_COMMANDS=YES -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCPACK_GENERATOR="TZ;TGZ;STGZ;DEB;RPM"
      ;;
    debian* )
      $RUN_PREFIX $CMAKE_COMMAND -DCMAKE_EXPORT_COMPILE_COMMANDS=YES -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCPACK_GENERATOR="TZ;TGZ;STGZ;DEB;RPM"
      ;;
    fedora* )
      $RUN_PREFIX $CMAKE_COMMAND -DCMAKE_EXPORT_COMPILE_COMMANDS=YES -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCPACK_GENERATOR="TZ;TGZ;STGZ;DEB;RPM"
      ;;
    *)
      echo "Unknown CONTAINER_TYPE ($CONTAINER_TYPE)!"
      exit 21
      ;;
  esac
else
  case $OSTYPE in
    linux* )
      $CMAKE_COMMAND -DCMAKE_EXPORT_COMPILE_COMMANDS=YES -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCPACK_GENERATOR="TZ;TGZ;STGZ;DEB;RPM"
      ;;
    darwin* )
      $CMAKE_COMMAND -DCPACK_GENERATOR="TZ;TGZ;STGZ" -G Xcode -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake
      # xcodebuild -project *.xcodeproj | xcpretty -r json-compilation-database --output compile_commands.json
      echo "# In order to open project run:"
      echo "open build/*.xcodeproj"
      ;;
    *)
      echo "Unknown OSTYPE ($OSTYPE)!"
      exit 22
      ;;
  esac
  BUILD_MAKEFILE="./build/Makefile"
  if [[ ! -r $BUILD_MAKEFILE ]]; then
    echo > $BUILD_MAKEFILE

    echo "default_target:" >> $BUILD_MAKEFILE
    printf "\tcmake --build . --config $BUILD_TYPE \n\n" >> $BUILD_MAKEFILE

    echo "clean:" >> $BUILD_MAKEFILE
    printf "\tcmake --build . --config $BUILD_TYPE --target  clean\n\n" >> $BUILD_MAKEFILE

    echo "install:" >> $BUILD_MAKEFILE
    printf "\tcmake --build . --config $BUILD_TYPE --target  install\n\n" >> $BUILD_MAKEFILE

    echo "uninstall:" >> $BUILD_MAKEFILE
    printf "\tcmake --build . --config $BUILD_TYPE --target  uninstall\n\n" >> $BUILD_MAKEFILE

    echo "test:" >> $BUILD_MAKEFILE
    printf "\tctest -C $BUILD_TYPE\n\n" >> $BUILD_MAKEFILE

    echo "package:" >> $BUILD_MAKEFILE
    printf "\tcpack -C $BUILD_TYPE\n\n" >> $BUILD_MAKEFILE

    echo "package_source:" >> $BUILD_MAKEFILE
    printf "\tcpack -C $BUILD_TYPE --config CPackSourceConfig.cmake\n\n" >> $BUILD_MAKEFILE
  fi
fi
###################
test -r build/compile_commands.json && test -r compile_commands.json || ln -s build/compile_commands.json
###################
echo "# In order to make project run:"
echo "make"
echo "# In order to test project run:"
echo "make test"
###################