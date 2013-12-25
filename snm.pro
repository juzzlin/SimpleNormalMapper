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

# Input
HEADERS += \
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

# Check if PREFIX environment variable is set.
# If not, then assume /usr.
_PREFIX = $$(PREFIX)
isEmpty(_PREFIX) {
    _PREFIX = /usr
}

unix {
    target.path    = $$_PREFIX/bin
    desktop.path   = $$_PREFIX/share/applications
    desktop.name   = snm.desktop
    desktop.files += data/snm.desktop
    desktop.extra  = cp data/snm.desktop.in data/snm.desktop
    icon1.path     = $$_PREFIX/share/icons/hicolor/64x64/apps
    icon1.files   += data/icons/snm.png
    icon2.path     = $$_PREFIX/share/pixmaps
    icon2.files   += data/icons/snm.png
    INSTALLS      += target desktop icon1 icon2
}

