// This file is part of Simple Normal Mapper.
// Copyright (c) 2013 Simple Normal Mapper developers.
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

#include "AboutDlg.hpp"
#include "Config.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>

AboutDlg::AboutDlg(QWidget * parent)
: QDialog(parent)
{
    setWindowTitle(tr("About") + " " + Config::name());
    initWidgets();
}

void AboutDlg::initWidgets()
{
    QVBoxLayout * vLayout     = new QVBoxLayout(this);
    QHBoxLayout * hLayout     = new QHBoxLayout();
    QLabel      * pixmapLabel = new QLabel(this);

    pixmapLabel->setPixmap(QPixmap(":/about.png").scaledToWidth(256));
    hLayout->addWidget(pixmapLabel);

    QLabel * infoLabel = new QLabel(this);
    infoLabel->setText(QString("<h2>") + Config::name() + " v" + Config::version() + "</h2>"
                       + "<p>" + Config::name() + " is licenced under GNU GPLv3.</p>"
                       + "<p>Copyright (c) 2013 " + Config::name() + " developers.</p>"
                       + "<a href='https://github.com/juzzlin/SimpleNormalMapper'>"
                       + "https://github.com/juzzlin/SimpleNormalMapper</a>");

    hLayout->addWidget(infoLabel);
    vLayout->addLayout(hLayout);
    QHBoxLayout * buttonLayout = new QHBoxLayout();
    QPushButton * button = new QPushButton("&Ok", this);
    connect(button, SIGNAL(clicked()), this, SLOT(accept()));
    buttonLayout->addWidget(button);
    buttonLayout->insertStretch(0);
    vLayout->addLayout(buttonLayout);
}
