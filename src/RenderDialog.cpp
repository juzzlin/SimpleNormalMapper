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

#include "RenderDialog.hpp"
#include "Settings.hpp"

#include <QFileDialog>
#include <QLabel>
#include <QPixmap>
#include <QProgressBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

RenderDialog::RenderDialog(QWidget * parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Render"));

    initLayout();
}

void RenderDialog::initLayout()
{
    QVBoxLayout * vLayout = new QVBoxLayout;
    QLabel * label = new QLabel(this);
    label->setPixmap(QPixmap(640, 400));
    vLayout->addWidget(label);
    QProgressBar * progress = new QProgressBar(this);
    progress->setRange(0, 100);
    progress->setValue(0);
    vLayout->addWidget(progress);

    QHBoxLayout * hLayout = new QHBoxLayout;
    QPushButton * render = new QPushButton(tr("&Render"), this);
    connect(render, SIGNAL(clicked()), this, SLOT(render()));
    hLayout->addWidget(render);
    QPushButton * save = new QPushButton(tr("&Save"), this);
    connect(save, SIGNAL(clicked()), this, SLOT(save()));
    hLayout->addWidget(save);
    QPushButton * close = new QPushButton(tr("&Close"), this);
    connect(close, SIGNAL(clicked()), this, SLOT(close()));
    hLayout->addWidget(close);

    vLayout->addLayout(hLayout);
    setLayout(vLayout);
}

void RenderDialog::render()
{
    // TODO
}

void RenderDialog::save()
{
    const QString path = Settings::loadRecentResultPath();
    const QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save the normal map image"), path, tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));
    Settings::saveRecentResultPath(fileName);
}
