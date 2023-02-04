#ifndef LEFTPANELUI_H
#define LEFTPANELUI_H

#include <QWidget>
#include <QPushButton>

class LeftPanelUi : public QWidget
{
    Q_OBJECT
public:
    explicit LeftPanelUi(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QPushButton*    m_runBtn;
    
};

#endif // LEFTPANELUI_H
