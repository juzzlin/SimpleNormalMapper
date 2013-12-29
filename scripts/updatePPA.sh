VERSION=1.0.1
DEBIAN_VERSION=1.0.1-1
rm -rf *${VERSION}*
cp ../simplenormalmapper-code/snm-$VERSION.tar.gz .
mv snm-$VERSION.tar.gz snm_$VERSION.orig.tar.gz 
tar xzvf snm_$VERSION.orig.tar.gz
cd snm-$VERSION
cp -rv packaging/debian .
debuild -S -sa && cd .. && dput ppa:jussi-lind/ppa "snm_${DEBIAN_VERSION}_source.changes"

