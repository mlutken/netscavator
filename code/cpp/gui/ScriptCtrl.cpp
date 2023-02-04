#include "ScriptCtrl.h"

#include <Configuration.h>
#include <Globals.h>
#include <php_embedding/php_embedding_utils.h>
#include <php_embedding/php_embedding_callbacks.h>

const int MAX_ARGS = 10;

ScriptCtrl::ScriptCtrl(QObject *parent) :
    QObject(parent)
{
}

ScriptCtrl::~ScriptCtrl()
{
    closeScript();
}

void ScriptCtrl::restartScript ()
{
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();

    char** argvPhp;
    int  argcPhp;

    argvPhp = allocateArrayOfStrings(MAX_ARGS, 256);
    c->getScriptArgvArgc( argcPhp, argvPhp );

    shutdownPhp();
    startupPhpScript(c->valueStrGet("php-ini-path").c_str(), argcPhp, argvPhp );
    freeArrayOfStrings( argvPhp, MAX_ARGS );

    executePhpString("require_once 'webminer.php';");

}

QString ScriptCtrl::getCrawlerStartPage ()
{
	return "TODO: implement ScriptCtrl::getCrawlerStartPage";
}

void ScriptCtrl::closeScript ()
{
    shutdownPhp();
}

