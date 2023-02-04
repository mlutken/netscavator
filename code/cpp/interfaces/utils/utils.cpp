#include "utils.h"
#include <boost/thread.hpp>
#include <curl/curl.h>
#include <ScriptingClassIF.h>
#include <url/Url.h>
#include <QFile>
#include <QDebug>

using namespace std;
using namespace cpaf::filesystem;
using namespace boost;

// IMPORTANT: Never include files from within a namespace!
namespace crawl {


QString toQString(const string& s)
{
    return QString::fromUtf8(s.c_str());
}

string toString(const QString& s)
{
    return s.toUtf8().constData();
}

QUrl toQUrl(const string& url)
{
    return QUrl(QString::fromUtf8(url.c_str()));
}

string toString(const QUrl& url)
{
    return url.toString().toUtf8().constData();
}


boost::shared_ptr<cpaf::filesystem::filepaths_t>
getStandardPhpIncludePaths( boost::filesystem::path scriptFullPath )
{
    boost::shared_ptr<filepaths_t> incPaths ( new filepaths_t );
    boost::filesystem::path p = scriptFullPath.parent_path();
    incPaths->push_back(p); // script dir
    incPaths->push_back(p / "utils"); // script-dir/utils dir
    incPaths->push_back(p / "templates"); // script-dir/templates dir
    p = p.parent_path();
    incPaths->push_back(p / "utils"); // script-dir/../utils dir
    incPaths->push_back(p / "templates"); // script-dir/../templates dir
    return incPaths;
}


std::string getStandardPhpIncludePathString ( boost::filesystem::path scriptFullPath )
{
#ifdef WINDOWS
    const std::string sSep = ";";
#else
    const std::string sSep = ":";
#endif

    boost::shared_ptr<filepaths_t> incPaths = getStandardPhpIncludePaths( scriptFullPath );

    std::string sIni;
    for (unsigned i = 0; i < incPaths->size(); ++i ) {
        if ( i > 0 ) sIni += sSep;
        sIni += (*incPaths)[i].string();
    }
    return sIni;
}

std::string getMinerName (
        boost::shared_ptr<ScriptingClassIF> pScriptingClass
        )
{
    std::string sMinerName = "";

    std::string sFunName = "Script_minerName" ;
    if ( pScriptingClass->scriptFunctionExists(sFunName) ) {
        sMinerName = pScriptingClass->callScriptFunction_String ( sFunName, sMinerName ) ;
    }

    sFunName = "currentMiner" ; // Function currentMiner get it's value from ScriptGlobals::currentMinerName()
    if ( sMinerName == "" ) {
        sMinerName = pScriptingClass->callScriptFunction_String ( sFunName ) ;
    }
    if ( sMinerName == "" ) sMinerName = "Crawler" ;
    return sMinerName;
}


void getUrlStartAndUrlSite (
        boost::shared_ptr<ScriptingClassIF> pScriptingClass
        , const std::string& sMinerName
        ,  std::string& sUrlSite
        , std::string& sUrlStart
        )
{
    std::string sFunName;
    sUrlSite = "";
    sFunName =  sMinerName + "_urlSite" ;
    if ( pScriptingClass->scriptFunctionExists(sFunName) ) {
        sUrlSite = pScriptingClass->callScriptFunction_String ( sFunName ) ;
    }


    sUrlStart = "";
    if ( sUrlStart == "" ) {
        sFunName =  sMinerName + "_urlStart" ;
        if ( pScriptingClass->scriptFunctionExists(sFunName) ) sUrlStart = pScriptingClass->callScriptFunction_String ( sFunName ) ;
    }
    if ( sUrlStart == "" ) {
        sUrlStart = sUrlSite;
    }
    if ( sUrlStart != "" ) {
        Url uStart(sUrlStart) ;
        if ( sUrlSite == "" ) {
            sUrlSite = uStart.protocolCompose() + uStart.domainCompose();
        }
    }
}


std::string thisThreadId()
{
    std::stringstream idStream;
    idStream << boost::this_thread::get_id();
    return idStream.str();
}

/**

\see http://curl.haxx.se/libcurl/c/example.html
\see http://curl.haxx.se/libcurl/c/httpput.html
\see http://curl.haxx.se/libcurl/c/simplepost.html
\see http://curl.haxx.se/libcurl/c/postit2.html
*/

//    bool curlPOSTFile( const std::string& sURL, const boost::filesystem::path& /*filePathName*/ )
bool curlPOSTFile( const std::string& sURL )
{

    CURL *curl;

    CURLcode res = CURLE_OK;
////TODO: Use or remove this variable    static const char *postthis="moo mooo moo moo";
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
        just as well be a https:// URL if that is what should receive the
        data. */
        curl_easy_setopt(curl, CURLOPT_URL, sURL.c_str() );
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");

//		curl_easy_setopt(curl, CURLOPT_RETURNTRANSFER, 1 );
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    return res == CURLE_OK;
}


    /** Get handler context name from function name. Function name are assumed to
    follow the 'Crawler_TheHandlerContext_whatever' or
    'TEMPLATE_TheHandlerContext_whatever'
    Typically Crawler_DoSearch_beginMining and similar.*/
    std::string handlerContextFromName(const std::string& sFunctionName)
    {
        string::size_type p1 = sFunctionName.find("__");
        string::size_type p2 = sFunctionName.rfind("__");
        if ( p1 == string::npos || p2 == string::npos || p1 == p2 )
            return "";

        return sFunctionName.substr(p1+2, p2 - p1 -2);
    }

    QByteArray readResourceFile(const QString path)
    {
        QFile file(path); // ":/jquery.min.js", ":/qtwebchannel/qwebchannel.js"
        if (file.open(QIODevice::ReadOnly)) {
            return file.readAll();
        }
        qDebug() << "ERROR loading resource file: " << path << "\n";
        return QByteArray{};

    }


} // END namespace crawl

