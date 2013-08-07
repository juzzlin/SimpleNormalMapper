#ifndef NORMALITEM_HPP
#define NORMALITEM_HPP

#include <QGraphicsItem>

class NormalItem : public QGraphicsItem
{
public:

    enum Type {Head, Tail};

    explicit NormalItem(Type type = Head);

    //! \reimp
    virtual QRectF boundingRect () const;

    //! \reimp
    virtual void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

private:

    NormalItem::Type m_type;
};

#endif // NORMALITEM_HPP
