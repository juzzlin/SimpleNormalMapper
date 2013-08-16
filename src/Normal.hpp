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

#ifndef NORMAL_HPP
#define NORMAL_HPP

#include <QGraphicsLineItem>
#include <QVector3D>
#include <QPointF>

class NormalItem;

class Normal
{
public:

    static const int OUTER_RADIUS = 20;

    Normal(NormalItem & head, NormalItem & tail, QGraphicsLineItem & line);

    const QVector3D & vector() const;

    QPointF location() const;

    NormalItem & head() const;

    NormalItem & tail() const;

    QGraphicsLineItem & line() const;

    void updateLine();

private:

    NormalItem        & m_head;
    NormalItem        & m_tail;
    QGraphicsLineItem & m_line;
    QVector3D           m_vector;
};

#endif // NORMAL_HPP
