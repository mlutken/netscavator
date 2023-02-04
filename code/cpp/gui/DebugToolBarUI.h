#pragma once

#include <QToolBar>
#include <QLabel>

class GuiActionsMgr;
class GuiGlobals;
class QComboBox;

class DebugToolBarUI : public QToolBar
{
    Q_OBJECT
public:
    DebugToolBarUI(const QString & title, GuiActionsMgr* pAMgr, QWidget * parent = nullptr);

    QString     textToFind() const;

public slots:
    void matchLabelTextSet( const QString& text);

protected:
    void wheelEvent ( QWheelEvent* event ) override;

private:
    void createStructure(GuiActionsMgr* pAMgr);

    ~DebugToolBarUI() override;

    GuiGlobals*     m_guiGlobals;
    QLabel*         m_matchLbl;
    QComboBox*      m_findCombo;
};
