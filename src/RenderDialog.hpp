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

#ifndef RENDERDIALOG_HPP
#define RENDERDIALOG_HPP

#include <QDialog>

class Editor;
class QLabel;

class RenderDialog : public QDialog
{
    Q_OBJECT

public:

    explicit RenderDialog(Editor & editor, QWidget * parent = nullptr);

private slots:

    void render();

    void save();

private:

    void initLayout();

    Editor & m_editor;
    QLabel * m_pixmapLabel;
};

#endif // RENDERDIALOG_HPP
