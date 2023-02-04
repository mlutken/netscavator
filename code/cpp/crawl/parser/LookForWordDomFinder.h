#ifndef CRAWL_LOOKFORWORDDOMFINDER_H
#define CRAWL_LOOKFORWORDDOMFINDER_H

#include <string>
#include <QString>
#include <containers/LookForWordMgr.h>

class ScriptMiner;


namespace crawl {

/** Main class to handle look for words when adding and executing the parser looking for the words
and the associated data. */
class LookForWordDomFinder
{
public:
    explicit LookForWordDomFinder(ScriptMiner* miner);
    void lfwInitPageLoaded      (LookForWordMgr* mgr);
    int domFindNext             (LookForWordMgr* mgr, const QString& referenceName);
    int outputValueFindNext     (std::string& outputValue, LookForWordMgr* mgr, const QString& referenceName);

    bool matchWholeWordsOnly() const;
    void matchWholeWordsOnlySet(bool matchWholeWordsOnly);

private:
    std::string  defaultOutputValueGet(const LookForWordMgr::ReferenceWordData& wd,
                                       const LookForWordMgr::ReferenceWordData::LookForWord& lfw,
                                       const std::string& postSeq) const;
    LookForWordMgr::ReferenceWordData* referenceWordData(LookForWordMgr* mgr, const QString& referenceName);
    bool hasPhpGetDataFunction(LookForWordMgr* mgr) const;
    bool hasPhpGetDataFallbackFunction(LookForWordMgr* mgr) const;

    ScriptMiner*    m_miner;
    bool            m_lfwEnabled = true;
    int             m_lfwStartPos = 0;
    int             m_lfwStopPos = 0;
    bool            m_matchWholeWordsOnly = false;

};

} // namespace crawl

#endif // CRAWL_LOOKFORWORDDOMFINDER_H
