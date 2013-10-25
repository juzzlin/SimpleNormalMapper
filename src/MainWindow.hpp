// This file is part of Simple Normal Mapper.
// Copyright (C) 2013 Jussi Lind <jussi.lind@iki.fi>
//
// Simple Normal Mapper is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Simple Normal Mapper is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Simple Normal Mapper. If not, see <http://www.gnu.org/licenses/>.

#include <QMainWindow>

class Editor;
class Renderer;
class RenderPreview;
class QAction;
class QCloseEvent;
class QSlider;
class QTextEdit;
class QToolBar;
class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(Editor & editor, Renderer & renderer);

    void loadImageFile(QString fileName);

protected:

    //! \reimp
    void closeEvent(QCloseEvent * event);

private slots:

    void console(QString text);

    void openImage();

    void saveNormals();

    void showAboutQt();

    void updateScale(int value);

private:

    void initLayout();

    void initMenuBar();

    void initControlToolbar();

    Editor         & m_editor;
    RenderPreview  * m_renderPreview;
    QToolBar       * m_controlToolbar;
    QAction        * m_saveNormalsAction;
    QSlider        * m_scaleSlider;
    QTextEdit      * m_console;
    SettingsDialog * m_settingsDialog;
};
