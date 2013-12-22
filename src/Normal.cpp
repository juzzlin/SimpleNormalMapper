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

#include "Normal.hpp"
#include "NormalItem.hpp"

#include <QBrush>
#include <QPen>

#include <cmath>

Normal::Normal(NormalItem & head, NormalItem & tail, QGraphicsLineItem & line)
    : m_head(head)
    , m_tail(tail)
    , m_line(line)
    , m_angle(90)
    , m_direction(0, 0)
    , m_vector(0, 0, 1) // Point upwards by default
{
    m_line.setPen(QPen(QBrush(QColor(0, 255, 0, 128)), 2, Qt::SolidLine, Qt::RoundCap));
}

void Normal::setAngle(float degrees)
{
    degrees = std::fmin(90, degrees);
    degrees = std::fmax(0, degrees);
    m_vector.setZ(std::sin(degrees * 3.1415 / 180));
    m_vector.normalize();
}

float Normal::angle() const
{
    return m_angle;
}

void Normal::setDirection(QVector2D direction)
{
    m_vector.setX(direction.x());
    m_vector.setY(direction.y());
    m_vector.normalize();
}

const QVector2D & Normal::direction() const
{
    return m_direction;
}

const QVector3D & Normal::vector() const
{
    return m_vector;
}

QPointF Normal::location() const
{
    return m_head.pos();
}

NormalItem & Normal::head() const
{
    return m_head;
}

NormalItem & Normal::tail() const
{
    return m_tail;
}

QGraphicsLineItem & Normal::line() const
{
    return m_line;
}

void Normal::updateLine()
{
    m_line.setLine(m_tail.pos().x(), m_tail.pos().y(), m_head.pos().x(), m_head.pos().y());
}

