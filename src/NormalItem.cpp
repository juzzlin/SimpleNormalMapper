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

#include "NormalItem.hpp"
#include "Normal.hpp"

#include <QPainter>
#include <cassert>

namespace {
const int HEAD_RADIUS = 10;
const int OUTER_RADIUS = 20;
const int LINE_WIDTH  = 2;
const QColor HEAD_COLOR(0, 0, 255, 128);
const QColor TAIL_COLOR(255, 0, 0, 128);
}

NormalItem::NormalItem(NormalItem::Type type)
    : m_type(type)
    , m_normal(nullptr)
    , m_color(type == Head ? HEAD_COLOR : TAIL_COLOR)
    , m_radius(type == Head ? HEAD_RADIUS : OUTER_RADIUS)
{
}

QRectF NormalItem::boundingRect () const
{
    return QRectF(-m_radius, -m_radius, m_radius * 2, m_radius * 2);
}

void NormalItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->save();

    painter->setPen(QPen(QBrush(m_color), LINE_WIDTH));
    painter->drawEllipse(
        QPointF(
            boundingRect().x() + boundingRect().width() / 2  + LINE_WIDTH,
            boundingRect().y() + boundingRect().height() / 2 + LINE_WIDTH),
            boundingRect().width() / 2 - LINE_WIDTH,
            boundingRect().height() / 2 - LINE_WIDTH);

    painter->restore();
}

NormalItem::Type NormalItem::getType() const
{
    return m_type;
}

void NormalItem::setNormal(Normal & normal)
{
    m_normal = &normal;
}

Normal & NormalItem::normal() const
{
    assert(m_normal);
    return *m_normal;
}

