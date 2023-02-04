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

void readRecentCrawlers( QStringList& list )
{
    QSettings settings("Nitram", "SleipnerCreator");
    list.clear();
    int size = settings.beginReadArray("recentCrawlers");

    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        list.append( settings.value("path").toString() );
    }
    settings.endArray();
}


void writeRecentCrawlers( const QStringList& list )
{
    QSettings settings("Nitram", "SleipnerCreator");
    settings.beginWriteArray("recentCrawlers");

    for (int i = 0; i < list.count(); ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue("path", list.at(i) );
    }
    settings.endArray();
}


void updateRecentCrawlersList ( const QFileInfo& filePath )
{
    QStringList& recentCrawlers = crawl::g()->gui()->recentCrawlers;
    readRecentCrawlers( recentCrawlers );
    QString absPath = filePath.absoluteFilePath();
    recentCrawlers.removeAll( absPath );
    recentCrawlers.push_front( absPath );
    if ( recentCrawlers.count() > 6 ) {
        recentCrawlers.pop_back();
    }
    writeRecentCrawlers( recentCrawlers );
}


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
