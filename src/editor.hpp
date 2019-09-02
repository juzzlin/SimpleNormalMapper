// This file is part of Simple Normal Mapper.
// Copyright (c) 2013 Simple Normal Mapper developers.
//
// Simple Normal Mapper is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Simple Normal Mapper is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Simple Normal Mapper. If not, see <http://www.gnu.org/licenses/>.

#include <QObject>
#include <QPixmap>
#include <QThread>
#include <QImage>
#include <QList>

#include <string>
#include <vector>
#include <memory>

#include "renderer.hpp"

class QGraphicsScene;
class EditorView;
class MainWindow;

class Editor : public QObject
{
    Q_OBJECT

public:

    Editor(const std::vector<std::string> & args);

    virtual ~Editor();

    void setImage(QImage image);

    void quit();

    QPixmap image() const;

    EditorView & view() const;

    QGraphicsScene & scene() const;

private:

    QGraphicsScene * m_scene;

    EditorView * m_view;

    Renderer * m_renderer;

    QThread * m_renderThread;

    std::unique_ptr<MainWindow> m_window;

    QImage m_image;

    QPixmap m_pixmap;
};

