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

#include "Settings.hpp"

#include <QSettings>
#ifdef USE_QT5
#include <QStandardPaths>
#else
#include <QDesktopServices>
#endif

namespace
{
    const char * QSETTINGS_COMPANY_NAME     = "snm";
    const char * QSETTINGS_SOFTWARE_NAME    = "snm";
    const char * SETTINGS_GROUP             = "Global";
    const char * SETTINGS_GROUP_MAIN_WINDOW = "MainWindow";
}

QString homeLocation()
{
#ifdef USE_QT5
    return QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
#else
    return QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
#endif

}

QString Settings::loadRecentResultPath()
{
    QSettings settings(QSETTINGS_COMPANY_NAME, QSETTINGS_SOFTWARE_NAME);
    settings.beginGroup(SETTINGS_GROUP);
    const QString path = settings.value("recentResultPath", homeLocation()).toString();
    settings.endGroup();
    return path;
}

void Settings::saveRecentResultPath(QString path)
{
    QSettings settings(QSETTINGS_COMPANY_NAME, QSETTINGS_SOFTWARE_NAME);
    settings.beginGroup(SETTINGS_GROUP);
    settings.setValue("recentResultPath", path);
    settings.endGroup();
}

QString Settings::loadRecentImagePath()
{
    QSettings settings(QSETTINGS_COMPANY_NAME, QSETTINGS_SOFTWARE_NAME);
    settings.beginGroup(SETTINGS_GROUP);
    const QString path = settings.value("recentImagePath", homeLocation()).toString();
    settings.endGroup();
    return path;
}

void Settings::saveRecentImagePath(QString path)
{
    QSettings settings(QSETTINGS_COMPANY_NAME, QSETTINGS_SOFTWARE_NAME);
    settings.beginGroup(SETTINGS_GROUP);
    settings.setValue("recentImagePath", path);
    settings.endGroup();
}

QString Settings::loadRecentNormalsPath()
{
    QSettings settings(QSETTINGS_COMPANY_NAME, QSETTINGS_SOFTWARE_NAME);
    settings.beginGroup(SETTINGS_GROUP);
    const QString path = settings.value("recentNormalsPath", homeLocation()).toString();
    settings.endGroup();
    return path;
}

void Settings::saveRecentNormalsPath(QString path)
{
    QSettings settings(QSETTINGS_COMPANY_NAME, QSETTINGS_SOFTWARE_NAME);
    settings.beginGroup(SETTINGS_GROUP);
    settings.setValue("recentNormalsPath", path);
    settings.endGroup();
}

QSize Settings::loadWindowSize()
{
    QSettings settings(QSETTINGS_COMPANY_NAME, QSETTINGS_SOFTWARE_NAME);
    settings.beginGroup(SETTINGS_GROUP_MAIN_WINDOW);
    const QSize size(settings.value("size", QSize(640, 480)).toSize());
    settings.endGroup();
    return size;
}

void Settings::saveWindowSize(QSize size)
{
    QSettings settings(QSETTINGS_COMPANY_NAME, QSETTINGS_SOFTWARE_NAME);
    settings.beginGroup(SETTINGS_GROUP_MAIN_WINDOW);
    settings.setValue("size", size);
    settings.endGroup();
}
