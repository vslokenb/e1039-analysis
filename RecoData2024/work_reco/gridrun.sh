#!/bin/bash
# gridrun.sh
RUN=$1
SPILL=$2
N_EVT=$3

if [ -z "$CONDOR_DIR_INPUT" -o -z "$CONDOR_DIR_OUTPUT" ] ; then
    echo "!ERROR!  CONDOR_DIR_INPUT/OUTPUT is undefined.  Abort."
    exit 1
fi
echo "INPUT  = $CONDOR_DIR_INPUT"
echo "OUTPUT = $CONDOR_DIR_OUTPUT"
echo "HOST   = $HOSTNAME"
echo "PWD    = $PWD"

tar xzf $CONDOR_DIR_INPUT/input.tar.gz

# Verify core landed correctly
CORE_LOCAL=$PWD/core-inst
if [ ! -e $CORE_LOCAL/this-core.sh ] ; then
    echo "!ERROR! core-inst not found at '$CORE_LOCAL' after extraction.  Abort."
    exit 1
fi
echo "CORE   = $CORE_LOCAL"

# Source setup.sh to get the e1039 environment, compiler flags, etc.
# setup.sh will print a warning and fall back to system core (because
# $USER is empty on the grid node and it re-sets E1039_CORE_DIR itself),
# but that's fine — we apply the local core immediately afterward.
source setup.sh

# Apply local core, overriding whatever setup.sh resolved.
# This mirrors exactly what setup.sh does in the non-grid branch.
echo "Applying local core from $CORE_LOCAL"
source $CORE_LOCAL/this-core.sh

export   LD_LIBRARY_PATH=$CORE_LOCAL/lib:$LD_LIBRARY_PATH
export ROOT_INCLUDE_PATH=$CORE_LOCAL/include:$ROOT_INCLUDE_PATH


# Build only AnaModule — 'src' (the top-level CMakeLists) is not shipped.
# We run cmake and make directly rather than using cmake-this/make-this,
# which would also attempt to build 'src' and fail.
echo "=== Building AnaModule ==="
# Replace these lines in gridrun.sh:

DIR_BUILD_ANA=$PWD/build/AnaModule
DIR_INST_ANA=$PWD/inst
DIR_SRC_ANA=$PWD/AnaModule          # capture before any cd
mkdir -p $DIR_BUILD_ANA
( cd $DIR_BUILD_ANA && cmake -DCMAKE_INSTALL_PREFIX=$DIR_INST_ANA $DIR_SRC_ANA )
if [ $? -ne 0 ] ; then
    echo "!ERROR! cmake failed for AnaModule.  Abort."
    exit 1
fi
( cd $DIR_BUILD_ANA && make install )
if [ $? -ne 0 ] ; then
    echo "!ERROR! make failed for AnaModule.  Abort."
    exit 1
fi

# Make sure the freshly installed library is found by ROOT
export   LD_LIBRARY_PATH=$DIR_INST_ANA/lib:$LD_LIBRARY_PATH
export ROOT_INCLUDE_PATH=$DIR_INST_ANA/include:$ROOT_INCLUDE_PATH
echo "=== AnaModule build complete ==="

touch timestamp.txt

FN_IN=$(printf 'run_%06d_spill_%09d_spin.root' $RUN $SPILL)
FN_OUT=$(printf 'run_%06d_spill_%09d_spin_reco.root' $RUN $SPILL)

echo "ROOT_INCLUDE_PATH = $ROOT_INCLUDE_PATH"
echo "LD_LIBRARY_PATH   = $LD_LIBRARY_PATH"

# Add this line just before the root invocation in gridrun.sh:
export ROOT_INCLUDE_PATH=$DIR_SRC_ANA:$DIR_INST_ANA/include:$ROOT_INCLUDE_PATH

time root -l -b -q "Fun4All.C($RUN, $SPILL, \"$CONDOR_DIR_INPUT/$FN_IN\", \"$FN_OUT\", $N_EVT)"
RET=$?
if [ $RET -ne 0 ] ; then
    echo "Error in Fun4All.C: $RET"
    exit $RET
fi
echo "$RET" >status.txt

find . -mindepth 1 -maxdepth 1 -newer timestamp.txt \
    ! -name "$(basename $CONDOR_DIR_OUTPUT)" \
    -exec mv {} $CONDOR_DIR_OUTPUT \;

echo "gridrun.sh finished!"