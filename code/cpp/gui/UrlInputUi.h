#pragma once

#include <QWidget>
#include <QString>

class QComboBox;

class UrlInputUi : public QWidget
{
    Q_OBJECT
public:
    explicit UrlInputUi(QWidget *parent = 0);
    QString     urlString       () const;


signals:
    void        urlChanged      ( const QString& url );
    
public slots:
    void        urlSetSlot      ( const QString& url );

protected:
    bool        eventFilter     (QObject* obj, QEvent* event) override;


private slots:
    void        urlActivatedSlot( const QString& url );
    
private:
    QComboBox*      m_pUrlCombo;
};
