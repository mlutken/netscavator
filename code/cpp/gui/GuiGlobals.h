#pragma once

#include <QString>
#include <QStringList>
#include <QSettings>


class GuiGlobals
{
public:
    GuiGlobals();
    ~GuiGlobals();
    void readFromSettings   ();
    void writeToSettings    ();

    QStringList     recentCrawlers;

    float browserZoomLevel() const;
    void browserZoomLevelSet(float value);

    int mainEditorZoomLevel() const;
    void mainEditorZoomLevelSet(int value);
    int phpQuickZoomLevel() const;
    void phpQuickZoomLevelSet(int value);
    QString phpQuickCode() const;
    void phpQuickCodeSet(const QString& phpQuickCode);

    int mainWindowWidth() const;
    void mainWindowWidthSet(int mainWindowWidth);

    int mainWindowHeight() const;
    void mainWindowHeightSet(int mainWindowHeight);

    int mainToolBarIconSize() const;
    void mainToolBarIconSizeSet(int mainToolBarIconSize);

    int debugToolBarIconSize() const;
    void debugToolBarIconSizeSet(int debugToolBarIconSize);

    int linearDomTableViewFontPointSize() const;
    void linearDomTableViewFontPointSizeSet(int linearDomTableViewFontPointSize);

    QSettings& settings () { return m_settings; }

private:
    int         m_mainWindowWidth = 600;
    int         m_mainWindowHeight = 400;
    int         m_mainToolBarIconSize = 40;
    int         m_debugToolBarIconSize = 40;
    float       m_browserZoomLevel = 1.0f;
    int         m_mainEditorZoomLevel = 1;
    int         m_phpQuickZoomLevel = 1;
    int         m_linearDomTableViewFontPointSize = 8;
    QString     m_phpQuickCode;
    QSettings   m_settings;
};
