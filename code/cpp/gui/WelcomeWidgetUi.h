#ifndef WELCOMEWIDGETUI_H
#define WELCOMEWIDGETUI_H

#include <QWidget>

class QTabWidget;
class ProjectsViewUi;

class WelcomeWidgetUi : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeWidgetUi(QWidget *parent = 0);

    ProjectsViewUi*     projects    () const { return m_pProjects; }

signals:
    void    newCrawlerSignal    ();
    void    openCrawlerSignal   ();


public slots:

private:
    // --- PRIVEATE: Data ---
    QTabWidget*         m_pTabs;
    ProjectsViewUi*     m_pProjects;
};

#endif // WELCOMEWIDGETUI_H
