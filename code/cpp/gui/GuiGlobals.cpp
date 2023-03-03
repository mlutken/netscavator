#include "GuiGlobals.h"

#include <iostream>
#include <QFileInfo>

#include <math/base/utils.hpp>
#include <filesystem/cpaf_special_dirs.h>
#include <gui_utils.h>
#include <interfaces/utils/utils.h>

GuiGlobals::GuiGlobals()
    : m_settings("Nitram", "SleipnerCreator")
{
    readFromSettings();
    std::cerr << "Gui settings file location: '" << m_settings.fileName().toUtf8().constData() << "'\n";
}

GuiGlobals::~GuiGlobals()
{
    writeToSettings();
}

void GuiGlobals::readFromSettings()
{
    m_settings.sync();
    m_mainWindowWidth = m_settings.value("mainWindow/width", 600).toInt();
    m_mainWindowHeight = m_settings.value("mainWindow/height", 400).toInt();
    m_mainToolBarIconSize = m_settings.value("mainToolBar/iconSize", 40).toInt();
    m_debugToolBarIconSize = m_settings.value("debugToolBar/iconSize", 40).toInt();
    m_browserZoomLevel = m_settings.value("mainBrowser/zoom", 1.0f).toFloat();
    m_mainEditorZoomLevel = m_settings.value("mainEditor/zoom", 1).toInt();
    m_phpQuickZoomLevel = m_settings.value("phpQuick/zoom", 1).toInt();
    m_linearDomTableViewFontPointSize = m_settings.value("linearDomTableView/fontPointSize", 8).toInt();
    m_phpQuickCode = m_settings.value("phpQuick/code", "<?php\n\n\n\n\n\n\n?>").toString();
}

void GuiGlobals::writeToSettings()
{
    m_settings.setValue("mainWindow/width", m_mainWindowWidth);
    m_settings.setValue("mainWindow/height", m_mainWindowHeight);
    m_settings.setValue("mainToolBar/iconSize", m_mainToolBarIconSize);
    m_settings.setValue("debugToolBar/iconSize", m_debugToolBarIconSize);
    m_settings.setValue("mainBrowser/zoom", m_browserZoomLevel);
    m_settings.setValue("mainEditor/zoom", m_mainEditorZoomLevel);
    m_settings.setValue("phpQuick/zoom", m_phpQuickZoomLevel);
    m_settings.setValue("linearDomTableView/fontPointSize", m_linearDomTableViewFontPointSize);
    m_settings.setValue("phpQuick/code", m_phpQuickCode);
    m_settings.sync();
}

float GuiGlobals::browserZoomLevel() const
{
    return cpaf::math::clamp_copy(m_browserZoomLevel, 0.2f, 100.0f);
}

void GuiGlobals::browserZoomLevelSet(float value)
{
    m_settings.setValue("mainBrowser/zoom", cpaf::math::clamp_copy(value, 0.2f, 100.0f));
    m_browserZoomLevel = value;
    writeToSettings();
}

int GuiGlobals::mainEditorZoomLevel() const
{
    return cpaf::math::clamp_copy(m_mainEditorZoomLevel, 0, 100);
}

void GuiGlobals::mainEditorZoomLevelSet(int value)
{
    m_settings.setValue("mainEditor/zoom", cpaf::math::clamp_copy(value, 0, 100));
    m_mainEditorZoomLevel = value;
    writeToSettings();
}

int GuiGlobals::phpQuickZoomLevel() const
{
    return cpaf::math::clamp_copy(m_phpQuickZoomLevel, 0, 100);
}

void GuiGlobals::phpQuickZoomLevelSet(int value)
{
    m_settings.setValue("phpQuick/zoom", cpaf::math::clamp_copy(value, 0, 100));
    m_phpQuickZoomLevel = value;
    writeToSettings();
}

QString GuiGlobals::phpQuickCode() const
{
    return m_phpQuickCode;
}

void GuiGlobals::phpQuickCodeSet(const QString& phpQuickCode)
{
    m_settings.setValue("phpQuick/code", phpQuickCode);
    m_phpQuickCode = phpQuickCode;
    writeToSettings();
}

int GuiGlobals::mainWindowWidth() const
{
    return m_mainWindowWidth;
}

void GuiGlobals::mainWindowWidthSet(int mainWindowWidth)
{
    m_settings.setValue("mainWindow/width", mainWindowWidth);
    m_mainWindowWidth = mainWindowWidth;
}

int GuiGlobals::mainWindowHeight() const
{
    return m_mainWindowHeight;
}

void GuiGlobals::mainWindowHeightSet(int mainWindowHeight)
{
    m_settings.setValue("mainWindow/height", mainWindowHeight);
    m_mainWindowHeight = mainWindowHeight;
}

int GuiGlobals::mainToolBarIconSize() const
{
    return cpaf::math::clamp_copy(m_mainToolBarIconSize, 8, 512);
}

void GuiGlobals::mainToolBarIconSizeSet(int mainToolBarIconSize)
{
    m_settings.setValue("mainToolBar/iconSize", cpaf::math::clamp_copy(mainToolBarIconSize, 8, 512));
    m_mainToolBarIconSize = mainToolBarIconSize;
    writeToSettings();
}

int GuiGlobals::debugToolBarIconSize() const
{
    return cpaf::math::clamp_copy(m_debugToolBarIconSize, 8, 512);
}

void GuiGlobals::debugToolBarIconSizeSet(int debugToolBarIconSize)
{
    m_settings.setValue("debugToolBar/iconSize", debugToolBarIconSize);
    m_debugToolBarIconSize = debugToolBarIconSize;
    writeToSettings();
}

int GuiGlobals::linearDomTableViewFontPointSize() const
{
    return m_linearDomTableViewFontPointSize;
}

void GuiGlobals::linearDomTableViewFontPointSizeSet(int linearDomTableViewFontPointSize)
{
    m_settings.setValue("linearDomTableView/fontPointSize", linearDomTableViewFontPointSize);
    m_linearDomTableViewFontPointSize = linearDomTableViewFontPointSize;
    writeToSettings();
}

QString GuiGlobals::fileOpenDir() const
{
    QString dir = m_settings.value("common/fileOpenDir").toString();
    if (dir.isEmpty()) {
        dir = crawl::toQString(cpaf::filesystem::special_dirs::home().native());
    }
    return dir;
}

void GuiGlobals::fileOpenDirSet(const QString& dir)
{
    m_settings.setValue("common/fileOpenDir", dir);
    writeToSettings();
}

const QStringList& GuiGlobals::recentCrawlers() const
{
    if (m_recentCrawlers.isEmpty()) {
        m_recentCrawlers = readRecentCrawlers();
    }
    return m_recentCrawlers;
}


QStringList GuiGlobals::readRecentCrawlers() const
{
    QStringList list;
    int size = m_settings.beginReadArray("recentCrawlers");

    for (int i = 0; i < size; ++i)
    {
        m_settings.setArrayIndex(i);
        list.append( m_settings.value("path").toString() );
    }
    m_settings.endArray();
    m_recentCrawlers = list;
    return list;
}

void GuiGlobals::writeRecentCrawlers( const QStringList& list )
{
    m_settings.beginWriteArray("recentCrawlers");

    for (int i = 0; i < list.count(); ++i)
    {
        m_settings.setArrayIndex(i);
        m_settings.setValue("path", list.at(i) );
    }
    m_settings.endArray();
    m_recentCrawlers = list;
    writeToSettings();
}

void GuiGlobals::updateRecentCrawlersList ( const QFileInfo& filePath )
{
    QStringList recentCrawlers = readRecentCrawlers();
    QString absPath = filePath.absoluteFilePath();
    recentCrawlers.removeAll( absPath );
    recentCrawlers.push_front( absPath );
    if ( recentCrawlers.count() > 15 ) {
        recentCrawlers.pop_back();
    }
    writeRecentCrawlers( recentCrawlers );
}




