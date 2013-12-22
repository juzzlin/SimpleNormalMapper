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
    , m_radiusSlider(nullptr)
    , m_amplitudeSlider(nullptr)
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
        updateRadiusToolTip();

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
        updateAmplitudeToolTip();

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
    addWidget(new QLabel("Sampling radius", this));
    m_radiusSlider = new QSlider(Qt::Horizontal, this);
    addWidget(m_radiusSlider);
    m_radiusSlider->setRange(1, 30);
    m_radiusSlider->setValue(1);
    updateRadiusToolTip();
    connect(m_radiusSlider, SIGNAL(valueChanged(int)), this, SLOT(radiusChanged(int)));
    addSeparator();

    addWidget(new QLabel("Height amplitude", this));
    m_amplitudeSlider = new QSlider(Qt::Horizontal, this);
    addWidget(m_amplitudeSlider);
    m_amplitudeSlider->setRange(0, 500);
    m_amplitudeSlider->setValue(10);
    updateAmplitudeToolTip();
    connect(m_amplitudeSlider, SIGNAL(valueChanged(int)), this, SLOT(amplitudeChanged(int)));
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

void ControlToolBar::updateRadiusToolTip()
{
    m_radiusSlider->setToolTip(QString::number(m_currentRadius));
}

void ControlToolBar::updateAmplitudeToolTip()
{
    m_amplitudeSlider->setToolTip(QString::number(m_currentAmplitude));
}
