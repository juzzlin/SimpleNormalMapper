#include "NormalItem.hpp"
#include <QPainter>

const int RADIUS = 5;

NormalItem::NormalItem()
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

    painter->restore();
}
