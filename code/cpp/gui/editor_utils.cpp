#include <gui/editor_utils.h>

#include <QFileInfo>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexer.h>
#include <Qsci/qscilexerhtml.h>


QsciLexer* lexerFromExtension ( const QString& /*extension*/, QsciScintilla* pParentEditor    )
{
    return new QsciLexerHTML(pParentEditor);
}


QsciLexer* lexerFromFilePath    ( const QFileInfo& filePath, QsciScintilla* pParentEditor )
{
    return lexerFromExtension( filePath.suffix(), pParentEditor );
}

QsciLexer* lexerFromFilePath    ( const QFileInfo& filePath )
{
    return lexerFromExtension( filePath.suffix(), 0 );
}
