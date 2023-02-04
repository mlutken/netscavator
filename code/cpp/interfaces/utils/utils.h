#ifndef _CRAWL_UTILS_H_
#define _CRAWL_UTILS_H_

#include <string>
#include <QString>
#include <QUrl>
#include <boost/shared_ptr.hpp>
#include <filesystem/cpaf_file_directory_functions.h>

/** \unit utils.h
!!! Common utility functions

This file is (currently) the place to put common free functions. In
case this file starts getting full of different functions we MUST try to group
the functions into smaller group giving each group a new header and cpp file.

*/



namespace crawl {
    class ScriptingClassIF;

    QString         toQString   (const std::string& s);
    std::string     toString    (const QString& s);

    QUrl            toQUrl      (const std::string& url);
    std::string     toString    (const QUrl& url);

//    QByteArray      toQByteArray(const std::string& s);
//    std::string     toString    (const QByteArray& s);

    boost::shared_ptr<cpaf::filesystem::filepaths_t>
                getStandardPhpIncludePaths      ( boost::filesystem::path scriptFullPath );
    std::string getStandardPhpIncludePathString ( boost::filesystem::path scriptFullPath );


    void getUrlStartAndUrlSite ( boost::shared_ptr<ScriptingClassIF> pScriptingClass, const std::string& sMinerName
                                 ,  std::string& sUrlSite, std::string& sUrlStart );

    std::string  getMinerName   ( boost::shared_ptr<ScriptingClassIF> pScriptingClass );

    std::string thisThreadId();

//    bool curlPOSTFile( const std::string& sURL, const boost::filesystem::path& filePathName ) ;
    bool curlPOSTFile( const std::string& sURL/*, const boost::filesystem::path& filePathName */) ;


    std::string handlerContextFromName (const std::string& sFunctionName );
    QByteArray readResourceFile(const QString path);

} // END namespace crawl

#endif //_CRAWL_UTILS_H_

