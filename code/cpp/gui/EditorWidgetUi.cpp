#include "EditorWidgetUi.h"

#include <stdio.h>
#include <QFileInfo>
#include <QLabel>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QTabBar>
#include <QColor>

#include <Globals.h>
#include <GuiGlobals.h>
#include <Configuration.h>
#include <EditorViewUi.h>
#include <gui_utils.h>

EditorWidgetUi::EditorWidgetUi(QWidget *parent) :
    QWidget(parent)
{
    // --- Load textModifiedIcon
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();
    std::string iconsDir = c->valueStrGet("resource-dir") + "/icons/48x48/";
    m_fileModifiedIcon = QIcon ( (iconsDir+"file_modified.png").c_str() );

    m_pTabs = new QTabWidget(this);
    m_pTabs->setTabsClosable(true);
    m_pTabs->setMovable(true);
    //m_pTabs->setDocumentMode(true);
//    connect(m_pTabs, SIGNAL(currentChanged(int)), this, SLOT(tabChangedSlot(int)));
    connect (m_pTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(tabCloseRequestedSlot(int)));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_pTabs);

    // --- Create tab for main crawler script ---
    m_pCrawlerEditor = new EditorViewUi;
    m_pCrawlerEditor->contentNameSet( tr("Crawler"));
    int index = m_pTabs->addTab( m_pCrawlerEditor, QString("[") + tr("Crawler Script") + "]" );
    connect( m_pCrawlerEditor, SIGNAL(modificationChangedSignal(EditorViewUi*,bool)), this, SLOT(textModifiedSlot(EditorViewUi*,bool)) );
    connect( m_pCrawlerEditor, SIGNAL(filePathChangedSignal(EditorViewUi*,QFileInfo)), this, SLOT(filePathChangedSlot(EditorViewUi*,QFileInfo)) );
    ////m_pTabs->tabBar()->setTabTextColor( index, QColor("red") );


    ////openCrawler("/home/ml/code/miners/doc/examples/code/ExNavigatorAndSelects/ExNavigatorAndSelects.php");

    ////addEditorTab(QString("/home/ml/code/miners/scripts/airplay/utils/AirplayUtils.php"));
    setLayout(layout);


}

EditorWidgetUi::~EditorWidgetUi()
{
}

// -----------------------------
// --- PUBLIC: Tab functions ---
// -----------------------------

EditorViewUi* EditorWidgetUi::addEditorTab( const QFileInfo& filePath )
{
    EditorViewUi* pEditorView = new EditorViewUi;
    int index = m_pTabs->addTab( pEditorView, tr("New file") );
    connect( pEditorView, SIGNAL(modificationChangedSignal(EditorViewUi*,bool)), this, SLOT(textModifiedSlot(EditorViewUi*,bool)) );
    connect( pEditorView, SIGNAL(filePathChangedSignal(EditorViewUi*,QFileInfo)), this, SLOT(filePathChangedSlot(EditorViewUi*,QFileInfo)) );

    openFile( index, filePath );
    return pEditorView;
}


EditorViewUi* EditorWidgetUi::addEditorTab( const QString& filePath )
{
    return addEditorTab( QFileInfo(filePath));
}


EditorViewUi* EditorWidgetUi::currentEditor() const
{
    return static_cast<EditorViewUi*>(m_pTabs->currentWidget());
}

EditorViewUi* EditorWidgetUi::editor( int index ) const
{
    QWidget* pWidget = m_pTabs->widget(index);
    return static_cast<EditorViewUi*>(pWidget);
}


// ------------------------------
// --- PUBLIC: File functions ---
// ------------------------------

void EditorWidgetUi::openCrawler( const QFileInfo& filePath )
{
//    int index = crawlerIndex();
//    openFile( index, filePath );
    m_pCrawlerEditor->openFile( filePath );
    crawl::g()->gui()->updateRecentCrawlersList( filePath );
}

void EditorWidgetUi::openCrawler( const QString& filePath )
{
    openCrawler( QFileInfo(filePath) );
}


// ------------------------------------
// --- PRIVATE: Slots and functions ---
// ------------------------------------

/** Index of main crawler script (editor) tab */
int EditorWidgetUi::crawlerIndex () const
{
    return m_pTabs->indexOf( m_pCrawlerEditor );
}



void EditorWidgetUi::openFile( int index, const QFileInfo& filePath )
{
    EditorViewUi* pEditorView = editor(index);
    if ( !pEditorView ) return;
    if ( !filePath.exists() ) return;

    // --- Set tab title and tooltip to leaf filename. Truncate long names. ---
    //setTabText( index, filePath );

    pEditorView->openFile(filePath);
}



//void EditorWidgetUi::tabChangedSlot  (int /*index*/ )
//{
//}


// ---------------------
// --- PUBLIC: Slots ---
// ---------------------

bool EditorWidgetUi::saveFileSlot()
{
    return currentEditor()->saveFileSlot();
}

bool EditorWidgetUi::saveCrawlerAsSlot()
{
    bool saved = m_pCrawlerEditor->saveFileAsSlot();
    if ( saved ) {
        crawl::g()->gui()->updateRecentCrawlersList( m_pCrawlerEditor->filePath() );
    }
    return saved;
}

bool EditorWidgetUi::saveFileAsSlot()
{
    if ( currentEditor() == m_pCrawlerEditor )  return saveCrawlerAsSlot();
    else return currentEditor()->saveFileAsSlot();
}

bool EditorWidgetUi::openCrawlerSlot()
{
    bool ok = m_pCrawlerEditor->openFileSlot();
    if (ok) crawl::g()->gui()->updateRecentCrawlersList( m_pCrawlerEditor->filePath() );
    return ok;
}

bool EditorWidgetUi::openCrawlerPathSlot ( const QString& path )
{
    bool ok = m_pCrawlerEditor->openFile( path );
    if (ok) crawl::g()->gui()->updateRecentCrawlersList( m_pCrawlerEditor->filePath() );
    return ok;
}


bool EditorWidgetUi::openFileSlot()
{
    EditorViewUi* pEditor = addEditorTab( QFileInfo() );
    bool ok = pEditor->openFileSlot();
    // TODO: Implement this:
    //if (ok) updateFilesOpenList( pEditor->filePath() );
    return ok;
}

bool EditorWidgetUi::closeCrawlerSlot  ()
{
    bool closed = false;
    if ( m_pCrawlerEditor->maybeSaveFile() ) {
        closed = true;
        m_pCrawlerEditor->newPhpFile("No crawler");
    }
    return closed;
}

bool EditorWidgetUi::closeCrawlerProjectSlot ()
{
    bool allClosed = closeCrawlerSlot();
    for ( int i = 0; i < m_pTabs->count(); ++i ) {
        EditorViewUi* pEditor =  editor(i);
        if ( pEditor && pEditor != m_pCrawlerEditor ) {
            allClosed = allClosed && pEditor->maybeSaveFile();
        }
    }
    return allClosed;
}


void EditorWidgetUi::closeFileSlot ()
{
    tabCloseRequestedSlot( m_pTabs->currentIndex() );
}

void EditorWidgetUi::newCrawlerSlot ()
{
    closeCrawlerSlot ();
}

void EditorWidgetUi::newFileSlot ()
{
    EditorViewUi* pEditor = addEditorTab( QFileInfo() );
    pEditor->newFile("New file");
}

void EditorWidgetUi::newPhpFileSlot ()
{
    EditorViewUi* pEditor = addEditorTab( QFileInfo() );
    pEditor->newPhpFile("New file");
}


// ----------------------
// --- PRIVATE: Slots ---
// ----------------------

void EditorWidgetUi::tabCloseRequestedSlot ( int index )
{
    if ( index != crawlerIndex() ) {
        EditorViewUi* pEditor = editor(index);
            if ( pEditor->maybeSaveFile() ) {
            m_pTabs->removeTab(index);
            delete pEditor;
        }
    }
    else closeCrawlerSlot();
}

void EditorWidgetUi::textModifiedSlot  ( EditorViewUi* pEditor, bool isModified )
{
    int index = m_pTabs->indexOf( pEditor );
    if (isModified) m_pTabs->setTabIcon( index, m_fileModifiedIcon );
    else            m_pTabs->setTabIcon(index, QIcon() );
////    printf("textModifiedSlot: %d,  %d\n", index, isModified);
}


void EditorWidgetUi::filePathChangedSlot  ( EditorViewUi* pWebView, const QFileInfo& filePath )
{
    int index = m_pTabs->indexOf( pWebView );
    setTabText( index, filePath );
}


void EditorWidgetUi::setTabText( int index, const QFileInfo& filePath )
{
    // --- Set tab title and tooltip to leaf filename. Truncate long names. ---
    QString title =  filePath.fileName();
    const int titleFullLenght = title.length();
    m_pTabs->setTabToolTip(index, title );
    title.truncate(12);
    if ( title.length() < titleFullLenght ) title += "..";
    if ( index == crawlerIndex() ) {
        title = "[" + title + "]";
    }
    m_pTabs->setTabText(index, title );
}
