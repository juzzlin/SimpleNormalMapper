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
    src/IO.hpp \
    src/MainWindow.hpp \
    src/NormalItem.hpp \
    src/Normal.hpp \
    src/Renderer.hpp \
    src/RenderPreview.hpp \
    src/SettingsDialog.hpp \
    src/Settings.hpp

SOURCES += \
    src/Config.cpp \
    src/ControlToolBar.cpp \
    src/Editor.cpp \
    src/EditorScene.cpp \
    src/EditorView.cpp \
    src/ImageItem.cpp \
    src/IO.cpp \
    src/main.cpp \
    src/MainWindow.cpp \
    src/NormalItem.cpp \
    src/Normal.cpp \
    src/Renderer.cpp \
    src/RenderPreview.cpp \
    src/SettingsDialog.cpp \
    src/Settings.cpp
