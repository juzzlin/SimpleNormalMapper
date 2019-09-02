TEMPLATE        = app
TARGET          = snm
INCLUDEPATH    += .
QMAKE_CXXFLAGS += -std=c++11

# Qt version check
contains(QT_VERSION, ^5\\..*) {
    message("Building for Qt version $${QT_VERSION}.")
    QT += widgets xml
} else {
    error("Qt5 is required!")
}

QT += widgets

DEFINES += VERSION=\\\"1.1.0\\\"

# Input
HEADERS += \
    src/about_dlg.hpp \
    src/config.hpp \
    src/control_tool_bar.hpp \
    src/editor.hpp \
    src/editor_view.hpp \
    src/main_window.hpp \
    src/renderer.hpp \
    src/render_preview.hpp \
    src/settings.hpp

SOURCES += \
    src/about_dlg.cpp \
    src/config.cpp \
    src/control_tool_bar.cpp \
    src/editor.cpp \
    src/editor_view.cpp \
    src/main.cpp \
    src/main_window.cpp \
    src/renderer.cpp \
    src/render_preview.cpp \
    src/settings.cpp

RESOURCES += data/icons/Icons.qrc
RC_FILE = data/icons/Windows.rc

# Install to /opt by calling "OPT=1 qmake" or to wanted prefix
# by e.g. "PREFIX=/usr qmake".

unix {

    _OPT = $$(OPT)
    _BIN = ""
    _DAT = ""
    if (!isEmpty(_OPT)) {
    message("Installs to /opt")
        _BIN = /opt/snm
        _DAT = /usr
    } else {
        # Check if PREFIX environment variable is set.
        # If not, then assume /usr.
        _PREFIX = $$(PREFIX)
        isEmpty(_PREFIX) {
            _PREFIX = /usr
        }
        message("Installs to "$$_PREFIX)
        _BIN = $$_PREFIX/bin
        _DAT = $$_PREFIX
    }

    # This is for DEB/RPM packaging
    _DESTDIR = $$(DESTDIR)
    if (!isEmpty(_DESTDIR)) {
        _BIN = $$_DESTDIR/$$_BIN
        _DAT = $$_DESTDIR/$$_DAT
    }

    target.path  = $$_BIN
    desktop.path = $$_DAT/share/applications

    if (!isEmpty(_OPT)) {
        desktop.files = data/opt/snm.desktop
    } else {
        desktop.files = data/snm.desktop
    }

    icon1.path     = $$_DAT/share/icons/hicolor/64x64/apps
    icon1.files   += data/icons/snm.png
    icon2.path     = $$_DAT/share/pixmaps
    icon2.files   += data/icons/snm.png
    INSTALLS      += target desktop icon1 icon2
}

