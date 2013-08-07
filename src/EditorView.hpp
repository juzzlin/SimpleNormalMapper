#include <QGraphicsView>

class Editor;

class EditorView : public QGraphicsView
{
public:

    EditorView(Editor & editor, QWidget * parent = nullptr);

protected:

    //! \reimp
    void mouseMoveEvent(QMouseEvent * event);

    //! \reimp
    void mousePressEvent(QMouseEvent * event);

    //! \reimp
    void mouseReleaseEvent(QMouseEvent * event);

    //! \reimp
    void keyPressEvent(QKeyEvent * event);

private:

    Editor & m_editor;
    QPoint   m_clickedPos;
    QPointF  m_clickedScenePos;
};
