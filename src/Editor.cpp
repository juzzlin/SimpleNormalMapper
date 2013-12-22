// This file is part of Simple Normal Mapper.
// Copyright (C) 2013 Jussi Lind <jussi.lind@iki.fi>
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

#include "Editor.hpp"
#include "EditorScene.hpp"
#include "EditorView.hpp"
#include "ImageItem.hpp"
#include "MainWindow.hpp"

#include <QGraphicsItem>
#include <QDebug>

#include <cassert>

Editor::Editor(const std::vector<std::string> & args)
    : m_scene(new EditorScene(this))
    , m_view(new EditorView(*this))
    , m_window(new MainWindow(*this, m_renderer))
    , m_selectedNormalItem(nullptr)
    , m_movedNormalItem(nullptr)
    , m_mode(Editor::None)
    , m_renderer()
{
    if (args.size() == 2)
    {
        m_window->loadImageFile(args.at(1).c_str());
    }

    m_window->show();
}

EditorView & Editor::view() const
{
    assert(m_view);
    return *m_view;
}

EditorScene & Editor::scene() const
{
    assert(m_scene);
    return *m_scene;
}

void Editor::setMode(Editor::Mode mode)
{
    m_mode = mode;
}

Editor::Mode Editor::mode() const
{
    return m_mode;
}

void Editor::setImage(QImage image)
{
    m_pixmap.convertFromImage(image);

    m_view->ensureVisible(0, 0, 0, 0);
    m_scene->setSceneRect(0, 0, m_pixmap.width(), m_pixmap.height());
    m_scene->clear();

    QGraphicsItem * imageItem = new ImageItem(m_pixmap);
    m_scene->addItem(imageItem);
    imageItem->setPos(m_pixmap.width() / 2, m_pixmap.height() / 2);

    m_renderer.setInput(m_pixmap);
}

QPixmap Editor::image() const
{
    return m_pixmap;
}

void Editor::addNormal(Normal & normal)
{
    m_normals << NormalPtr(&normal);
}

void Editor::clear()
{
    m_normals.clear();
}

void Editor::setSelectedNormalItem(NormalItem * normal)
{
    m_selectedNormalItem = normal;
}

void Editor::setMovedNormalItem(NormalItem * normal)
{
    m_movedNormalItem = normal;
}

NormalItem * Editor::selectedNormalItem() const
{
    return m_selectedNormalItem;
}

NormalItem * Editor::movedNormalItem() const
{
    return m_movedNormalItem;
}

Editor::~Editor()
{
    delete m_window;

    m_selectedNormalItem = nullptr;
    m_movedNormalItem = nullptr;
}
