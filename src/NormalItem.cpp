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
