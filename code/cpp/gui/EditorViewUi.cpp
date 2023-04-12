#include "EditorViewUi.h"

#include <iostream>
#include <fstream>
#include <QTextStream>
#include <QApplication>
#include <QWheelEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <math/base/utils.hpp>
#include <filesystem/cpaf_file_directory_functions.h>

#include <utils/utils.h>
#include <gui/editor_utils.h>
#include <interfaces/Globals.h>
#include <GuiGlobals.h>

// -------------------------------------------
// --- PUBLIC: Constructor, Init functions ---
// -------------------------------------------

using namespace std;
using namespace crawl;

EditorViewUi::EditorViewUi()
    : QsciScintilla()
    , m_filePath("")
    , m_contentName( tr("File"))
{
    m_guiGlobals = g()->gui();
    setFolding(QsciScintilla::PlainFoldStyle);
    setTabWidth(4);
    setAutoCompletionThreshold(3);
    setAutoCompletionCaseSensitivity(false);
    setUtf8(true);
    zoomTo(m_guiGlobals->mainEditorZoomLevel());

    connect( this, SIGNAL(modificationChanged(bool)), this, SLOT(modificationChangedSlot(bool)) );

}

EditorViewUi::~EditorViewUi()
{

}


// ------------------------------
// --- PUBLIC: File functions ---
// ------------------------------
bool EditorViewUi::openFile( const QString& filePath )
{
    return openFile( QFileInfo(filePath) );
}

bool EditorViewUi::openFile( const QFileInfo& filePath)
{
    m_filePath = filePath;
    if ( !m_filePath.exists() ) return false;

    QString sFile;
    QFile file( filePath.filePath() );
    bool openedOk = false;
    if (file.open(QFile::ReadOnly)) {
        openedOk = true;
        char buf[1024];
        qint64 lineLength = file.readLine(buf, sizeof(buf));
        while ( lineLength != -1) {
            sFile += QString::fromUtf8(buf);
            lineLength = file.readLine(buf, sizeof(buf));
        }
    }
    setLexer( lexerFromFilePath(filePath, this) );
    setText(sFile);
    setModified(false);
    if ( openedOk ) {
        emit filePathChangedSignal( this, m_filePath );
        return true;
    }
    return false;
}

bool EditorViewUi::saveFile  ( const QFileInfo& filePath )
{
    m_filePath = filePath;
    return saveFile();
}

bool EditorViewUi::saveFile  ( const QString& filePath )
{
    return saveFile( QFileInfo(filePath) );
}

bool EditorViewUi::saveFile ()
{
    bool ok = false;
    ofstream out( m_filePath.filePath().toUtf8().data() );
    if ( out.is_open() ) {
        ok = true;
        QApplication::setOverrideCursor(Qt::WaitCursor);
        out << text().remove('\r').toUtf8().constData();
        QApplication::restoreOverrideCursor();
        setModified(false);
    }
    else {
        QMessageBox::warning(this, tr("Creator"),
                             tr("Cannot write file %1")
                             .arg(m_filePath.filePath())
                             );

    }
    //QFile file(m_filePath.filePath() );
    //if (file.open(QFile::WriteOnly)) {
    //    ok = true;
    //    QTextStream out(&file);
    //    QApplication::setOverrideCursor(Qt::WaitCursor);
    //    out << text().toUtf8().data();
    //    QApplication::restoreOverrideCursor();
    //    setModified(false);
    //}
    //else {
    //    QMessageBox::warning(this, tr("Creator"),
    //                         tr("Cannot write file %1:\n%2.")
    //                         .arg(m_filePath.filePath())
    //                         .arg(file.errorString()));

    //}
    return ok;
}


bool EditorViewUi::saveFileAs()
{
    QString dir ("");
    if ( m_filePath.fileName() != "" ) {
        dir = m_filePath.dir().absolutePath();
    }

    QString fileName = QFileDialog::getSaveFileName(this, m_contentName, dir );
    if (fileName.isEmpty())
        return false;

    bool savedOk = saveFile(fileName);
    if ( savedOk ) {
        emit filePathChangedSignal( this, m_filePath );
        setLexer( lexerFromFilePath(m_filePath, this) );
    }
    return savedOk;
}


bool EditorViewUi::maybeSaveFile()
{
    if ( isModified() ) {
        int ret = QMessageBox::warning(this, tr("Application"),
                     m_contentName + ":\n" +
                     tr("The ") + leafFileName() + tr(" has been modified.\n"
                     "Do you want to save your changes?"),
                     QMessageBox::Yes | QMessageBox::Default,
                     QMessageBox::No,
                     QMessageBox::Cancel | QMessageBox::Escape);
        if (ret == QMessageBox::Yes) {
            return saveFileSlot();
        }
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}


void EditorViewUi::newFile ( const QString& tabText )
{
    m_filePath = QFileInfo("");
    setText("");
    setModified(false);
    emit filePathChangedSignal( this, QFileInfo(tabText) );
}

void EditorViewUi::newPhpFile ( const QString& tabText )
{
    newFile(tabText);
    setText("<?php\n\n?>");
    setLexer( lexerFromFilePath(QFileInfo("dummy.php"), this) );
}


bool  EditorViewUi::hasFilePath () const
{
    return m_filePath.exists();
}


// ---------------------
// --- PUBLIC: Slots ---
// ---------------------

bool EditorViewUi::saveFileSlot()
{
    if ( hasFilePath() )   return saveFile();
    else                   return saveFileAs();
}

bool EditorViewUi::saveFileAsSlot()
{
    return saveFileAs();
}

bool EditorViewUi::openFileSlot()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Scripts (*.php *.cpp *.h)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDirectory(g()->gui()->fileOpenDir());
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        g()->gui()->fileOpenDirSet(dialog.directory().canonicalPath());
        QFileInfo path (fileNames[0]);
        return openFile(path);
    }
    return false;
}

void EditorViewUi::findTextSlot(const QString& text)
{
    bool useRegex = false;
    bool caseSensitive = false;
    bool wholeWordsOnly = false;
    bool wrapToStart = true;
    findFirst(text, useRegex, caseSensitive, wholeWordsOnly, wrapToStart);
}

void EditorViewUi::findTextNextSlot(const QString& /*text*/)
{
    findNext();
}

// ----------------------------
// --- PROTECTED: overrides ---
// ----------------------------

void EditorViewUi::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers() && Qt::ControlModifier ) {
        const int zoomDelta = cpaf::math::clamp_copy(event->angleDelta().y(), -1, 1);
        m_guiGlobals->mainEditorZoomLevelSet(m_guiGlobals->mainEditorZoomLevel() + zoomDelta);
        zoomTo(m_guiGlobals->mainEditorZoomLevel());
        event->accept();
        return;
    }
    else {
        QsciScintilla::wheelEvent(event);
        return;
    }
    event->ignore();
}

void EditorViewUi::keyPressEvent(QKeyEvent* event)
{
    QsciScintilla::keyPressEvent(event);
    if (event->type() == QEvent::KeyPress && event->matches(QKeySequence::Save)) {
        saveFileSlot();
    }
}

// ----------------------
// --- PRIVATE: Slots ---
// ----------------------

void EditorViewUi::modificationChangedSlot   ( bool isModified )
{
    emit modificationChangedSignal( this, isModified );
}

