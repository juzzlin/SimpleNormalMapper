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
#include <QPainter>

namespace {
const int RADIUS = 5;
const int LINE_WIDTH = 2;
const QColor HEAD_COLOR(0, 255, 0, 128);
const QColor TAIL_COLOR(255, 0, 0, 128);
}

NormalItem::NormalItem(NormalItem::Type type)
    : m_type(type)
{
}

QRectF NormalItem::boundingRect () const
{
    return QRectF(-RADIUS / 2, -RADIUS / 2, RADIUS, RADIUS);
}

void NormalItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->save();

    if (m_type == Head)
    {
        painter->setPen(QPen(QBrush(HEAD_COLOR), LINE_WIDTH));
    }
    else
    {
        painter->setPen(QPen(QBrush(TAIL_COLOR), LINE_WIDTH));
    }

    painter->drawEllipse(
        QPointF(
            boundingRect().x() + boundingRect().width() / 2  + LINE_WIDTH / 2,
            boundingRect().y() + boundingRect().height() / 2 + LINE_WIDTH / 2),
        LINE_WIDTH,
        LINE_WIDTH);

    painter->restore();
}
