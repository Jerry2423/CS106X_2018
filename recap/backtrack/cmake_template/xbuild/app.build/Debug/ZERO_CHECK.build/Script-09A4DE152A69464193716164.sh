#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/bryant/Programming/cs106b/recap/backtrack/cmake_template/xbuild
  make -f /Users/bryant/Programming/cs106b/recap/backtrack/cmake_template/xbuild/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/bryant/Programming/cs106b/recap/backtrack/cmake_template/xbuild
  make -f /Users/bryant/Programming/cs106b/recap/backtrack/cmake_template/xbuild/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/bryant/Programming/cs106b/recap/backtrack/cmake_template/xbuild
  make -f /Users/bryant/Programming/cs106b/recap/backtrack/cmake_template/xbuild/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/bryant/Programming/cs106b/recap/backtrack/cmake_template/xbuild
  make -f /Users/bryant/Programming/cs106b/recap/backtrack/cmake_template/xbuild/CMakeScripts/ReRunCMake.make
fi

