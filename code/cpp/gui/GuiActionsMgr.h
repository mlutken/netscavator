#pragma once

#include <map>
#include <QString>

class QMainWindow;
class QAction;

class GuiActionsMgr
{
public:
    typedef std::map<QString, QAction*>         GuiActionsMapT;
    GuiActionsMgr(QMainWindow* pMainWindow);
    ~GuiActionsMgr();

    QAction*            byName  ( const QString& actionName ) const;

private:
    QMainWindow*        m_pMainWindow;
    GuiActionsMapT      m_actionsMap;

};
