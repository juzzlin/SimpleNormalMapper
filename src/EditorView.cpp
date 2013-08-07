#include "EditorView.hpp"
#include "Editor.hpp"
#include "EditorScene.hpp"
#include "NormalItem.hpp"

#include <QMouseEvent>

EditorView::EditorView(Editor & editor, QWidget * parent)
    : QGraphicsView(&editor.scene(), parent)
    , m_editor(editor)
{
    setBackgroundBrush(QBrush(QColor(0, 0, 0)));
}

void EditorView::mouseMoveEvent(QMouseEvent * event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void EditorView::mousePressEvent(QMouseEvent * event)
{
    m_clickedPos      = event->pos();
    m_clickedScenePos = mapToScene(m_clickedPos);

    if (m_editor.mode() == Editor::InsertNormals)
    {
        QGraphicsItem * normalItem = new NormalItem(NormalItem::Head);
        m_editor.scene().addItem(normalItem);
        normalItem->setPos(m_clickedScenePos);
    }

    QGraphicsView::mousePressEvent(event);
}

void EditorView::mouseReleaseEvent(QMouseEvent * event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void EditorView::keyPressEvent(QKeyEvent * event)
{
    QGraphicsView::keyPressEvent(event);
}
