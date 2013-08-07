#include <QMainWindow>

class Editor;
class QAction;
class QCloseEvent;
class QSlider;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(Editor & editor);

protected:

    //! \reimp
    void closeEvent(QCloseEvent * event);

private slots:

    void openImage();

    void insertNormals();

    void deleteNormals();

    void moveNormals();

    void console(QString text);

    void updateScale(int value);

private:

    void initLayout();

    void initMenuBar();

    Editor & m_editor;

    QAction   * m_insertNormalsAction;
    QAction   * m_deleteNormalsAction;
    QAction   * m_moveNormalsAction;
    QSlider   * m_scaleSlider;
    QTextEdit * m_console;
};
