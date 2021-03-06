function bv_tbb_initialize
{
    export DO_TBB="no"
}

function bv_tbb_enable
{
    DO_TBB="yes"
}

function bv_tbb_disable
{
    DO_TBB="no"
}

function bv_tbb_depends_on
{
    echo ""
}

function bv_tbb_info
{
    export TBB_VERSION=${TBB_VERSION:-"tbb2018_20171205oss"}
    if [[ "$OPSYS" == "Darwin" ]] ; then
        export TBB_FILE=${TBB_FILE:-"${TBB_VERSION}_mac.tgz"}
    else
        export TBB_FILE=${TBB_FILE:-"${TBB_VERSION}_lin.tgz"}
    fi
    export TBB_COMPATIBILITY_VERSION=${TBB_COMPATIBILITY_VERSION:-"${TBB_VERSION}"}
    export TBB_BUILD_DIR=${TBB_BUILD_DIR:-"${TBB_VERSION}"}
    export TBB_MD5_CHECKSUM=""
    export TBB_SHA256_CHECKSUM=""
}

function bv_tbb_print
{
    printf "%s%s\n" "TBB_FILE=" "${TBB_FILE}"
    printf "%s%s\n" "TBB_VERSION=" "${TBB_VERSION}"
    printf "%s%s\n" "TBB_COMPATIBILITY_VERSION=" "${TBB_COMPATIBILITY_VERSION}"
    printf "%s%s\n" "TBB_BUILD_DIR=" "${TBB_BUILD_DIR}"
}

function bv_tbb_host_profile
{
    if [[ "$DO_TBB" == "yes" ]] ; then
        echo >> $HOSTCONF
        echo "##" >> $HOSTCONF
        echo "## TBB" >> $HOSTCONF
        echo "##" >> $HOSTCONF
        echo "VISIT_OPTION_DEFAULT(TBB_ROOT \${VISITHOME}/tbb/\${VISITARCH}/$TBB_VERSION)" \
            >> $HOSTCONF
    fi
}

function bv_tbb_print_usage
{
    #tbb does not have an option, it is only dependent on tbb.
    printf "%-15s %s [%s]\n" "--tbb" "Build TBB" "$DO_TBB"
}

function bv_tbb_ensure
{
    if [[ "$DO_TBB" == "yes" ]] ; then
        ensure_built_or_ready "tbb" $TBB_VERSION $TBB_BUILD_DIR $TBB_FILE
        if [[ $? != 0 ]] ; then
            ANY_ERRORS="yes"
            DO_TBB="no"
            error "Unable to build TBB.  ${TBB_FILE} not found."
        fi
    fi
}

function bv_tbb_dry_run
{
    if [[ "$DO_TBB" == "yes" ]] ; then
        echo "Dry run option not set for TBB."
    fi
}

# ***************************************************************************
# build_tbb
#
# Modifications:
#
# ***************************************************************************

function build_tbb
{
    # Unzip the TBB tarball and copy it to the VisIt installation.
    info "Installing prebuilt TBB"
    tar zxvf $TBB_FILE
    mkdir $VISITDIR/tbb
    mkdir $VISITDIR/tbb/$VISITARCH
    cp -R $TBB_VERSION "$VISITDIR/tbb/$VISITARCH"
    rm -rf $TBB_VERSION

    if [[ "$DO_GROUP" == "yes" ]] ; then
        chmod -R ug+w,a+rX "$VISITDIR/tbb/$VISITARCH"
        chgrp -R ${GROUP} "$VISITDIR/tbb/$VISITARCH"
    fi
    cd "$START_DIR"
    info "Done with TBB"
    return 0
}

function bv_tbb_is_enabled
{
    if [[ $DO_TBB == "yes" ]]; then
        return 1    
    fi
    return 0
}

function bv_tbb_is_installed
{
    check_if_installed "tbb"
    if [[ $? == 0 ]] ; then
        return 1
    fi
    return 0
}

function bv_tbb_build
{
    if [[ "$DO_TBB" == "yes" ]] ; then
        check_if_installed "tbb"
        if [[ $? == 0 ]] ; then
            info "Skipping build of TBB"
        else
            build_tbb
            if [[ $? != 0 ]] ; then
                error "Unable to build or install TBB.  Bailing out."
            fi
            info "Done building TBB"
        fi
    fi
}

