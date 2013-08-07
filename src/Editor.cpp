#include "Editor.hpp"
#include "EditorScene.hpp"
#include "EditorView.hpp"
#include "ImageItem.hpp"
#include "MainWindow.hpp"

#include <QGraphicsItem>
#include <QDebug>

#include <cassert>

Editor::Editor(const std::vector<std::string> & args)
    : m_scene(new EditorScene(this))
    , m_view(new EditorView(*this))
    , m_window(new MainWindow(*this))
    , m_mode(Editor::None)
{
    m_window->show();
}

EditorView & Editor::view() const
{
    assert(m_view);
    return *m_view;
}

EditorScene & Editor::scene() const
{
    assert(m_scene);
    return *m_scene;
}

void Editor::setMode(Editor::Mode mode)
{
    m_mode = mode;
}

Editor::Mode Editor::mode() const
{
    return m_mode;
}

void Editor::setImage(QImage image)
{
    QPixmap pixmap;
    pixmap.convertFromImage(image);

    m_view->ensureVisible(0, 0, 0, 0);
    m_scene->setSceneRect(0, 0, pixmap.width(), pixmap.height());
    m_scene->clear();

    QGraphicsItem * imageItem = new ImageItem(pixmap);
    m_scene->addItem(imageItem);
    imageItem->setPos(pixmap.width() / 2, pixmap.height() / 2);
}

Editor::~Editor()
{
    delete m_window;
}
