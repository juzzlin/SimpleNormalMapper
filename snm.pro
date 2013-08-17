TEMPLATE        = app
TARGET          = snm
INCLUDEPATH    += .
QT             += widgets
QMAKE_CXXFLAGS += -std=c++11

# Qt version check
!contains(QT_VERSION, ^5\\..*) {
message("Cannot build Qt Creator with Qt version $${QT_VERSION}.")
error("Use at least Qt 5.0.")
}

# Input
HEADERS += \
    src/Config.hpp \
    src/Editor.hpp \
    src/EditorScene.hpp \
    src/EditorView.hpp \
    src/ImageItem.hpp \
    src/MainWindow.hpp \
    src/NormalItem.hpp \
    src/Normal.hpp \
    src/Renderer.hpp \
    src/RenderDialog.hpp \
    src/SettingsDialog.hpp \

SOURCES += \
    src/Config.cpp \
    src/Editor.cpp \
    src/EditorScene.cpp \
    src/EditorView.cpp \
    src/ImageItem.cpp \
    src/main.cpp \
    src/MainWindow.cpp \
    src/NormalItem.cpp \
    src/Normal.cpp \
    src/Renderer.cpp \
    src/RenderDialog.cpp \
    src/SettingsDialog.cpp \
