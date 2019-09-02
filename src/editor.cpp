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

#include "editor.hpp"
#include "editor_view.hpp"
#include "main_window.hpp"

#include <QGraphicsItem>
#include <QGraphicsScene>

#include <cassert>

Editor::Editor(const std::vector<std::string> & args)
    : m_scene(new QGraphicsScene(this))
    , m_view(new EditorView(*this))
    , m_renderer(new Renderer)
    , m_renderThread(new QThread(this))
    , m_window(new MainWindow(*this, *m_renderer))
{
    if (args.size() == 2)
    {
        m_window->loadImageFile(args.at(1).c_str());
    }

    m_window->show();
    m_renderer->moveToThread(m_renderThread);
    m_renderThread->start();
}

EditorView & Editor::view() const
{
    assert(m_view);
    return *m_view;
}

QGraphicsScene & Editor::scene() const
{
    assert(m_scene);
    return *m_scene;
}

void Editor::setImage(QImage image)
{
    m_view->ensureVisible(0, 0, 0, 0);

    m_pixmap.convertFromImage(image);

    m_scene->setSceneRect(0, 0, m_pixmap.width(), m_pixmap.height());
    m_scene->clear();
    m_scene->addItem(new QGraphicsPixmapItem(m_pixmap));

    // Renderer is a thread so use invokeMethod to safely set the input.
    QMetaObject::invokeMethod(m_renderer, "setInput", Q_ARG(QImage, image));
}

void Editor::quit()
{
    m_renderThread->quit();
    m_renderThread->wait();
}

QPixmap Editor::image() const
{
    return m_pixmap;
}

Editor::~Editor() = default;
