#include "OutputViewUi.h"

#include <iostream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QThread>

using namespace crawl;
using namespace std;

// ----------------------
// --- OutputViewText ---
// ----------------------

OutputViewText::OutputViewText( QWidget* parent)
    : QPlainTextEdit(parent)
{
    setLineWrapMode(QPlainTextEdit::NoWrap); // QPlainTextEdit::WidgetWidth
    setReadOnly(true);
    setMaximumBlockCount(2000);
}

// --------------------
// --- OutputViewUi ---
// --------------------

OutputViewUi::OutputViewUi( QWidget* parent )
    : QWidget(parent)
{
    m_text = new OutputViewText( this );
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* topLayout = new QHBoxLayout(this);

    m_viewModeSelect = new QComboBox(this);
    m_viewModeSelect->addItem( tr("View data") );
    m_viewModeSelect->addItem( tr("View PHP debug") );
    m_viewModeSelect->addItem( tr("View data+debug") );
    m_wrapModeSelect = new QCheckBox( tr("wrap"), this );

    topLayout->addWidget(m_viewModeSelect);
    topLayout->addWidget(m_wrapModeSelect);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_text);
    setLayout(mainLayout);
}

bool OutputViewUi::event(QEvent* e)
{
    bool processed = false;

    if (e->type() == PostStringEvent::staticType()) {
        auto ev = static_cast<PostStringEvent*>(e);
        m_text->appendHtml(ev->str); // Crash here!
        processed = true;
    }

    if (!processed)
        return QObject::event(e);

    return true;
}

void OutputViewUi::clearSlot()
{
    m_text->clear();
}

void OutputViewUi::appendHtmlSlot(const QString& html)
{
    m_text->appendHtml(html);
}
