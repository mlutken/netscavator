#pragma once

#include <QObject>

namespace crawl {

class WebChannelBridge : public QObject
{
    Q_OBJECT
public:
    explicit WebChannelBridge(QObject *parent = nullptr);

signals:
    void nodeClick              (const QString& xpathList);
    void inputSet               (const QString& xpathList, const QString& input);
    void markPositions          (const QString& xpathList, bool clearCurrentlyMarked);
    void hoverPosition          (const QString& xpath);
    void cppToBrowser           (const QString& text, int counter);
    void domPosSelectedSig      (const QString& xpath, const QString& innerText);
    void domPosHoverSig         (const QString& xpath, const QString& innerText);

public slots:

    void browserToCpp           (const QString& text, int counter);
    void jsDomPosSelectedSlot   (const QString& xpath, const QString& innerText);
    void jsDomPosHoverSlot      (const QString& xpath, const QString& innerText);

private:

};

} // namespace crawl

