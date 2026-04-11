DIR_TOP=$(dirname $(readlink -f $BASH_SOURCE))
DIR_BUILD=$DIR_TOP/build
DIR_INST=$DIR_TOP/inst

FN_SETUP=/exp/seaquest/app/software/osg/software/e1039/this-e1039.sh
if [ ! -e $FN_SETUP ] ; then # On grid
    FN_SETUP=/cvmfs/seaquest.opensciencegrid.org/seaquest/${FN_SETUP#/exp/seaquest/app/software/osg/}
fi
source $FN_SETUP

# Override system core with local core
E1039_CORE_DIR=/seaquest/users/$USER/displaced_rereco/core-inst
if [ -e $E1039_CORE_DIR/this-core.sh ] ; then
    source $E1039_CORE_DIR/this-core.sh
else
    echo "!!WARNING!!  Cannot find local core at '$E1039_CORE_DIR'.  Using system core."
fi

export   LD_LIBRARY_PATH=$DIR_INST/lib:$LD_LIBRARY_PATH
export ROOT_INCLUDE_PATH=$DIR_INST/include:$ROOT_INCLUDE_PATH

# Map each subdirectory name to its source location
declare -A SUBDIR_SRC
SUBDIR_SRC["AnaModule"]=$DIR_TOP/AnaModule
SUBDIR_SRC["src"]=$DIR_TOP

function cmake-this {
    if [ -e $DIR_BUILD ] ; then
        echo "Clean up the build directory..."
        \rm -rf $DIR_BUILD
    fi
    if [ -e $DIR_INST ] ; then
        echo "Clean up the install directory..."
        \rm -rf $DIR_INST
    fi

    local OK=true
    for SUBDIR in AnaModule src ; do
        local SRC=${SUBDIR_SRC[$SUBDIR]}
        if [ ! -e $SRC ] ; then
            echo "Skipping '$SUBDIR' (source not found at '$SRC')."
            continue
        fi
        local BUILD=$DIR_BUILD/$SUBDIR
        mkdir -p $BUILD
        echo "Run cmake for $SUBDIR (source: $SRC)..."
        ( cd $BUILD && cmake -DCMAKE_INSTALL_PREFIX=$DIR_INST $SRC )
        if [ $? -ne 0 ] ; then
            echo "NG.  cmake failed for $SUBDIR."
            OK=false
        fi
    done

    if $OK ; then
        echo "OK.  Run 'make-this' at any time/directory."
        return 0
    else
        echo "NG.  Need a fix."
        return 1
    fi
}

function make-this {
    local OK=true
    for SUBDIR in AnaModule src ; do
        local BUILD=$DIR_BUILD/$SUBDIR
        if [ ! -e $BUILD/Makefile ] ; then
            echo "Skipping '$SUBDIR': build directory not ready (run cmake-this first)."
            continue
        fi
        echo "Building $SUBDIR..."
        ( cd $BUILD && make install )
        if [ $? -ne 0 ] ; then
            echo "NG.  make failed for $SUBDIR."
            OK=false
        fi
    done
    $OK && return 0 || return 1
}

alias jobsub_q_mine='jobsub_q --group spinquest --user=$USER'