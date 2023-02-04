#ifndef GUI_UTILS_H
#define GUI_UTILS_H

#include <QPoint>
#include <QStringList>

class QFileInfo;
class QString;
class QWidget;

// ------------------------------
// --- QString util functions ---
// ------------------------------
QString leafFileName ( const QString& filePath );


// --------------------------------------
// --- Recent crawlers list functions ---
// --------------------------------------

void    readRecentCrawlers          ( QStringList& list       );
void    writeRecentCrawlers         ( const QStringList& list );
void    updateRecentCrawlersList    ( const QFileInfo& filePath         );
void    leftMouseClick              (QWidget* eventsReciverWidget, QPoint clickPos);

#endif // GUI_UTILS_H
