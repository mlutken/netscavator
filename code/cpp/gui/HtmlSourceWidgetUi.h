#ifndef HTMLSOURCEWIDGETUI_H
#define HTMLSOURCEWIDGETUI_H

#include <QWidget>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerhtml.h>

class HtmlSourceWidgetUi : public QsciScintilla
{
    Q_OBJECT
public:
    explicit HtmlSourceWidgetUi(QWidget *parent = nullptr);

signals:

public slots:
    void    findTextSlot        (const QString& text);
    void    findTextNextSlot    (const QString& text);

};

#endif // HTMLSOURCEWIDGETUI_H
