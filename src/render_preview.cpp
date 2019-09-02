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

#include "render_preview.hpp"
#include "editor.hpp"
#include "settings.hpp"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QPixmap>

RenderPreview::RenderPreview(Renderer & renderer, QWidget * parent)
    : QGraphicsView(parent)
    , m_scene()
    , m_renderer(renderer)
{
    setScene(&m_scene);
    setBackgroundBrush(QBrush{Qt::black});

    connect(&m_renderer, &Renderer::processingFinished, this, &RenderPreview::updatePreview);
}

RenderPreview::~RenderPreview()
{
}

void RenderPreview::prepareForImage(const QImage & image)
{
    m_scene.clear();
    m_scene.setSceneRect(0, 0, image.width(), image.height());
}

void RenderPreview::render()
{
    // Renderer is a thread so use invokeMethod to safely call render().
    QMetaObject::invokeMethod(&m_renderer, "render");
}

void RenderPreview::updatePreview(const QImage & result)
{
    const auto pixmap = QPixmap::fromImage(result);

    m_scene.clear();
    m_scene.setSceneRect(0, 0, pixmap.width(), pixmap.height());
    m_scene.addItem(new QGraphicsPixmapItem(pixmap));
}

void RenderPreview::save()
{
    const auto path = Settings::loadRecentResultPath();
    const auto fileName = QFileDialog::getSaveFileName(
        this, tr("Save the normal map image"), path, tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));

    if (m_renderer.image().save(fileName))
    {
        Settings::saveRecentResultPath(fileName);
        emit messageLogged(tr("Successfully saved to '") + fileName + "'.");
    }
    else
    {
        QMessageBox::critical(
            this,
            tr("Saving failed!"),
            tr("Unknown image type ") + fileName);
        emit messageLogged(tr("Saving failed!"));
    }
}
