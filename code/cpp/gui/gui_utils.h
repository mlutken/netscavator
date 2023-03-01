#pragma once

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

void    leftMouseClick              (QWidget* eventsReciverWidget, QPoint clickPos);
