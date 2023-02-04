#include <memory>
#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
//FIXME OLD QWebView #include <QtWebKit/QtWebKit>
#include <QSplitter>
#include <QLineEdit>
#include <SignalsManager.h>
//#include <creatorutils/DomTreeTextHtmlGen.h>
#include <url/Url.h>
#include <Configuration.h>
#include <Globals.h>
#include <GuiGlobals.h>
#include <WebkitCreatorFactory.h>
#include <SimpleCrawlerFactory.h>
#include <CrawlerMainWindowUi.h>
#include <CrawlerSimple.h>
#include <scripting/ScriptExecutor.h>
#include <php_embedding/php_embedding_callbacks.h>
#include <ScriptMiner.h>

using namespace crawl;

std::unique_ptr<crawl::NetscavatorFactoryIF> createNetcavatorFactory(
        const boost::shared_ptr<crawl::Configuration>& c,
        const std::string& browser)
{
    if (browser == "webkit") {
        return std::make_unique<WebkitCreatorFactory>(c);
    }
    else if (browser == "simple") {
        return std::make_unique<SimpleCrawlerFactory>(c);
    }
    return std::unique_ptr<crawl::NetscavatorFactoryIF>();
}

/** Create default scriptminer to be used only briefly for reading in the
    crawler script and giving it at chance to set config values like for
    example the 'browser' to use. */
boost::shared_ptr<ScriptMiner> createScriptMinerForConfig()
{
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();
    auto fac = createNetcavatorFactory(c, "simple");
    auto browser = boost::shared_ptr<crawl::WebBrowserIF>(fac->createBrowser(nullptr));
    const std::string baseOutputName = "Crawler";
    StringSearch::DataWriterVecT writers;

    auto miner = boost::shared_ptr<ScriptMiner>(
            new ScriptMiner(browser, baseOutputName, crawl::Url(""), writers, boost::shared_ptr<ScriptingClassIF>(), c )
    );
    return miner;
}

//CMD: /home/ml/code/miners/scripts/cycling/com/bike24.com.php --browser webkit --max-pageloads 5 --upload-result no

int main(int argc, char *argv[])
{
    boost::shared_ptr<crawl::Configuration> c = crawl::g()->configuration();
    g_phpEmbedCallbacks::Instance().logToStdOut = true;

    if ( !c->parseCommandLine( "crawler", argc, argv ) ) {
        exit(0);
    }
    auto scriptAbsPath = QString::fromUtf8(c->valueStrGet("script-path").c_str());

    // Give the script a chance to set core configuration variables like
    // for example 'browser'
    {
        crawl::ScriptExecutor se;
        se.loadMinerCode(createScriptMinerForConfig(), scriptAbsPath);
    }

    c->printSettings();
    const auto browser = c->valueStrGet("browser");
    auto netscavatorFactoryPtr = createNetcavatorFactory(c, browser);

    QCoreApplication::setOrganizationName("Nitram");
    QCoreApplication::setOrganizationDomain("netscavator.com");
    QCoreApplication::setApplicationName("Sleipner Creator");
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

    if (browser == "simple") {
        QCoreApplication app(argc, argv);
        CrawlerSimple crawlerSimple(netscavatorFactoryPtr.get());
        crawlerSimple.run(scriptAbsPath, c->runMode());
        return app.exec();
    }
    else {
        QApplication app(argc, argv);
        CrawlerMainWindowUi crawlerWindow(netscavatorFactoryPtr.get());
        crawlerWindow.run(scriptAbsPath, c->runMode());
        return app.exec();
    }
}


