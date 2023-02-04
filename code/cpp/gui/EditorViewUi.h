#ifndef EDITORVIEWUI_H
#define EDITORVIEWUI_H

#include <QFileInfo>
#include <QString>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerhtml.h>

class GuiGlobals;


class EditorViewUi : public QsciScintilla
{
    Q_OBJECT

public:
    // --- PUBLIC: Constructor, Init functions ---
    EditorViewUi();
    ~EditorViewUi() override;

    const QString&  contentName     () const { return m_contentName; }
    void            contentNameSet  ( const QString& contentName ) { m_contentName = contentName; }

    // ------------------------------
    // --- PUBLIC: File functions ---
    // ------------------------------
    bool        openFile        ( const QString& filePath   );
    bool        openFile        ( const QFileInfo& filePath );
    bool        saveFile        ( const QFileInfo& filePath );
    bool        saveFile        ( const QString& filePath   );
    bool        saveFile        ();
    bool        saveFileAs      ();
    bool        maybeSaveFile   ();

    void        newFile         ( const QString& tabText );
    void        newPhpFile      ( const QString& tabText );
    bool        hasFilePath     () const;
    const QFileInfo&    filePath() const { return m_filePath; }
    QString     leafFileName    () const { return m_filePath.fileName(); }

signals:
    void        modificationChangedSignal   ( EditorViewUi* pWebView, bool isModified );
    void        filePathChangedSignal       ( EditorViewUi* pWebView, const QFileInfo& filePath );

public slots:
    bool        saveFileSlot    ();
    bool        saveFileAsSlot  ();
    bool        openFileSlot    ();
    void        findTextSlot    (const QString& text);
    void        findTextNextSlot(const QString& text);

protected:
    void    wheelEvent                  ( QWheelEvent* event ) override;
    void    keyPressEvent               ( QKeyEvent *event) override;
private slots:
    void            modificationChangedSlot     ( bool isModified );

private:
    GuiGlobals* m_guiGlobals;
    QFileInfo   m_filePath;
    QString     m_contentName;
};

#endif // EDITORVIEWUI_H
