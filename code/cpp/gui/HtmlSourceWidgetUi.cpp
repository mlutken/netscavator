#include "HtmlSourceWidgetUi.h"

#include <QLabel>
#include <QVBoxLayout>
#include <Qsci/qscilexerhtml.h>

HtmlSourceWidgetUi::HtmlSourceWidgetUi(QWidget *parent)
    : QsciScintilla(parent)
{
    setLexer(new QsciLexerHTML(this));
    setUtf8(true);
    setReadOnly(true);
}

void HtmlSourceWidgetUi::findTextSlot(const QString& text)
{
    bool useRegex = false;
    bool caseSensitive = false;
    bool wholeWordsOnly = false;
    bool wrapToStart = true;
    findFirst(text, useRegex, caseSensitive, wholeWordsOnly, wrapToStart);
}

void HtmlSourceWidgetUi::findTextNextSlot(const QString& /*text*/)
{
    findNext();
}
