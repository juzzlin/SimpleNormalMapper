#!/bin/sh

# Script taken from http://qt-project.org/doc/qt-5.0/qtdoc/deployment-x11.html

appname=`basename $0 | sed s,\.sh$,,`

dirname=`dirname $0`
tmp="${dirname#?}"

if [ "${dirname%$tmp}" != "/" ]; then
    dirname=$PWD/$dirname
fi

LD_LIBRARY_PATH=$dirname/deps
echo $LD_LIBRARY_PATH
export LD_LIBRARY_PATH
$dirname/$appname "$@"

