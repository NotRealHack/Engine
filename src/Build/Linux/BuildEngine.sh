#!/bin/bash

set -ex


#Export some constants like compiler
export CC=g++
export DBGIC=g++
export LD=ld
export AS=as

#Handle every possible argument passed to this script
while [[ $# -gt 1 ]]; do
  key = "$1"
  case $key in
    debug|DEBUG|Debug|dEBUG)
      debug=YES
      release=NO
      shift
      ;;
    release|RELEASE|Release|rELEASE)
      release=YES
      debug=NO
      shift
      ;;
    -v|--verbose)
      verbose=YES
      shift
      ;;
    -V|--version)
      echo "Build Script Version 0.1"
      exit 0
      ;;
    -h|--help)
      echo "Build Script Help:"
      echo "BuildEngine.sh debug - Make an debug build (Standard option)"
      echo "BuildEngine.sh release - Make an release build"
      echo ""
      echo "Other possible arguments:"
      echo "--verbose/-v: Talk to you a lot"
      echo "--version/-V: Output the version"
      echo ""
      exit 0
      ;;
    *)
      echo "No build type specified. Asserting we want a debug build!"
      debug=YES
      release=NO
      shift
      ;;
    ;;
  esac
  shift
done

if [!release && !debug]; then
  echo "No build type specified. Asserting we want a debug build!"
  debug=YES
  release=NO
fi

#Get some constants like target arch
export ARCH='uname -m'
export SYSTM='uname -o'

#Fail instantly if we got the wrong OS here
if [$SYSTM -eq "MS/Windows"]; then
  echo "Why do you use Windows for an Linux build?"
  echo "If you want to build for Windows, use Visual Studio!"
  exit 3
fi
if [$SYSTM -eq "Cygwin"]; then
  echo "Cygwin support could be enabled, but meh."
  echo "If you want to build for Windows, use Visual Studio!"
  exit 3
fi
if [$SYSTM -eq ""]; then
  echo "ERROR: Unable to enumerate the operating system used!"
  echo "If you want to build for Windows, use Visual Studio!"
  exit 3
fi
if [$SYSTM -eq "Msys"]; then
  echo "MinGW support could be enabled, but meh."
  echo "Why don't you use Visual Studio?"
  exit 3
fi
if [$SYSTM -eq "UWIN"]; then
  echo "UWIN support could be enabled, but meh."
  echo "Use Visual Studio instead!"
  exit 3
fi

#Fail instantly if we are on the wrong target architecture
if [$ARCH -neq "x86_64"]; then
  echo "We NEED an Intel/AMD 64 bit processor!"
  exit 5
fi

#Get ourselves into the correct directory
cd ../../ #Directory src/

#Make an object directory if we don't have one yet
if [! -e "Build/Linux/object"]; then
  mkdir Build/Linux/object
fi
if [! -e "Build/Linux/object/Debug" && $debug -eq "YES"]; then
  mkdir Build/Linux/object/Debug
fi
if [! -e "Build/Linux/object/Release" && $release -eq "YES"]; then
  mkdir Build/Linux/object/Release
fi

#Make an output directory if we don't have one yet
if [! -e "Build/Linux/out"]; then
  mkdir Build/Linux/out
fi
if [! -e "Build/Linux/out/Debug" && $debug -eq "YES"]; then
  mkdir Build/Linux/out/Debug
fi
if [! -e "Build/Linux/out/Release" && $release -eq "YES"]; then
  mkdir Build/Linux/out/Release
fi


#TODO: Build that shit^^
