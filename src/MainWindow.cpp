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

#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QDateTime>
#include <QDebug>
#include <QHBoxLayout>
#include <QStandardPaths>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QImage>
#include <QLabel>
#include <QSettings>
#include <QSizePolicy>
#include <QSlider>
#include <QSplitter>
#include <QStatusBar>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

namespace
{
    const char       * SOFTWARE_NAME           = "Simple Normal Mapper";
    const char       * SOFTWARE_VERSION        = "0.0.0";
    const char       * QSETTINGS_COMPANY_NAME  = "snm";
    const char       * QSETTINGS_SOFTWARE_NAME = "snm";
    const char       * SETTINGS_GROUP          = "MainWindow";
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
    , m_scaleSlider(new QSlider(Qt::Horizontal, this))
    , m_console(new QTextEdit(this))
{
    setWindowTitle(QString(SOFTWARE_NAME) + " " + SOFTWARE_VERSION);

    QStatusBar * statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    QSettings settings(QSETTINGS_COMPANY_NAME, QSETTINGS_SOFTWARE_NAME);

    // Read dialog size data
    settings.beginGroup(SETTINGS_GROUP);
    resize(settings.value("size", QSize(640, 480)).toSize());
    settings.endGroup();

    // Try to center the window.
    QRect geometry(QApplication::desktop()->availableGeometry());
    move(geometry.width() / 2 - width() / 2,
        geometry.height() / 2 - height() / 2);

    initMenuBar();
    initLayout();
}

void MainWindow::initMenuBar()
{
    QMenuBar * menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu * fileMenu = new QMenu(tr("&File"), this);
    menuBar->addMenu(fileMenu);

    QAction * fileOpenAction = new QAction(tr("&Open image.."), this);
    connect(fileOpenAction, SIGNAL(triggered()), this, SLOT(openImage()));
    fileMenu->addAction(fileOpenAction);

    QMenu * editMenu = new QMenu(tr("&Edit"), this);
    menuBar->addMenu(editMenu);

    m_insertNormalsAction = new QAction(tr("&Insert normals.."), this);
    m_insertNormalsAction->setEnabled(false);
    connect(m_insertNormalsAction, SIGNAL(triggered()), this, SLOT(insertNormals()));
    editMenu->addAction(m_insertNormalsAction);

    m_moveNormalsAction = new QAction(tr("&Move normals.."), this);
    m_moveNormalsAction->setEnabled(false);
    connect(m_moveNormalsAction, SIGNAL(triggered()), this, SLOT(moveNormals()));
    editMenu->addAction(m_moveNormalsAction);

    m_deleteNormalsAction = new QAction(tr("&Delete normals.."), this);
    m_deleteNormalsAction->setEnabled(false);
    connect(m_deleteNormalsAction, SIGNAL(triggered()), this, SLOT(deleteNormals()));
    editMenu->addAction(m_deleteNormalsAction);
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
    // Load recent path
    QSettings settings(QSETTINGS_COMPANY_NAME, QSETTINGS_SOFTWARE_NAME);

    settings.beginGroup(SETTINGS_GROUP);
    QString path = settings.value("recentPath",
    QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).toString();
    settings.endGroup();

    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Open an image"), path, tr("All files (*.*);;JPEG (*.jpg *.jpeg);;PNG (*.png)"));

    QImage image;
    if (image.load(fileName))
    {
        m_editor.clear();
        m_editor.setImage(image);

        m_insertNormalsAction->setEnabled(true);
        m_deleteNormalsAction->setEnabled(true);
        m_moveNormalsAction->setEnabled(true);

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
}

void MainWindow::deleteNormals()
{
    m_editor.setMode(Editor::DeleteNormals);
}

void MainWindow::moveNormals()
{
    m_editor.setMode(Editor::MoveNormals);
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    // Open settings file
    QSettings settings(QSETTINGS_COMPANY_NAME, QSETTINGS_SOFTWARE_NAME);

    // Save window size
    settings.beginGroup(SETTINGS_GROUP);
    settings.setValue("size", size());
    settings.endGroup();

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
