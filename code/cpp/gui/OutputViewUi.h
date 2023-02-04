#ifndef CRAWL_OUTPUT_VIEW_UI_H
#define CRAWL_OUTPUT_VIEW_UI_H

#include <DataWriterIF.h>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QCheckBox>
#include <MinerWorkerIF.h>

class OutputViewText : public QPlainTextEdit
{
    Q_OBJECT
public:
    OutputViewText(QWidget* parent = nullptr);
private:
};


class OutputViewUi : public QWidget
{
    Q_OBJECT
public:
    OutputViewUi(QWidget* parent = nullptr);
    bool	event(QEvent * e) override;

public slots:
    void clearSlot();
    void appendHtmlSlot(const QString& html);
private:
    OutputViewText*     m_text;
    QComboBox*          m_viewModeSelect;
    QCheckBox*          m_wrapModeSelect;
};

#endif // CRAWL_OUTPUT_VIEW_UI_H
