#!/bin/sh

etc_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null && pwd)"
GOOGLETEST_HDL=`cd $etc_dir/.. ; pwd`
export GOOGLETEST_HDL

# Add a path to the simscripts directory
export PATH=$GOOGLETEST_HDL/packages/simscripts/bin:$PATH

# Force the PACKAGES_DIR
export PACKAGES_DIR=$GOOGLETEST_HDL/packages

