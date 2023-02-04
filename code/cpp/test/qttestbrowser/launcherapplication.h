#ifndef LAUNCHERAPPLICATION_H
#define LAUNCHERAPPLICATION_H

#include <QApplication>
#include "launcherwindow.h"


class LauncherApplication : public QApplication {
    Q_OBJECT

public:
    LauncherApplication(int& argc, char** argv);
    QStringList urls() const { return m_urls; }
    bool isRobotized() const { return m_isRobotized; }
    int robotTimeout() const { return m_robotTimeoutSeconds; }
    int robotExtraTime() const { return m_robotExtraTimeSeconds; }

private:
    void handleUserOptions();
    void applyDefaultSettings();
    void requiresGraphicsView(const QString& option);

private:
    bool m_isRobotized;
    int m_robotTimeoutSeconds;
    int m_robotExtraTimeSeconds;
    QStringList m_urls;
    WindowOptions m_windowOptions;

};

#endif // LAUNCHERAPPLICATION_H
