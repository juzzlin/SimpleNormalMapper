#include "EditorView.hpp"
#include "EditorScene.hpp"

EditorView::EditorView(EditorScene * scene, QWidget * parent)
    : QGraphicsView(scene, parent)
{
    setBackgroundBrush(QBrush(QColor(0, 0, 0)));
}
