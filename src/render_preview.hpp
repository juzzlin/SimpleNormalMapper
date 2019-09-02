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

#ifndef RENDERDIALOG_HPP
#define RENDERDIALOG_HPP

#include <QGraphicsView>
#include <QGraphicsScene>

class Renderer;

class RenderPreview : public QGraphicsView
{
    Q_OBJECT

public:

    explicit RenderPreview(Renderer & renderer, QWidget * parent);
    virtual ~RenderPreview();

public slots:

    void render();

    void save();

    void prepareForImage(const QImage & image);

private slots:

    void updatePreview(const QImage & result);

signals:

    void messageLogged(QString message);

private:

    QGraphicsScene m_scene;
    Renderer &     m_renderer;

};

#endif // RENDERDIALOG_HPP
