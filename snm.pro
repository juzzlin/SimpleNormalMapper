TEMPLATE        = app
TARGET          = snm
INCLUDEPATH    += .
QMAKE_CXXFLAGS += -std=c++0x

# Qt version check
message("Building for Qt version $${QT_VERSION}.")
contains(QT_VERSION, ^5\\..*) {
QT += widgets
DEFINES += USE_QT5
} else {
QT += gui
}

DEFINES += VERSION=\\\"0.1.1\\\"

# Input
HEADERS += \
    src/AboutDlg.hpp \
    src/Config.hpp \
    src/ControlToolBar.hpp \
    src/Editor.hpp \
    src/EditorScene.hpp \
    src/EditorView.hpp \
    src/ImageItem.hpp \
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
    src/ImageItem.cpp \
    src/main.cpp \
    src/MainWindow.cpp \
    src/Renderer.cpp \
    src/RenderPreview.cpp \
    src/Settings.cpp

RESOURCES += data/icons/Icons.qrc
RC_FILE = data/icons/Windows.rc

# Install to /opt by calling "OPT=1 qmake" or to wanted prefix
# by e.g. "PREFIX=/usr qmake".

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
    _BIN = $$_PREFIX
    _DAT = $$_PREFIX
}

unix {
    target.path    = $$_BIN/bin
    desktop.path   = $$_DAT/share/applications
    desktop.name   = snm.desktop
    desktop.files += data/snm.desktop

    if (!isEmpty(_OPT)) {
        desktop.extra  = cp data/snm.desktop.opt.in data/snm.desktop
    } else {
        desktop.extra  = cp data/snm.desktop.in data/snm.desktop
    }

    icon1.path     = $$_DAT/share/icons/hicolor/64x64/apps
    icon1.files   += data/icons/snm.png
    icon2.path     = $$_DAT/share/pixmaps
    icon2.files   += data/icons/snm.png
    INSTALLS      += target desktop icon1 icon2
}

