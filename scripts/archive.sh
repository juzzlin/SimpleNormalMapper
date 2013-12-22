VERSION=$(git log | grep -m 1 "^\s*[0-9]\.[0-9]\.[0-9]" | awk '{print $1}')
git archive --format=tar --prefix=snm-$VERSION/ HEAD | gzip > snm-$VERSION.tar.gz
git archive --format=zip --prefix=snm-$VERSION/ HEAD > snm-$VERSION.zip

