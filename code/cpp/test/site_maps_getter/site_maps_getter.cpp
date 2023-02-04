#include <navigator/SiteMapGetter.h>
#include <applicationutils/QtHttpDownloader.h>
#include <utils/QStringFinder.h>
#include <QApplication>
#include <iostream>
#include <QWidget>
#include <QtXml/QDomDocument>

using namespace std;
using namespace crawl;

static crawl::QtHttpDownloader manager;
static crawl::SiteMapGetter g_smg;

void completeCallback(QNetworkReply* reply, const QUrl& url)
{
    cout << "Download completed: " << url.toString().toUtf8().data() << endl;
    const QString filename = QtHttpDownloader::saveFileName(url);

    if (QtHttpDownloader::saveToDisk(filename, reply)) {
        cout << "Download of " << qPrintable(url.toString()) << " succeeded (saved to " <<
                qPrintable(filename) << ")" << endl;
    }
    QCoreApplication::instance()->quit();
}

void completeByteArrayCallback(const QByteArray& data, const QUrl& url, bool ok)
{
    cout << "QByteArray Download completed[" << ok << "] : " << url.toString().toUtf8().data() << endl;
    //const QString filename = QtHttpDownloader::saveFileName(url);

    cout << "DATA\n" << qPrintable(data) << endl;
    QCoreApplication::instance()->quit();
}

void testDownload1()
{
    cout << "testDownload1()" << endl;
////    manager.download(QUrl("https://www.veromoda.com/dk/da/sitemap_index.xml"), completeCallback);
    const QUrl url("https://www.veromoda.com/on/demandware.static/-/Library-Sites-bestseller-content-library/da_DK/dwa1e426d2/affiliatefeeds/product-sitemap/Sitemap_vm_17_BSE-DK.xml.gz");
//    const QUrl url("https://www.veromoda.com/dk/da/sitemap_index.xml");

    manager.downloadToByteArray(url, completeByteArrayCallback);

}

void testSitemapGetter1()
{
    cout << "testSitemapGetter1()" << endl;
//    g_smg.siteSet("https://www.veromoda.com");
    g_smg.siteSet("https://www.cyclingfreak.dk");

    g_smg.downloadSiteMap();
//    const QUrl url("https://www.veromoda.com/on/demandware.static/-/Library-Sites-bestseller-content-library/da_DK/dwa1e426d2/affiliatefeeds/product-sitemap/Sitemap_vm_17_BSE-DK.xml.gz");
//    const QUrl url("https://www.veromoda.com/dk/da/sitemap_index.xml");

//    manager.downloadToByteArray(url, completeByteArrayCallback);

}

void testSitemapGetter2()
{
    cout << "testSitemapGetter2() No sitemap" << endl;
//    g_smg.siteSet("https://www.veromoda.com");
    g_smg.siteSet("http://www.bikedesign.dk");

    g_smg.downloadSiteMap();
//    const QUrl url("https://www.veromoda.com/on/demandware.static/-/Library-Sites-bestseller-content-library/da_DK/dwa1e426d2/affiliatefeeds/product-sitemap/Sitemap_vm_17_BSE-DK.xml.gz");
//    const QUrl url("https://www.veromoda.com/dk/da/sitemap_index.xml");

//    manager.downloadToByteArray(url, completeByteArrayCallback);

}


[[ noreturn ]] void testQDomDocument()
{
const char* siteMapData = R"foo(
<?xml version="1.0" encoding="UTF-8"?>
<sitemapindex xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">
    <sitemap>
        <loc>1.xml.gz</loc>
    </sitemap>
    <sitemap>
        <loc>2.xml.gz</loc>
    </sitemap>
    <sitemap>
        <loc>3.xml.gz</loc>
    </sitemap>
</sitemapindex>
)foo";

    cout << "testStringFinder()" << endl;

    QDomDocument doc;
    QString errorMsg = "";
    int errorLine = -1;
    int errorColumn = -1;

    const bool ok = doc.setContent(QString::fromUtf8(siteMapData), &errorMsg, &errorLine, &errorColumn);
    cout << "Ok: " << ok << "\n"
         << "Error msg : " << qPrintable(errorMsg) << "\n"
         << "Error line: " << errorLine << "\n"
         << "Error col : " << errorColumn << "\n"
         << endl;
    QDomNodeList list=doc.elementsByTagName("loc");
    QString e=list.at(0).toElement().text();
    cout << "ELEM: " << qPrintable(e) << endl;


    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            cout << qPrintable(e.tagName()) << endl; // the node really is an element.
        }
        n = n.nextSibling();
    }

    exit(0);
}



[[ noreturn ]] void testStringFinder()
{
const char* siteMapData = R"foo(
<?xml version="1.0" encoding="UTF-8"?>
<sitemapindex xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">
    <sitemap>
        <loc>1.xml.gz</loc>
    </sitemap>
    <sitemap>
        <loc>2.xml.gz</loc>
    </sitemap>
    <sitemap>
        <loc>3.xml.gz</loc>
    </sitemap>
</sitemapindex>
)foo";

    cout << "testStringFinder()" << endl;
    QStringFinder sf(siteMapData);
//    QStringFinder sf("123456");

//    cout << "sf.searchIn().lenght(): '" << sf.searchIn().length() << "'\n" << endl;
//    cout << "sf.searchIn(): '\n" << qPrintable(sf.searchIn()) << "'\n" << endl;
//    cout << "sf.currentValue(): '\n" << qPrintable(sf.currentValue()) << "'\n" << endl;

    sf.ignoreCaseSet(true);
    bool moreLocations = true;
    int iter = 0 ;
    while (moreLocations) {
        ++iter;
        if (iter == 4) {
            cout << "DONE ?" << endl;
        }
//        cout << "[" << iter << "] CUR val: [" << sf.rangeBegin() << "," << sf.rangeEnd() << "] '\n"
//             <<  qPrintable(sf.currentValue()) << "'\n" << endl;
        moreLocations = sf.findBeginNext("<loc>");

        if (moreLocations) {
            moreLocations = sf.findEndNext("</loc>");
            if (moreLocations) {
                cout << "loc: [" << sf.rangeBegin() << "," << sf.rangeEnd() << "] '\n"
                     <<  qPrintable(sf.currentValue()) << "'\n" << endl;
                sf.nextSearch();
            }
        }
        if (iter > 4) {
            cout << "ERROR infinite loop!" << endl;
            moreLocations = false;
        }
    }

    exit(0);
}

void sitemapsDownloaded(SiteMapGetter* smg)
{
    cout << "****** Sitemaps downloaded *******" << endl;
    int i = 0;
    for (const auto& s : smg->locationUrls()) {
        ++i;
        cout << "[" << i << "] " << s << "\n";
        if (i > 10) {
            cout << "Only printing 10 URLs!" << endl;;

        }
    }
    cout << endl;
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
//    testStringFinder();
    g_smg.doneCallbackSet(sitemapsDownloaded);

//    QTimer::singleShot(0, &manager, &QtHttpDownloader::main);
    QTimer::singleShot(0, testSitemapGetter1);
//    QTimer::singleShot(0, &manager, &QtHttpDownloader::mainTester);

    return app.exec();
}





//int main(int argc, char *argv[])
//{
//	QApplication app(argc, argv);

//    QWidget w;
//    w.resize(1024,800);
//    w.show();
//	return app.exec();
//}

