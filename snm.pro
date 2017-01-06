TEMPLATE        = app
TARGET          = snm
INCLUDEPATH    += .
QMAKE_CXXFLAGS += -std=c++11

# Check Qt version
!contains(QT_VERSION, ^5\\.[1-9]\\..*) {
message("Cannot build Qt Creator with Qt version $${QT_VERSION}.")
error("Use at least Qt 5.1.")
}

QT += widgets

DEFINES += VERSION=\\\"1.1.0\\\"

# Input
HEADERS += \
    src/AboutDlg.hpp \
    src/Config.hpp \
    src/ControlToolBar.hpp \
    src/Editor.hpp \
    src/EditorScene.hpp \
    src/EditorView.hpp \
    src/MainWindow.hpp \
    src/Renderer.hpp \
    src/RenderPreview.hpp \
    src/Settings.hpp

SOURCES += \
    src/AboutDlg.cpp \
    src/Config.cpp \
    src/ControlToolBar.cpp \
    src/Editor.cpp \
    src/EditorScene.cpp \
    src/EditorView.cpp \
    src/main.cpp \
    src/MainWindow.cpp \
    src/Renderer.cpp \
    src/RenderPreview.cpp \
    src/Settings.cpp

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

