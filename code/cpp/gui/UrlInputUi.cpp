#include "UrlInputUi.h"

#include <iostream>
#include <QComboBox>
#include <QHBoxLayout>
#include <QEvent>
#include <QKeyEvent>

#include <Globals.h>
#include <GuiActionsMgr.h>


UrlInputUi::UrlInputUi(QWidget *parent) :
    QWidget(parent)
{
    m_pUrlCombo = new QComboBox(this);
    m_pUrlCombo->setEditable(true);
    m_pUrlCombo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(m_pUrlCombo);

    setLayout(layout);

    connect(m_pUrlCombo, SIGNAL(activated(QString)), this, SLOT(urlActivatedSlot(QString) ));
    m_pUrlCombo->installEventFilter(this);
}

QString UrlInputUi::urlString () const
{
    return m_pUrlCombo->currentText();
}

bool UrlInputUi::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() == QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
            crawl::g()->guiActionsMgr()->trigger("load_url");
        } else {
            return QWidget::eventFilter(obj, event);
        }
    } else {
        return QWidget::eventFilter(obj, event);
    }
    return false;
}


// ---------------------
// --- public slots: ---
// ---------------------
void UrlInputUi::urlSetSlot ( const QString& url )
{
    m_pUrlCombo->setEditText(url);
}



// ----------------------
// --- private slots: ---
// ----------------------


void UrlInputUi::urlActivatedSlot( const QString& url )
{
    emit urlChanged(url);
}
