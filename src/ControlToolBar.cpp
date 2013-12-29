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

#include "ControlToolBar.hpp"
#include "Editor.hpp"
#include "RenderPreview.hpp"
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

ControlToolBar::ControlToolBar(RenderPreview * renderPreview, QWidget* parent)
    : QToolBar("Controls", parent)
    , m_currentAmplitude(1.0)
    , m_currentRadius(1)
    , m_previewCheckBox(nullptr)
    , m_radiusSlider(nullptr)
    , m_amplitudeSlider(nullptr)
    , m_renderButton(nullptr)
    , m_renderPreview(renderPreview)
{
    initToolbar();

    m_renderTimer.setInterval(250);
    m_renderTimer.setSingleShot(true);
    connect(&m_renderTimer, SIGNAL(timeout()), m_renderPreview, SLOT(render()));
}

ControlToolBar::~ControlToolBar()
{
}

void ControlToolBar::changeRadius(int radius)
{
    m_currentRadius = radius * 0.1f;
    updateRadiusToolTip();

    emit radiusChanged(m_currentRadius);

    if (m_previewCheckBox->checkState() == Qt::Checked)
    {
        m_renderTimer.start();
    }
}

void ControlToolBar::changePreview(bool preview)
{
    if (preview)
    {
        m_renderTimer.start();
    }
}

void ControlToolBar::changeAmplitude(int amplitude)
{
    m_currentAmplitude = amplitude * 0.25f;
    updateAmplitudeToolTip();

    emit amplitudeChanged(m_currentAmplitude);

    if (m_previewCheckBox->checkState() == Qt::Checked)
    {
        m_renderTimer.start();
    }
}

void ControlToolBar::initToolbar()
{
    addWidget(new QLabel("Sampling radius", this));
    m_radiusSlider = new QSlider(Qt::Horizontal, this);
    addWidget(m_radiusSlider);
    m_radiusSlider->setRange(1, 100);
    m_radiusSlider->setValue(1);
    m_radiusSlider->setEnabled(false);
    updateRadiusToolTip();
    connect(m_radiusSlider, SIGNAL(valueChanged(int)), this, SLOT(changeRadius(int)));
    addSeparator();

    addWidget(new QLabel("Height amplitude", this));
    m_amplitudeSlider = new QSlider(Qt::Horizontal, this);
    addWidget(m_amplitudeSlider);
    m_amplitudeSlider->setRange(0, 100);
    m_amplitudeSlider->setValue(10);
    m_amplitudeSlider->setEnabled(false);
    updateAmplitudeToolTip();
    connect(m_amplitudeSlider, SIGNAL(valueChanged(int)), this, SLOT(changeAmplitude(int)));
    addSeparator();

    m_previewCheckBox = new QCheckBox("Live preview");
    m_previewCheckBox->setChecked(false);
    m_previewCheckBox->setEnabled(false);
    connect(m_previewCheckBox, SIGNAL(toggled(bool)), this, SLOT(changePreview(bool)));
    addWidget(m_previewCheckBox);
    addSeparator();

    m_renderButton = new QPushButton(tr("&Render"), this);
    connect(m_renderButton, SIGNAL(clicked()), m_renderPreview, SLOT(render()));
    m_renderButton->setEnabled(false);
    addWidget(m_renderButton);
}

void ControlToolBar::enableControls()
{
    m_radiusSlider->setEnabled(true);
    m_amplitudeSlider->setEnabled(true);
    m_previewCheckBox->setEnabled(true);
    m_renderButton->setEnabled(true);
}

void ControlToolBar::updateRadiusToolTip()
{
    m_radiusSlider->setToolTip(QString::number(m_currentRadius));
}

void ControlToolBar::updateAmplitudeToolTip()
{
    m_amplitudeSlider->setToolTip(QString::number(m_currentAmplitude));
}
