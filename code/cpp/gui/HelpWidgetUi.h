#ifndef HELPWIDGETUI_H
#define HELPWIDGETUI_H

#include <QWidget>

//FIXME OLD QWebView class QWebView;
class QTableWidget;

class HelpWidgetUi : public QWidget
{
    Q_OBJECT
public:
    explicit HelpWidgetUi(QWidget *parent = 0);
    
signals:
    
public slots:

private slots:
    void	itemSelectionChangedSlot ();

private:
//FIXME OLD QWebView     QWebView*       m_pHelpBrowser;
    QTableWidget*   m_pHelpMenuTbl;
};

#endif // HELPWIDGETUI_H
