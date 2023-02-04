#ifndef SCRIPTCTRL_H
#define SCRIPTCTRL_H

#include <QObject>

class ScriptCtrl : public QObject
{
    Q_OBJECT
public:
    explicit ScriptCtrl(QObject *parent = 0);
    ~ScriptCtrl();

    void        restartScript           ();
    QString     getCrawlerStartPage     ();
    void        closeScript             ();

signals:
    
public slots:
    
};

#endif // SCRIPTCTRL_H
