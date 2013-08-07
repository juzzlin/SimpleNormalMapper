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

#include "EditorView.hpp"
#include "Editor.hpp"
#include "EditorScene.hpp"
#include "NormalItem.hpp"

#include <QMouseEvent>

EditorView::EditorView(Editor & editor, QWidget * parent)
    : QGraphicsView(&editor.scene(), parent)
    , m_editor(editor)
{
    setBackgroundBrush(QBrush(QColor(0, 0, 0)));
}

void EditorView::mouseMoveEvent(QMouseEvent * event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void EditorView::mousePressEvent(QMouseEvent * event)
{
    m_clickedPos      = event->pos();
    m_clickedScenePos = mapToScene(m_clickedPos);

    if (m_editor.mode() == Editor::InsertNormals)
    {
        addNormal();
    }

    QGraphicsView::mousePressEvent(event);
}

void EditorView::addNormal()
{
    NormalItem * head = new NormalItem(NormalItem::Head);
    m_editor.scene().addItem(head);
    head->setPos(m_clickedScenePos);

    NormalItem * tail = new NormalItem(NormalItem::Tail);
    m_editor.scene().addItem(tail);
    tail->setPos(m_clickedScenePos);

    NormalItem * knob = new NormalItem(NormalItem::Knob);
    m_editor.scene().addItem(knob);
    knob->setPos(m_clickedScenePos);

    Normal * normal = new Normal(*head, *tail, *knob);
    m_editor.addNormal(*normal);
}

void EditorView::mouseReleaseEvent(QMouseEvent * event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void EditorView::keyPressEvent(QKeyEvent * event)
{
    QGraphicsView::keyPressEvent(event);
}
