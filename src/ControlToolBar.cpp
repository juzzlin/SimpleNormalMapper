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

#include "ControlToolBar.hpp"
#include "Editor.hpp"
#include "Renderer.hpp"
#include "RenderPreview.hpp"
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

ControlToolBar::ControlToolBar(RenderPreview * renderPreview, Renderer& renderer, QWidget* parent)
    : QToolBar("Controls", parent)
    , m_currentAmplitude(1.0)
    , m_currentRadius(1)
    , m_previewCheckBox(nullptr)
    , m_radiusLabel(nullptr)
    , m_amplitudeLabel(nullptr)
    , m_renderPreview(renderPreview)
    , m_renderer(renderer)
{
    initToolbar();
}

ControlToolBar::~ControlToolBar()
{
}

void ControlToolBar::radiusChanged(int radius)
{
    if (m_currentRadius != radius)
    {
        m_currentRadius = radius;
        updateRadiusLabel();

        m_renderer.setRadius(radius);

        if (m_previewCheckBox->checkState() == Qt::Checked)
        {
            m_renderPreview->render();
        }
    }
}

void ControlToolBar::previewChanged(bool preview)
{
    if (preview)
    {
        m_renderPreview->render();
    }
}

void ControlToolBar::amplitudeChanged(int amplitude)
{
    if (m_currentAmplitude != amplitude)
    {
        m_currentAmplitude = 0.01 * amplitude;
        updateAmplitudeLabel();

        // Updates height map
        m_renderer.setAmplitude(m_currentAmplitude);

        if (m_previewCheckBox->checkState() == Qt::Checked)
        {
            m_renderPreview->render();
        }
    }
}

void ControlToolBar::initToolbar()
{
    QSlider * radiusSlider = new QSlider(Qt::Horizontal, this);
    addWidget(radiusSlider);
    m_radiusLabel = new QLabel(this);
    addWidget(m_radiusLabel);
    radiusSlider->setRange(1, 30);
    radiusSlider->setValue(1);
    updateRadiusLabel();
    connect(radiusSlider, SIGNAL(valueChanged(int)), this, SLOT(radiusChanged(int)));

    addSeparator();

    QSlider * amplitudeSlider = new QSlider(Qt::Horizontal, this);
    addWidget(amplitudeSlider);
    m_amplitudeLabel = new QLabel(this);
    addWidget(m_amplitudeLabel);
    amplitudeSlider->setRange(0, 500);
    amplitudeSlider->setValue(10);
    updateAmplitudeLabel();
    connect(amplitudeSlider, SIGNAL(valueChanged(int)), this, SLOT(amplitudeChanged(int)));

    addSeparator();

    m_previewCheckBox = new QCheckBox("Live preview");
    m_previewCheckBox->setChecked(false);
    connect(m_previewCheckBox, SIGNAL(toggled(bool)), this, SLOT(previewChanged(bool)));
    addWidget(m_previewCheckBox);

    addSeparator();

    QPushButton * render = new QPushButton(tr("&Render"), this);
    connect(render, SIGNAL(clicked()), m_renderPreview, SLOT(render()));
    addWidget(render);

    QPushButton * save = new QPushButton(tr("&Save"), this);
    connect(save, SIGNAL(clicked()), m_renderPreview, SLOT(save()));
    addWidget(save);
}

void ControlToolBar::updateRadiusLabel()
{
    m_radiusLabel->setText(QString("Sampling radius: %1").arg(m_currentRadius));
}

void ControlToolBar::updateAmplitudeLabel()
{
    m_amplitudeLabel->setText(QString("Height amplitude: %1").arg(m_currentAmplitude));
}
