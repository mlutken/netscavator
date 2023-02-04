#ifndef EDITOR_UTILS_H
#define EDITOR_UTILS_H

class QsciLexer;
class QString;
class QFileInfo;
class QsciScintilla;

QsciLexer* lexerFromExtension   ( const QString& extension, QsciScintilla* pParentEditor    );
QsciLexer* lexerFromFilePath    ( const QFileInfo& filePath, QsciScintilla* pParentEditor   );
QsciLexer* lexerFromFilePath    ( const QFileInfo& filePath  );

#endif // EDITOR_UTILS_H
