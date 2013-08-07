TEMPLATE        = app
TARGET          = snm
INCLUDEPATH    += .
QT             += widgets
QMAKE_CXXFLAGS += -std=c++0x

# Qt version check
!contains(QT_VERSION, ^5\\..*) {
message("Cannot build Qt Creator with Qt version $${QT_VERSION}.")
error("Use at least Qt 5.0.")
}

# Input
HEADERS += src/Editor.hpp src/EditorScene.hpp src/EditorView.hpp src/MainWindow.hpp \
    src/ImageItem.hpp src/NormalItem.hpp
SOURCES += src/Editor.cpp src/EditorScene.cpp src/EditorView.cpp src/main.cpp src/MainWindow.cpp \
    src/ImageItem.cpp src/NormalItem.cpp
