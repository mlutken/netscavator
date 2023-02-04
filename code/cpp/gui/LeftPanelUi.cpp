#include "LeftPanelUi.h"
#include <QVBoxLayout>

LeftPanelUi::LeftPanelUi(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    m_runBtn = new QPushButton("Run run", this);

    layout->addWidget(m_runBtn);
    setLayout(layout);

}
