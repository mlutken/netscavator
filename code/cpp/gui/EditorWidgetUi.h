#ifndef EDITORWIDGETUI_H
#define EDITORWIDGETUI_H

#include <QWidget>
#include <QIcon>

class QTabWidget;
class EditorViewUi;
class QFileInfo;

class EditorWidgetUi : public QWidget
{
    Q_OBJECT
public:
    explicit EditorWidgetUi(QWidget *parent = 0);
    ~EditorWidgetUi();

    // --- PUBLIC: Tab functions ---
    EditorViewUi*   addEditorTab    ( const QFileInfo& filePath );
    EditorViewUi*   addEditorTab    ( const QString& filePath );
    EditorViewUi*   addEditorTab    ();
    EditorViewUi*   currentEditor   () const;
    EditorViewUi*   editor          ( int index ) const;
    EditorViewUi*   crawlerEditor   () const         { return m_pCrawlerEditor; }

    // --- PUBLIC: File functions ---
    void            openCrawler   ( const QFileInfo& filePath   ) ;
    void            openCrawler   ( const QString& filePath     ) ;


signals:
    
public slots:
    bool        saveFileSlot            ();
    bool        saveCrawlerAsSlot       ();
    bool        saveFileAsSlot          ();
    bool        openCrawlerSlot         ();
    bool        openCrawlerPathSlot     ( const QString& path );
    bool        openFileSlot            ();
    bool        closeCrawlerSlot        ();
    bool        closeCrawlerProjectSlot ();
    void        closeFileSlot           ();
    void        newCrawlerSlot          ();
    void        newFileSlot             ();
    void        newPhpFileSlot          ();


    // --- PRIVATE: Slots and functions ---
private:
    int             crawlerIndex        () const;
    void            openFile            ( int index, const QFileInfo& filePath );

private slots:
    void                tabCloseRequestedSlot   ( int index );
    void                textModifiedSlot        ( EditorViewUi* pEditor, bool isModified );
    void                filePathChangedSlot     ( EditorViewUi* pWebView, const QFileInfo& filePath );

private:
    // --- PRIVATE: Helper functions ---
    void        setTabText  ( int index, const QFileInfo& filePath );

    // --- PRIVEATE: Data ---
    QTabWidget*         m_pTabs;
    EditorViewUi*       m_pCrawlerEditor;
    QIcon               m_fileModifiedIcon;
};

#endif // EDITORWIDGETUI_H
