#include "EditorWidget.h"
#include <QPushButton>
#include <QBoxLayout>

EditorWidget::EditorWidget(QWidget *parent) :
    QWidget(parent)
{
    QPushButton* fileOpenBtn = new QPushButton(tr("Open file"));
    fileOpenBtn->setFont(QFont("Times", 12, QFont::Bold));
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(fileOpenBtn);
    setLayout(layout);

}
