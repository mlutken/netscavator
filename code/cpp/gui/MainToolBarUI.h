#pragma once

#include <QToolBar>

class GuiActionsMgr;
class GuiGlobals;

class MainToolBarUI : public QToolBar
{
public:
    MainToolBarUI(const QString & title, GuiActionsMgr* pAMgr, QWidget * parent = 0);


protected:
    virtual void    wheelEvent      ( QWheelEvent* event ) override;

private:
    void createStructure(GuiActionsMgr* pAMgr);

    ~MainToolBarUI();

    GuiGlobals* m_guiGlobals;

};
