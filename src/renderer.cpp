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

#include "renderer.hpp"

#include <QImage>
#include <QRgb>
#include <cmath>

static const int DEFAULT_Z = -10;

Renderer::Renderer(QObject * parent)
    : QObject(parent)
{
}

Renderer::HeightMap Renderer::buildHeightMap()
{
    Renderer::HeightMap output;
    output.resize(m_width * m_height);

    int minIntensity = 0;
    int maxIntensity = 0;
    for (int j = 0; j < m_height; j++)
    {
        for (int i = 0; i < m_width; i++)
        {
            const int r = qRed(m_image.pixel(i, j));
            const int g = qGreen(m_image.pixel(i, j));
            const int b = qBlue(m_image.pixel(i, j));
            const int intensity = static_cast<int>(0.2989 * r + 0.5870 * g + 0.1140 * b);
            minIntensity = intensity < minIntensity ? intensity : minIntensity;
            maxIntensity = intensity > maxIntensity ? intensity : maxIntensity;
        }
    }

    for (int j = 0; j < m_height; j++)
    {
        for (int i = 0; i < m_width; i++)
        {
            const int r = qRed(m_image.pixel(i, j));
            const int g = qGreen(m_image.pixel(i, j));
            const int b = qBlue(m_image.pixel(i, j));
            const int a = qAlpha(m_image.pixel(i, j));
            const int intensity = static_cast<int>(0.2989 * r + 0.5870 * g + 0.1140 * b);
            const int index = j * m_width + i;

            if (a == 0)
            {
                output[index].height = m_amplitude * DEFAULT_Z;
            }
            else
            {
                output[index].height = m_amplitude * float(intensity - minIntensity) / (maxIntensity - minIntensity);
            }

            output[index].normal = QVector3D(0, 0, 0);
        }
    }

    return output;
}

float Renderer::getHeight(int x, int y)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
    {
        return DEFAULT_Z;
    }

    return m_map.at(y * m_width + x).height;
}

QVector3D Renderer::calculateNormal(int x, int y, float r, float a)
{
    const float DEG_TO_RAD = 3.1415f / 180.0f;

    const int sx1 = static_cast<int>(x + std::cos(a * DEG_TO_RAD) * r);
    const int sy1 = static_cast<int>(y + std::sin(a * DEG_TO_RAD) * r);
    const int sx2 = static_cast<int>(x + std::cos((a + 60) * DEG_TO_RAD) * r);
    const int sy2 = static_cast<int>(y + std::sin((a + 60) * DEG_TO_RAD) * r);
    const int sx3 = static_cast<int>(x + std::cos((a + 120) * DEG_TO_RAD) * r);
    const int sy3 = static_cast<int>(y + std::sin((a + 120) * DEG_TO_RAD) * r);

    const QVector3D h1(sx2 - sx1, sy2 - sy1, getHeight(sx2, sy2) - getHeight(sx1, sy1));
    const QVector3D h2(sx3 - sx1, sy3 - sy1, getHeight(sx3, sy3) - getHeight(sx1, sy1));

    return QVector3D::crossProduct(h1, h2).normalized();
}

void Renderer::calculateNormals(float r)
{
    for (int j = 0; j < m_height; j++)
    {
        for (int i = 0; i < m_width; i++)
        {
            int steps = 0;
            for (int a = 0; a < 360; a += 45)
            {
                m_map[j * m_width + i].normal += calculateNormal(i, j, r, a);
                steps++;
            }

            m_map[j * m_width + i].normal /= steps;
        }
    }
}

void Renderer::render()
{
    calculateNormals(m_radius);

    for (int j = 0; j < m_height; j++)
    {
        for (int i = 0; i < m_width; i++)
        {
            const int index = j * m_width + i;

            int r = static_cast<int>(m_map.at(index).normal.x() * 128);
            r += 128;
            r = r < 0   ? 0   : r;
            r = r > 255 ? 255 : r;

            int g = static_cast<int>(m_map.at(index).normal.y() * 128);
            g += 128;
            g = g < 0   ? 0   : g;
            g = g > 255 ? 255 : g;

            int b = static_cast<int>(m_map.at(index).normal.z() * 128);
            b += 128;
            b = b < 0   ? 0   : b;
            b = b > 255 ? 255 : b;

            m_result.setPixel(i, j, qRgb(r, g, b));
        }
    }

    emit processingFinished(m_result);
}

void Renderer::setInput(const QImage & input)
{
    m_width  = input.width();
    m_height = input.height();
    m_image  = input;
    m_result = QImage(m_width, m_height, QImage::Format_ARGB32);
    m_map    = buildHeightMap();
}

void Renderer::setAmplitude(float amplitude)
{
    if (!qFuzzyCompare(m_amplitude, amplitude))
    {
        m_amplitude = amplitude;
        m_map = buildHeightMap();
    }
}

void Renderer::setRadius(float radius)
{
    m_radius = radius;
}

const QImage & Renderer::image() const
{
    return m_result;
}
