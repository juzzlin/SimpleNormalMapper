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

#include "MainWindow.hpp"
#include "Editor.hpp"
#include "EditorView.hpp"
#include "IO.hpp"
#include "RenderDialog.hpp"
#include "Settings.hpp"
#include "SettingsDialog.hpp"

#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QDateTime>
#include <QDebug>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QSizePolicy>
#include <QSlider>
#include <QSplitter>
#include <QStatusBar>
#include <QTextEdit>
#include <QVBoxLayout>

namespace
{
    const char       * SOFTWARE_NAME           = "Simple Normal Mapper";
    const char       * SOFTWARE_VERSION        = "0.0.0";
    const int          MARGIN                  = 0;
    const unsigned int MIN_ZOOM                = 0;
    const unsigned int MAX_ZOOM                = 400;
    const unsigned int INI_ZOOM                = 100;
    const int          CONSOLE_HEIGHT          = 64;
}

MainWindow::MainWindow(Editor & editor)
    : m_editor(editor)
    , m_insertNormalsAction(nullptr)
    , m_deleteNormalsAction(nullptr)
    , m_moveNormalsAction(nullptr)
    , m_saveNormalsAction(nullptr)
    , m_scaleSlider(new QSlider(Qt::Horizontal, this))
    , m_console(new QTextEdit(this))
    , m_settingsDialog(new SettingsDialog(this))
{
    setWindowTitle(QString(SOFTWARE_NAME) + " " + SOFTWARE_VERSION);

    QStatusBar * statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    resize(Settings::loadWindowSize());

    // Try to center the window.
    QRect geometry(QApplication::desktop()->availableGeometry());
    move(geometry.width() / 2 - width() / 2,
        geometry.height() / 2 - height() / 2);

    initMenuBar();
    initLayout();

    connect(&editor.view(), SIGNAL(normalInserted(bool)), m_openRenderDialogAction, SLOT(setEnabled(bool)));
    connect(&editor.view(), SIGNAL(normalInserted(bool)), m_deleteNormalsAction, SLOT(setEnabled(bool)));
    connect(&editor.view(), SIGNAL(normalInserted(bool)), m_moveNormalsAction, SLOT(setEnabled(bool)));
    connect(&editor.view(), SIGNAL(normalInserted(bool)), m_saveNormalsAction, SLOT(setEnabled(bool)));
}

void MainWindow::initMenuBar()
{
    QMenuBar * menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu * fileMenu = new QMenu(tr("&File"), this);
    menuBar->addMenu(fileMenu);

    QAction * openImageAction = new QAction(tr("&Open new image.."), this);
    connect(openImageAction, SIGNAL(triggered()), this, SLOT(openImage()));
    fileMenu->addAction(openImageAction);

    QAction * openNormalsAction = new QAction(tr("&Open normals.."), this);
    connect(openNormalsAction, SIGNAL(triggered()), this, SLOT(openNormals()));
    fileMenu->addAction(openNormalsAction);

    m_saveNormalsAction = new QAction(tr("&Save normals.."), this);
    connect(m_saveNormalsAction, SIGNAL(triggered()), this, SLOT(saveNormals()));
    m_saveNormalsAction->setEnabled(false);
    fileMenu->addAction(m_saveNormalsAction);

    QMenu * editMenu = new QMenu(tr("&Edit"), this);
    menuBar->addMenu(editMenu);

    m_insertNormalsAction = new QAction(tr("&Insert normals"), this);
    m_insertNormalsAction->setEnabled(false);
    connect(m_insertNormalsAction, SIGNAL(triggered()), this, SLOT(insertNormals()));
    editMenu->addAction(m_insertNormalsAction);

    m_moveNormalsAction = new QAction(tr("&Move/adjust normals"), this);
    m_moveNormalsAction->setEnabled(false);
    connect(m_moveNormalsAction, SIGNAL(triggered()), this, SLOT(moveNormals()));
    editMenu->addAction(m_moveNormalsAction);

    m_deleteNormalsAction = new QAction(tr("&Delete normals"), this);
    m_deleteNormalsAction->setEnabled(false);
    connect(m_deleteNormalsAction, SIGNAL(triggered()), this, SLOT(deleteNormals()));
    editMenu->addAction(m_deleteNormalsAction);
    editMenu->addSeparator();

    m_openRenderDialogAction = new QAction(tr("&Render normal map.."), this);
    m_openRenderDialogAction->setEnabled(false);
    connect(m_openRenderDialogAction, SIGNAL(triggered()), this, SLOT(openRenderDialog()));
    editMenu->addAction(m_openRenderDialogAction);
    editMenu->addSeparator();

    QAction * settingsAct = new QAction(tr("&Settings.."), this);
    editMenu->addAction(settingsAct);
    connect(settingsAct, SIGNAL(triggered()), m_settingsDialog, SLOT(exec()));

    QMenu * helpMenu = new QMenu(tr("&Help"), this);
    menuBar->addMenu(helpMenu);

    // Add "about Qt"-action
    QAction * aboutQtAct = new QAction(tr("About &Qt"), this);
    helpMenu->addAction(aboutQtAct);
    connect(aboutQtAct, &QAction::triggered, [this]{QMessageBox::aboutQt(this, tr("About Qt"));});
}

void MainWindow::initLayout()
{
    // Create a splitter
    QSplitter * splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Vertical);

    // Create layouts for slider, view and toolbar
    QVBoxLayout * centralLayout = new QVBoxLayout;
    centralLayout->addWidget(qobject_cast<QWidget *>(&m_editor.view()));

    // Add zoom slider to the layout
    m_scaleSlider->setRange(MIN_ZOOM, MAX_ZOOM);
    m_scaleSlider->setValue(INI_ZOOM);
    m_scaleSlider->setTracking(false);
    m_scaleSlider->setTickInterval(10);
    m_scaleSlider->setTickPosition(QSlider::TicksBelow);
    connect(m_scaleSlider, SIGNAL(valueChanged(int)), this, SLOT(updateScale(int)));
    QHBoxLayout * sliderLayout = new QHBoxLayout;
    sliderLayout->addWidget(new QLabel(tr("Scale:")));
    sliderLayout->addWidget(m_scaleSlider);
    centralLayout->addLayout(sliderLayout);

    // Add console to the splitter and splitter to the layout
    m_console->setReadOnly(true);
    m_console->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    m_console->resize(m_console->width(), 50);
    QWidget * dummy = new QWidget(this);
    splitter->addWidget(dummy);
    dummy->setLayout(centralLayout);
    dummy->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    splitter->addWidget(m_console);

    // Set contents margins so that they look nice
    splitter->setContentsMargins(
        centralLayout->contentsMargins().left(),
        0,
        centralLayout->contentsMargins().right(),
        centralLayout->contentsMargins().bottom());

    centralLayout->setContentsMargins(
        0,
        centralLayout->contentsMargins().top(),
        0,
        centralLayout->contentsMargins().bottom());

    // Set splitter as the central widget
    setCentralWidget(splitter);

    QList<int> sizes;
    sizes << height() - CONSOLE_HEIGHT << CONSOLE_HEIGHT;
    splitter->setSizes(sizes);
}

void MainWindow::openImage()
{
    const QString path = Settings::loadRecentImagePath();
    const QString fileName = QFileDialog::getOpenFileName(
        this, tr("Open an image"), path, tr("All files (*.*);;JPEG (*.jpg *.jpeg);;PNG (*.png)"));
    loadImageFile(fileName);
    Settings::saveRecentImagePath(fileName);
}

void MainWindow::openNormals()
{
    const QString path = Settings::loadRecentNormalsPath();
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Open normals"), path, tr("SNM (*.snm)"));
    m_editor.io().openNormals(fileName);
    Settings::saveRecentNormalsPath(path);
}

void MainWindow::saveNormals()
{
    const QString path = Settings::loadRecentNormalsPath();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save normals"), path, tr("SNM (*.snm)"));
    if (!fileName.endsWith(".snm"))
    {
        fileName.append(".snm");
    }

    m_editor.io().saveNormals(fileName);
    Settings::saveRecentNormalsPath(fileName);
}

void MainWindow::loadImageFile(QString fileName)
{
    QImage image;
    if (image.load(fileName))
    {
        statusBar()->showMessage(tr("Ready."));

        m_editor.clear();
        m_editor.setImage(image);

        m_insertNormalsAction->setEnabled(true);

        console("Succesfully loaded '" + fileName + "'.");
    }
    else
    {
        QMessageBox::critical(this, tr("Load image"), tr("Failed to load ") + fileName);
    }
}

void MainWindow::insertNormals()
{
    m_editor.setMode(Editor::InsertNormals);
    statusBar()->showMessage(tr("Insert normals.."));
}

void MainWindow::deleteNormals()
{
    m_editor.setMode(Editor::DeleteNormals);
    statusBar()->showMessage(tr("Delete normals.."));
}

void MainWindow::moveNormals()
{
    m_editor.setMode(Editor::MoveNormals);
    statusBar()->showMessage(tr("Move normals.."));
}

void MainWindow::openRenderDialog()
{
    RenderDialog dlg(m_editor, this);
    dlg.exec();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    Settings::saveWindowSize(size());
    event->accept();
}

void MainWindow::updateScale(int value)
{
    qreal scale = static_cast<qreal>(value) / 100;

    QTransform transform;
    transform.scale(scale, scale);
    m_editor.view().setTransform(transform);

    console(QString("Scale set to %1%").arg(value));
}

void MainWindow::console(QString text)
{
    QDateTime date = QDateTime::currentDateTime();
    m_console->append(QString("(") + date.toString("hh:mm:ss") + "): " + text);
}
