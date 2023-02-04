#ifndef DOMSEQWIDGET_H
#define DOMSEQWIDGET_H

#include <QWidget>

class QVBoxLayout;

class DomSeqWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DomSeqWidget(QWidget *parent = nullptr);

signals:

public slots:
private:
    QVBoxLayout*    m_layout;
};

#endif // DOMSEQWIDGET_H
