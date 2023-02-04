#ifndef PHPQUICKUI_H
#define PHPQUICKUI_H

#include <string>
#include <QWidget>

class QPushButton;
class QsciScintilla;
class QVBoxLayout;

class GuiGlobals;

class PhpQuickUi : public QWidget
{
    Q_OBJECT
public:
    explicit PhpQuickUi(QWidget *parent = 0);
    virtual ~PhpQuickUi() override;
    std::string     phpStringOld() const;
    QString         phpString() const;


signals:
    void            executePhpQuick();

public slots:

protected:
    virtual void    wheelEvent  ( QWheelEvent* event ) override;

private slots:
    void            onExecutePhpBtnClicked();

private:
    void            saveSettings();
    GuiGlobals*     m_guiGlobals;
    QVBoxLayout*    m_pMainLayout;
    QPushButton*    m_pExecutePhpBtn;
    QsciScintilla*  m_pPhpEdit;

};

#endif // PHPQUICKUI_H
