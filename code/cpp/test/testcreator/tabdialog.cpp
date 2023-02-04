/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include <boost/algorithm/string.hpp>
#include <cpaf_string_utils.hpp>
#include <php_embedding/php_embedding_utils.h>
#include <php_embedding/php_embedding_callbacks.h>
#include <crawl/ScriptMiner.h>
#include <Configuration.h>
#include <Globals.h>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerhtml.h>

#include "tabdialog.h"
#include "MyWidget.h"

using namespace std;
using namespace boost;
using namespace boost::algorithm;

const int MAX_ARGS = 10;

TabDialog::TabDialog(const QString& fileName, QWidget *parent)
    : QWidget(parent)
{
    QFileInfo fileInfo(fileName);


    tabWidget           = new QTabWidget;
    m_pMyWidget         = new MyWidget;
    m_pMainScriptTab    = new MainScriptFileTab(m_pMyWidget);
    tabWidget->addTab( m_pMyWidget, tr("Browser"));
    tabWidget->addTab( m_pMainScriptTab, tr("Main script") );
    tabWidget->addTab(new GeneralTab(fileInfo), tr("General"));
    tabWidget->addTab(new PermissionsTab(fileInfo), tr("Permissions"));

    m_pMainScriptTab->openFile(fileName);
//    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
//                                     | QDialogButtonBox::Cancel);



    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
 //   mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Miner creator"));
}

GeneralTab::GeneralTab(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent)
{
    QLabel *fileNameLabel = new QLabel(tr("File Name:"));
    QLineEdit *fileNameEdit = new QLineEdit(fileInfo.fileName());

    QLabel *pathLabel = new QLabel(tr("Path:"));
    QLabel *pathValueLabel = new QLabel(fileInfo.absoluteFilePath());
    pathValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *sizeLabel = new QLabel(tr("Size:"));
    qlonglong size = fileInfo.size()/1024;
    QLabel *sizeValueLabel = new QLabel(tr("%1 K").arg(size));
    sizeValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *lastReadLabel = new QLabel(tr("Last Read:"));
    QLabel *lastReadValueLabel = new QLabel(fileInfo.lastRead().toString());
    lastReadValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *lastModLabel = new QLabel(tr("Last Modified:"));
    QLabel *lastModValueLabel = new QLabel(fileInfo.lastModified().toString());
    lastModValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileNameLabel);
    mainLayout->addWidget(fileNameEdit);
    mainLayout->addWidget(pathLabel);
    mainLayout->addWidget(pathValueLabel);
    mainLayout->addWidget(sizeLabel);
    mainLayout->addWidget(sizeValueLabel);
    mainLayout->addWidget(lastReadLabel);
    mainLayout->addWidget(lastReadValueLabel);
    mainLayout->addWidget(lastModLabel);
    mainLayout->addWidget(lastModValueLabel);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

PermissionsTab::PermissionsTab(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *permissionsGroup = new QGroupBox(tr("Permissions"));

    QCheckBox *readable = new QCheckBox(tr("Readable"));
    if (fileInfo.isReadable())
        readable->setChecked(true);

    QCheckBox *writable = new QCheckBox(tr("Writable"));
    if ( fileInfo.isWritable() )
        writable->setChecked(true);

    QCheckBox *executable = new QCheckBox(tr("Executable"));
    if ( fileInfo.isExecutable() )
        executable->setChecked(true);

    QGroupBox *ownerGroup = new QGroupBox(tr("Ownership"));

    QLabel *ownerLabel = new QLabel(tr("Owner"));
    QLabel *ownerValueLabel = new QLabel(fileInfo.owner());
    ownerValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *groupLabel = new QLabel(tr("Group"));
    QLabel *groupValueLabel = new QLabel(fileInfo.group());
    groupValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QVBoxLayout *permissionsLayout = new QVBoxLayout;
    permissionsLayout->addWidget(readable);
    permissionsLayout->addWidget(writable);
    permissionsLayout->addWidget(executable);
    permissionsGroup->setLayout(permissionsLayout);

    QVBoxLayout *ownerLayout = new QVBoxLayout;
    ownerLayout->addWidget(ownerLabel);
    ownerLayout->addWidget(ownerValueLabel);
    ownerLayout->addWidget(groupLabel);
    ownerLayout->addWidget(groupValueLabel);
    ownerGroup->setLayout(ownerLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(permissionsGroup);
    mainLayout->addWidget(ownerGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

MainScriptFileTab::MainScriptFileTab(MyWidget* pMyWidget, QWidget *parent)
    : QWidget(parent)
    , m_pMyWidget( pMyWidget )
    , m_scriptPath("")
{
    g_phpEmbedCallbacks::Instance().startUpFun = boost::bind(&MainScriptFileTab::phpStartupCallback, this, _1 );

    QPushButton* executePhpBtn  = new QPushButton( tr("Run script")) ;
    QPushButton* fileOpenBtn    = new QPushButton( tr("Open") );
    QPushButton* fileSaveBtn    = new QPushButton( tr("Save")) ;
    QPushButton* fileSaveAsBtn  = new QPushButton( tr("Save As")) ;

    m_pScriptTextEdit = new QsciScintilla;
    QsciLexerHTML* lexer = new QsciLexerHTML(m_pScriptTextEdit);
    m_pScriptTextEdit->setLexer(lexer);
//    const char* keywords = lexer->keywords(1);
//    printf("keywords: %s\n", keywords);
    m_pScriptTextEdit->setFolding(QsciScintilla::PlainFoldStyle);
    m_pScriptTextEdit->setTabWidth(4);
    m_pScriptTextEdit->setAutoCompletionThreshold(3);
    m_pScriptTextEdit->setAutoCompletionCaseSensitivity(false);
    m_pScriptTextEdit->setUtf8(true);
    m_pScriptTextEdit->zoomTo(2);
    //m_pScriptTextEdit->setAutoCompletionWordSeparators();

    connect(executePhpBtn,  SIGNAL(clicked()), this, SLOT( executePhpSlot() ));
    connect(fileOpenBtn,    SIGNAL(clicked()), this, SLOT( openFileSlot()   ));
    connect(fileSaveBtn,    SIGNAL(clicked()), this, SLOT( saveFileSlot()   ));
    connect(fileSaveAsBtn,  SIGNAL(clicked()), this, SLOT( saveFileAsSlot() ));

    connect(m_pScriptTextEdit, SIGNAL(textChanged()), this, SLOT(documentWasModifiedSlot()));


    QHBoxLayout* layoutToolBar = new QHBoxLayout;
    QVBoxLayout* layout = new QVBoxLayout;
    layoutToolBar->addWidget(executePhpBtn);
    layoutToolBar->addWidget(fileOpenBtn);
    layoutToolBar->addWidget(fileSaveBtn);
    layoutToolBar->addWidget(fileSaveAsBtn);
    layout->addLayout(layoutToolBar);
    layout->addWidget(m_pScriptTextEdit);
    setLayout(layout);
}

bool MainScriptFileTab::saveFile(const boost::filesystem::path& path)
{
    QString fileName = path.string().c_str();
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << m_pScriptTextEdit->text();
    QApplication::restoreOverrideCursor();

    setCurrentScriptFile(path);
    return true;
}

bool MainScriptFileTab::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;

    boost::filesystem::path p (fileName.toUtf8().data() );
    return saveFile(p);
}


bool MainScriptFileTab::maybeSave()
{
    if (m_pScriptTextEdit->isModified()) {
        int ret = QMessageBox::warning(this, tr("Application"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Yes | QMessageBox::Default,
                     QMessageBox::No,
                     QMessageBox::Cancel | QMessageBox::Escape);
        if (ret == QMessageBox::Yes)
            return saveFile(m_scriptPath);
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainScriptFileTab::setCurrentScriptFile   ( const boost::filesystem::path& path )
{
    m_scriptPath = path;
}


void MainScriptFileTab::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        //writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}


bool MainScriptFileTab::saveFileSlot()
{
    if ( !m_scriptPath.empty() )    saveFile(m_scriptPath);
    else                            saveFileAs();
}

bool MainScriptFileTab::saveFileAsSlot()
{
    return saveFileAs();
}

void MainScriptFileTab::openFileSlot()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Scripts (*.php *.cpp *.h)"));
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        openFile(fileNames[0]);
    }
}

void MainScriptFileTab::documentWasModifiedSlot()
{
    setWindowModified(m_pScriptTextEdit->isModified());
}


void MainScriptFileTab::executePhpSlot()
{
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();

//    std::string s = m_pScriptTextEdit->toPlainText().toUtf8().data();
    std::string s = m_pScriptTextEdit->text().toUtf8().data();
    erase_all( s, "<?php" );
    erase_all( s, "?>" );

    shutdownPhp();
    ////startupPhp( "" );

    //////
    char** argvPhp;
    int  argcPhp;

    argvPhp = allocateArrayOfStrings(MAX_ARGS, 256);
    c->getScriptArgvArgc( argcPhp, argvPhp );

    startupPhpScript(c->valueStrGet("php-ini-path").c_str(), argcPhp, argvPhp );
    freeArrayOfStrings( argvPhp, MAX_ARGS );

    executePhpString("require_once 'webminer.php';");

    setMinerPointerRaw( m_pMyWidget->miner().get());
    executePhpString( s.c_str() );
    if ( m_pMyWidget->miner() ) {
        m_pMyWidget->miner()->runModeSet( crawl::rmNormalE );
        m_pMyWidget->miner()->beginMiningAuto(true);
    }
}


void MainScriptFileTab::openFile( const QString& filePath)
{
    m_scriptPath = filePath.toUtf8().data();

    QString sFile;
    QFile file(filePath);
    if (file.open(QFile::ReadOnly)) {
        char buf[1024];
        qint64 lineLength = file.readLine(buf, sizeof(buf));
        while ( lineLength != -1) {
            sFile += QString::fromUtf8(buf);
            lineLength = file.readLine(buf, sizeof(buf));
        }
    }
//    m_pScriptTextEdit->setPlainText(sFile);
    m_pScriptTextEdit->setText(sFile);
}

int MainScriptFileTab::phpStartupCallback  ( struct _sapi_module_struct* /*sapi_module*/ )
{
    using namespace boost::filesystem;

    if ( !m_scriptPath.empty() ) {
        path p = m_scriptPath.parent_path();
        if ( !p.empty() ) {
            iniFileAddIncludePath( p.string().c_str() );
        }
    }
}
