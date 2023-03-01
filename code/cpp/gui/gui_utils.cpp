#include "gui_utils.h"

#include <QString>
#include <QSettings>
#include <QFileInfo>
#include <QStringList>
#include <QMouseEvent>
#include <QCoreApplication>
#include <QWidget>
#include <QTimer>

#include <Globals.h>
#include <GuiGlobals.h>

// ------------------------------
// --- QString util functions ---
// ------------------------------

QString leafFileName ( const QString& filePath )
{
    return QFileInfo(filePath).fileName();
}

// --------------------------------------
// --- Recent crawlers list functions ---
// --------------------------------------

/// From here: https://stackoverflow.com/questions/43067680/qt-webengine-simulate-mouse-event
/// @sa https://www.linuxquestions.org/questions/programming-9/simulating-a-mouse-click-594576/

void leftMouseClick(QWidget* eventsReciverWidget, QPoint clickPos)
{
    auto *press = new QMouseEvent(QEvent::MouseButtonPress,
                                            clickPos,
                                            Qt::LeftButton,
                                            Qt::MouseButton::NoButton,
                                            Qt::NoModifier);
    QCoreApplication::postEvent(eventsReciverWidget, press);
    // Some delay

    QTimer::singleShot(300, [clickPos, eventsReciverWidget]() {
        auto *release = new QMouseEvent(QEvent::MouseButtonRelease,
                                                clickPos,
                                                Qt::LeftButton,
                                                Qt::MouseButton::NoButton,
                                                Qt::NoModifier);
        QCoreApplication::postEvent(eventsReciverWidget, release);
    });
}
