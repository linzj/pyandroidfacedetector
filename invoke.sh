MYPATH=`dirname $0`
PYTHONPATH=`readlink -f $MYPATH/build/lib.linux-x86_64-2.7` \
$*
