#pragma once

#include <QWidget>
#include <QString>

class QComboBox;
class QUrl;

class UrlInputUi : public QWidget
{
    Q_OBJECT
public:
    explicit UrlInputUi(QWidget *parent = 0);
    QString     urlString           () const;

    void        addQuickLoadUrl     (const QString& url);

signals:
    void        urlChanged          (const QString& url);
    
public slots:
    void        urlSetSlot          (const QString& url);
    void        clearQuickLoadUrls  ();
    void        setCurrentUrl       (const QString& url);
    void        setCurrentUrl       (const QUrl& url);
protected:
    bool        eventFilter         (QObject* obj, QEvent* event) override;

    
private:
    QComboBox*      m_pUrlCombo;
};
