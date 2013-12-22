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

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <QPixmap>
#include <QImage>
#include <QObject>
#include <QVector3D>

class Renderer : public QObject
{
    Q_OBJECT

public:

    struct HeightCell
    {
        float height;
        QVector3D normal;
    };

    typedef QVector<HeightCell> HeightMap;

    explicit Renderer(QObject * parent = nullptr);

public slots:

    void render();

    void setInput(const QPixmap & input);

    void setAmplitude(float amplitude);

    void setRadius(float radius);

signals:

    void processingFinished(const QPixmap & result);

private:

    Renderer::HeightMap buildHeightMap();

    QVector3D calculateNormal(int x, int y, float r, float a);

    void calculateNormals(float r);

    float getHeight(int x, int y);

    QImage              m_image;
    QImage              m_result;
    QPixmap             m_output;
    Renderer::HeightMap m_map;
    int                 m_width;
    int                 m_height;
    float               m_radius;
    float               m_amplitude;
};

#endif // RENDERER_HPP
