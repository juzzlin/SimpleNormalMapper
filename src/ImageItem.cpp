#include "ImageItem.hpp"
#include <QPainter>

ImageItem::ImageItem(QPixmap pixmap)
    : m_pixmap(pixmap)
    , m_size(m_pixmap.width(), m_pixmap.height())
{
}

QRectF ImageItem::boundingRect () const
{
    return QRectF(-m_size.width() / 2, -m_size.height() / 2, m_size.width(), m_size.height());
}

void ImageItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->save();

    painter->drawPixmap(
        boundingRect().x(), boundingRect().y(),
        boundingRect().width(), boundingRect().height(),
        m_pixmap);

    painter->restore();
}
