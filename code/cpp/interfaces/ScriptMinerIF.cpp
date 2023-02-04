#include "ScriptMinerIF.h"

#include <iostream>
#include "WebBrowserIF.h"
#include <Configuration.h>



namespace crawl {

    ScriptMinerIF::ScriptMinerIF()
        : m_pConfig  ( new Configuration )
    {
    }

    ScriptMinerIF::ScriptMinerIF(
            boost::shared_ptr<ScriptingClassIF> pScriptClass
            , boost::shared_ptr<Configuration> pConfig )
        :  m_pConfig  (pConfig),
           m_pScriptingClassIF(pScriptClass)
    {
    }

    ScriptMinerIF::~ScriptMinerIF  ()
    {
    }

    void ScriptMinerIF::scriptingClassSet ( boost::shared_ptr<ScriptingClassIF> pScriptClass )
    {
        m_pScriptingClassIF = pScriptClass;
    }

    void ScriptMinerIF::configurationSet ( boost::shared_ptr<Configuration> pConfig  )
    {
        m_pConfig = pConfig;
    }

    void ScriptMinerIF::scriptHtmlEntitiesReplaceAdd(const std::string& lookFor, const std::string& replaceWith)
    {
        if(webBrowser()) {
            webBrowser()->scriptHtmlEntitiesReplaceAdd(lookFor, replaceWith);
        }
    }

    void ScriptMinerIF::scriptHtmlEntitiesReplaceClear()
    {
        if(webBrowser()) {
            webBrowser()->scriptHtmlEntitiesReplaceClear();
        }
    }

    // --------------------
    // --- PUBLIC: Info ---
    // --------------------
    boost::shared_ptr<ScriptingClassIF>         ScriptMinerIF::scriptingClass()
    {
        return m_pScriptingClassIF;
    }

    const boost::shared_ptr<ScriptingClassIF>   ScriptMinerIF::scriptingClass() const
    {
        return m_pScriptingClassIF;
    }


    const boost::shared_ptr<Configuration>  ScriptMinerIF::config() const
    {
        return m_pConfig;
    }

    boost::shared_ptr<Configuration>  ScriptMinerIF::config()
    {
        return m_pConfig;
    }

    bool ScriptMinerIF::runModeCreator() const
    {
        return crawl::runModeCreator(runMode());
    }

    void ScriptMinerIF::domContinueSearch()
    {
        domStartPosSet( domContinuePos() );
    }

    std::vector<int> ScriptMinerIF::domFindAllPositions(const std::string& sSequence)
    {
        std::vector<int> v;
        int posSave = domPos();
        domNewSearch();
        while ( domFindNext( sSequence ) ) {
            v.push_back(domPos());
        }
        domPosSet( posSave );
        return v;
    }

    int ScriptMinerIF::lfwDomFind(const std::string& referenceName)
    {
        domNewSearch();
        int pos = lfwDomFindNext(referenceName);

        return pos;
    }

    std::string ScriptMinerIF::lfwOutputValueFind(const std::string& referenceName)
    {
        domNewSearch();
        std::string val = lfwOutputValueFindNext(referenceName);
        return val;
    }

    std::vector<int> ScriptMinerIF::lfwDomFindAllPositions(const std::string& referenceName)
    {
        std::vector<int> v;
        int posSave = domPos();
        domNewSearch();
        while ( lfwDomFindNext( referenceName ) ) {
            v.push_back(domPos());
        }
        domPosSet( posSave );
        return v;
    }

    int ScriptMinerIF::lfwDomStartPos() const
    {
        return m_lfwDomStartPos;
    }

    void ScriptMinerIF::lfwDomStartPosSet(int pos)
    {
        m_lfwDomStartPos = pos;
    }

    int ScriptMinerIF::lfwDomStopPos() const
    {
        return m_lfwDomStopPos;
    }

    void ScriptMinerIF::lfwDomStopPosSet(int pos)
    {
        m_lfwDomStopPos = pos;
    }

    int ScriptMinerIF::configDelayPageLoadedTime() const
    {
        auto browser = webBrowser();
        if (browser)
            return browser->delayPageLoadedSignalTimeInMs();
        return -1;
    }

    void ScriptMinerIF::configDelayPageLoadedTimeSet(int milliseconds)
    {
        auto browser = webBrowser();
        if (browser) {
            browser->delayPageLoadedSignalTimeInMsSet(milliseconds);
        }
    }


} //END namespace crawl





