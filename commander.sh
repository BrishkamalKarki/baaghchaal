#!/usr/bin/env bash

# ./commander.sh or ./commander.ps1 -D for debug mode
# ./commander.sh -R for the release mode
# -C at last for the initial build file setup

# DEFAULT - DEBUG MODE
BUILD_DIR="build_ln"
SUB_BUILD_DIR="build_release"


if [ "$1" = "-R" ]; then
  if [ "$2" = "-C" ] || [ "$1" = "-C" ]; then
    cmake --preset release-linux
    cp -t "$BUILD_DIR/build_debug/" "$PWD/libraries/x64-linux/lib"/*.a   
    echo -e "\e[34mre-builded dude\e[0m"
  fi
  cmake --build "$BUILD_DIR/$SUB_BUILD_DIR"
  echo -e "\e[36me-compiled the code dude"
  echo -e "\e[32mrunning in release mode in linux\e[0m"
  ./build_ln/build_release/BaaghChaal
else
  SUB_BUILD_DIR="build_debug"
  if [ "$2" = "-C" ] || [ "$1" = "-C" ]; then
    cmake --preset debug-linux
    cp -t "$BUILD_DIR/build_debug/" "$PWD/libraries/x64-linux/lib"/*.a     
    echo -e "\e[34mre-builded dude\e[0m"
  fi
  cmake --build "$BUILD_DIR/$SUB_BUILD_DIR"
  echo -e "\e[36mre-compiled the code dude"
  echo -e "\e[32mrunning in debug mode in linux\e[0m"
  ./build_ln/build_debug/BaaghChaal
fi