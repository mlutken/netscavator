#include "ScriptExecutor.h"

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <QThread>

#include <filesystem/cpaf_file_directory_functions.h>

#include <Configuration.h>
#include <Globals.h>
#include <ScriptMinerIF.h>
#include <utils/utils.h>
#include <php_embedding/php_embedding_utils.h>
#include <php_embedding/php_embedding_callbacks.h>
#include <scriptcrawl_private_php.h>

const int MAX_ARGS = 10;


using namespace boost::algorithm;
using namespace std;

namespace crawl {

ScriptExecutor::ScriptExecutor(QObject *parent)
    : QObject(parent),
      m_scriptingClassIF(createPhpScriptingClass())
{

}

ScriptExecutor::~ScriptExecutor()
{
    shutdown();
}

boost::shared_ptr<ScriptingClassIF> ScriptExecutor::scriptingClass()
{
    return m_scriptingClassIF;
}

const boost::shared_ptr<ScriptingClassIF> ScriptExecutor::scriptingClass() const
{
    return m_scriptingClassIF;
}


void ScriptExecutor::startup(const boost::shared_ptr<ScriptMinerIF>& scriptMiner)
{
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();

    char** argvPhp;
    int  argcPhp;

    argvPhp = allocateArrayOfStrings(MAX_ARGS, 256);
    c->getScriptArgvArgc( argcPhp, argvPhp );

    shutdown();
    startupPhpScript(c->valueStrGet("php-ini-path").c_str(), argcPhp, argvPhp );
    freeArrayOfStrings( argvPhp, MAX_ARGS );

    executePhpString("require_once 'webminer.php';");
    if (scriptMiner)
        setMinerPointerRaw(scriptMiner.get());
}



void ScriptExecutor::shutdown()
{
    shutdownPhp();
}

void ScriptExecutor::loadMinerCode(const boost::shared_ptr<ScriptMinerIF>& scriptMiner,
                                   const QString& scriptCode, const QString& scriptAbsPath)
{
    using namespace std;

    if (scriptMiner) {
        scriptMiner->clearForReloadScript();
    }
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();
    std::string sPhpScript = scriptCode.toUtf8().data();
    erase_first( sPhpScript, "<?php" );
    erase_last( sPhpScript, "?>" );

    shutdownPhp();
    char** argvPhp;
    int  argcPhp;

    argvPhp = allocateArrayOfStrings(MAX_ARGS, 256);
    c->getScriptArgvArgc( argcPhp, argvPhp );

    startupPhpScript(c->valueStrGet("php-ini-path").c_str(), argcPhp, argvPhp );
    freeArrayOfStrings( argvPhp, MAX_ARGS );

    // --- Add to ini path ---
    boost::filesystem::path scriptPath( scriptAbsPath.toUtf8().data() );
    if ( !scriptPath.empty() ) {
        std::string sIni = getStandardPhpIncludePathString( scriptPath );
        iniFileAddIncludePath( sIni.c_str() );
    }
    // ---

    executePhpString("require_once 'webminer.php';");

    if (scriptMiner) {
        setMinerPointerRaw( scriptMiner.get());
    }
    executePhpString( sPhpScript.c_str() );
}

void ScriptExecutor::loadMinerCode (boost::shared_ptr<ScriptMinerIF> scriptMiner, const QString& scriptAbsPath)
{
    const string path = scriptAbsPath.toUtf8().data();
    const QString scriptCode = QString::fromUtf8(cpaf::filesystem::read_file(path).c_str());
    loadMinerCode(scriptMiner, scriptCode, scriptAbsPath);
}

void ScriptExecutor::loadMinerCode (const QString& scriptAbsPath)
{
    loadMinerCode(boost::shared_ptr<ScriptMinerIF>(), scriptAbsPath);
}

} // namespace crawl

