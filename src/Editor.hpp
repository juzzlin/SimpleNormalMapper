#include <QObject>
#include <QImage>

#include <string>
#include <vector>

class EditorScene;
class EditorView;
class MainWindow;

class Editor : public QObject
{
    Q_OBJECT

public:

    enum Mode
    {
        None,
        InsertNormals,
        MoveNormals,
        DeleteNormals
    };

    Editor(const std::vector<std::string> & args);
    virtual ~Editor();

    void setMode(Editor::Mode mode);

    Editor::Mode mode() const;

    void setImage(QImage image);

    EditorView & view() const;

    EditorScene & scene() const;

private:

    EditorScene * m_scene;
    EditorView  * m_view;
    MainWindow  * m_window;
    QImage        m_image;
    Mode          m_mode;
};
