#ifndef NORMALITEM_HPP
#define NORMALITEM_HPP

#include <QGraphicsItem>
#include <QPixmap>

class NormalItem : public QGraphicsItem
{
public:

    explicit NormalItem();

    //! \reimp
    virtual QRectF boundingRect () const;

    //! \reimp
    virtual void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

private:

};

#endif // NORMALITEM_HPP
