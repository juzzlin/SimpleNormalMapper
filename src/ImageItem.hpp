#ifndef IMAGEITEM_HPP
#define IMAGEITEM_HPP

#include <QGraphicsItem>
#include <QPixmap>

class ImageItem : public QGraphicsItem
{
public:

    explicit ImageItem(QPixmap pixmap);

    //! \reimp
    virtual QRectF boundingRect () const;

    //! \reimp
    virtual void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

private:

    QPixmap m_pixmap;
    QSize m_size;
};

#endif // IMAGEITEM_HPP
