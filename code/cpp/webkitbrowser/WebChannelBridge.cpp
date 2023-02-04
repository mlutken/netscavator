#include "WebChannelBridge.h"
#include <iostream>
#include <QTimer>
#include <utils/utils.h>
#include <htmlparser/html/XPath.h>
#include <htmlparser/html/ParserDom.h>

using namespace std;
using namespace crawl;

namespace crawl {

WebChannelBridge::WebChannelBridge(QObject *parent)
    : QObject{parent}
{
//    connect(dialog, &Dialog::cppToBrowser, this, &Core::cppToBrowser);

}

void WebChannelBridge::browserToCpp(const QString& text, int counter)
{
    cerr << "FIXMENM WebChannelBridge::browserToCpp: "
         << text.toUtf8().constData()
         << "  counter: " << counter
         << "\n";
    counter++;
//    QTimer::singleShot(2000, this, [=, this]() {emit cppToBrowser("From C++ to browser", counter);} );
    //    emit cppToBrowser("From C++ to browser", counter);
}

void WebChannelBridge::jsDomPosSelectedSlot(const QString& xpath, const QString& innerText)
{
    const string path = toString(xpath);
    crawl::XPath xp(path);
//    cerr << "FIXMENM WebChannelBridge::jsDomPosSelectedSlot; "
//         << "\nxpath: " << xpath.toUtf8().constData()
//         << "\nconv : " << xp.toString()
//         << "\ninnerText: " << innerText.toUtf8().constData()
//         << "\n";

    emit domPosSelectedSig(xpath, innerText);
}


void WebChannelBridge::jsDomPosHoverSlot(const QString& xpath, const QString& innerText)
{
    const string path = toString(xpath);
    crawl::XPath xp(path);
//    cerr << "FIXMENM WebChannelBridge::jsDomPosHoverSlot; "
//         << "\nxpath: " << xpath.toUtf8().constData()
////         << "\nconv : " << xp.toString()
////         << "\ninnerText: " << innerText.toUtf8().constData()
//         << "\n";

    emit domPosHoverSig(xpath, innerText);
}

} // namespace crawl
