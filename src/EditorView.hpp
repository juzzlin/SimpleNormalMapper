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

#include <QGraphicsView>

class Editor;

class EditorView : public QGraphicsView
{
public:

    EditorView(Editor & editor, QWidget * parent = nullptr);

protected:

    //! \reimp
    void mouseMoveEvent(QMouseEvent * event);

    //! \reimp
    void mousePressEvent(QMouseEvent * event);

    //! \reimp
    void mouseReleaseEvent(QMouseEvent * event);

    //! \reimp
    void keyPressEvent(QKeyEvent * event);

private:

    Editor & m_editor;
    QPoint   m_clickedPos;
    QPointF  m_clickedScenePos;
};
