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

#include "Renderer.hpp"

#include <QDebug>

Renderer::Renderer()
{
}

// Note that currently width and height must match the original width and height,
// because it's assumed in the normal coordinates.
QPixmap Renderer::render(int width, int height, Renderer::NormalList normals, bool qubic)
{
    QPixmap result(width, height);

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            for (Renderer::NormalPtr normal : normals)
            {
                qDebug() << normal->location();
            }
        }
    }

    return result;
}
