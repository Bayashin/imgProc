#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/k21099kk/src/imgProc/第2回/pixelScan
  make -f /Users/k21099kk/src/imgProc/第2回/pixelScan/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/k21099kk/src/imgProc/第2回/pixelScan
  make -f /Users/k21099kk/src/imgProc/第2回/pixelScan/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/k21099kk/src/imgProc/第2回/pixelScan
  make -f /Users/k21099kk/src/imgProc/第2回/pixelScan/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/k21099kk/src/imgProc/第2回/pixelScan
  make -f /Users/k21099kk/src/imgProc/第2回/pixelScan/CMakeScripts/ReRunCMake.make
fi

