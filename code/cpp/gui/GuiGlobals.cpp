#include "GuiGlobals.h"

#include <QFileInfo>

#include <math/base/utils.hpp>
#include <gui_utils.h>

GuiGlobals::GuiGlobals()
{
    readFromSettings();
}

GuiGlobals::~GuiGlobals()
{
    writeToSettings();
}

void GuiGlobals::readFromSettings()
{
    QSettings settings("Nitram", "SleipnerCreator");
    readRecentCrawlers ( recentCrawlers );
    m_mainWindowWidth = settings.value("mainWindow/width", 600).toInt();
    m_mainWindowHeight = settings.value("mainWindow/height", 400).toInt();
    m_mainToolBarIconSize = settings.value("mainToolBar/iconSize", 40).toInt();
    m_debugToolBarIconSize = settings.value("debugToolBar/iconSize", 40).toInt();
    m_browserZoomLevel = settings.value("mainBrowser/zoom", 1.0f).toFloat();
    m_mainEditorZoomLevel = settings.value("mainEditor/zoom", 1).toInt();
    m_phpQuickZoomLevel = settings.value("phpQuick/zoom", 1).toInt();
    m_linearDomTableViewFontPointSize = settings.value("linearDomTableView/fontPointSize", 8).toInt();
    m_phpQuickCode = settings.value("phpQuick/code", "<?php\n\n\n\n\n\n\n?>").toString();
}

void GuiGlobals::writeToSettings()
{
    QSettings settings("Nitram", "SleipnerCreator");
    writeRecentCrawlers( recentCrawlers );
    settings.setValue("mainWindow/width", m_mainWindowWidth);
    settings.setValue("mainWindow/height", m_mainWindowHeight);
    settings.setValue("mainToolBar/iconSize", m_mainToolBarIconSize);
    settings.setValue("debugToolBar/iconSize", m_debugToolBarIconSize);
    settings.setValue("mainBrowser/zoom", m_browserZoomLevel);
    settings.setValue("mainEditor/zoom", m_mainEditorZoomLevel);
    settings.setValue("phpQuick/zoom", m_phpQuickZoomLevel);
    settings.setValue("linearDomTableView/fontPointSize", m_linearDomTableViewFontPointSize);
    settings.setValue("phpQuick/code", m_phpQuickCode);
}

float GuiGlobals::browserZoomLevel() const
{
    return cpaf::math::clamp_copy(m_browserZoomLevel, 0.2f, 100.0f);
}

void GuiGlobals::browserZoomLevelSet(float value)
{
    m_settings.setValue("mainBrowser/zoom", cpaf::math::clamp_copy(value, 0.2f, 100.0f));
    m_browserZoomLevel = value;
}

int GuiGlobals::mainEditorZoomLevel() const
{
    return cpaf::math::clamp_copy(m_mainEditorZoomLevel, 0, 100);
}

void GuiGlobals::mainEditorZoomLevelSet(int value)
{
    m_settings.setValue("mainEditor/zoom", cpaf::math::clamp_copy(value, 0, 100));
    m_mainEditorZoomLevel = value;
}

int GuiGlobals::phpQuickZoomLevel() const
{
    return cpaf::math::clamp_copy(m_phpQuickZoomLevel, 0, 100);
}

void GuiGlobals::phpQuickZoomLevelSet(int value)
{
    m_settings.setValue("phpQuick/zoom", cpaf::math::clamp_copy(value, 0, 100));
    m_phpQuickZoomLevel = value;
}
QString GuiGlobals::phpQuickCode() const
{
    return m_phpQuickCode;
}

void GuiGlobals::phpQuickCodeSet(const QString& phpQuickCode)
{
    m_settings.setValue("phpQuick/code", phpQuickCode);
    m_phpQuickCode = phpQuickCode;
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
}

int GuiGlobals::debugToolBarIconSize() const
{
    return cpaf::math::clamp_copy(m_debugToolBarIconSize, 8, 512);
}

void GuiGlobals::debugToolBarIconSizeSet(int debugToolBarIconSize)
{
    m_settings.setValue("debugToolBar/iconSize", debugToolBarIconSize);
    m_debugToolBarIconSize = debugToolBarIconSize;
}

int GuiGlobals::linearDomTableViewFontPointSize() const
{
    return m_linearDomTableViewFontPointSize;
}

void GuiGlobals::linearDomTableViewFontPointSizeSet(int linearDomTableViewFontPointSize)
{
    m_settings.setValue("linearDomTableView/fontPointSize", linearDomTableViewFontPointSize);
    m_linearDomTableViewFontPointSize = linearDomTableViewFontPointSize;
}






