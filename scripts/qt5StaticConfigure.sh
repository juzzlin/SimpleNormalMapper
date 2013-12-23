#!/bin/bash

PREFIX='/home/jussil/qt5'
./configure \
            -developer-build \
            -opensource \
            -confirm-license \
            -force-pkg-config \
            -release \
            -static \
            -prefix $PREFIX \
            -no-icu \
            -opengl desktop \
            -no-glib \
            -accessibility \
            -nomake examples \
            -nomake tests \
            -qt-zlib \
            -qt-libpng \
            -qt-libjpeg \
            -qt-sql-sqlite \
            -qt-xcb \
            -qt-pcre \
            -v

