#include "UrlInputUi.h"

#include <stdio.h>
#include <QComboBox>
#include <QHBoxLayout>


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


}

QString UrlInputUi::urlString () const
{
    return m_pUrlCombo->currentText();
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
    printf("ML: UrlInputUi::urlActivatedSlot: %s\n", url.toUtf8().data() );
    emit urlChanged(url);
}
