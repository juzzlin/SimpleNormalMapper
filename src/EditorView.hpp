#include <QGraphicsView>

class EditorScene;

class EditorView : public QGraphicsView
{
public:

    EditorView(EditorScene * scene, QWidget * parent = nullptr);

private:
};
