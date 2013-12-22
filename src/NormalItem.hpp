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

#ifndef NORMALITEM_HPP
#define NORMALITEM_HPP

#include <QGraphicsItem>

class Normal;

class NormalItem : public QGraphicsItem
{
public:

    enum Type {Head, Tail};

    explicit NormalItem(Type type);

    //! \reimp
    virtual QRectF boundingRect () const;

    //! \reimp
    virtual void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    //! Note that QGraphicsItem already defines type().
    Type getType() const;

    void setNormal(Normal & normal);

    Normal & normal() const;

private:

    NormalItem::Type m_type;
    Normal         * m_normal;
    QColor           m_color;
    float            m_radius;
};

#endif // NORMALITEM_HPP
