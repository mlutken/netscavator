#include "LookForWordDomFinder.h"
#include <iostream>
#include <interfaces/utils/utils.h>
#include <interfaces/ScriptMinerIF.h>
#include <interfaces/ScriptingClassIF.h>
#include <parser/DomSeq.h>
#include <ScriptMiner.h>

namespace crawl {


LookForWordDomFinder::LookForWordDomFinder(ScriptMiner* miner)
    : m_miner(miner)
{

}

void LookForWordDomFinder::lfwInitPageLoaded(LookForWordMgr* mgr)
{
    if (!mgr)
        return;

    const std::string startPosSeq = mgr->lfwStartPosDomSeq();
    const std::string stopPosSeq = mgr->lfwStopPosDomSeq();
    m_lfwStartPos = 0;
    m_lfwStopPos = 0; // Means end of dom when it is set in LinearDomSearch::setStopPos()
    m_lfwEnabled = true;

    if (startPosSeq != "") {
        m_lfwStartPos = m_miner->domFindPos(startPosSeq);
        m_lfwEnabled = m_lfwStartPos != 0;
    }
    if (m_lfwEnabled && stopPosSeq != "") {
        m_lfwStopPos = m_miner->domFindPos(stopPosSeq);
        m_lfwEnabled = m_lfwStopPos != 0;
    }
}

int LookForWordDomFinder::domFindNext(LookForWordMgr* mgr, const QString& referenceName)
{
    LookForWordMgr::ReferenceWordData* wd = referenceWordData(mgr, referenceName);
    if (!wd ||!m_lfwEnabled)
        return 0;

    // Set special look-for-word dom start, stop pos if not zero
    int startPosSave = m_miner->domStartPos();
    int stopPosSave = m_miner->domStopPos();

    m_miner->domStartPosSet(m_lfwStartPos);
    m_miner->domStopPosSet(m_lfwStopPos);

    int posStart = m_miner->domPos();

    // int iCount, const std::string& sPattern, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes, const std::string& sCommaChar
    int pos = 0;
    for ( const auto& lfw : *wd) {
        m_miner->domPosSet(posStart);
        auto seq = DomSeq( 1, toString(lfw.m_word), toString(lfw.m_compareFun), 0, lfw.m_nodeTypes, "," );
        pos = m_miner->domSeqFindNextParams	( 1, seq, "", crawl::DomNodeTypes::ALL_NODE_TYPES );
        if (pos)
            break;
    }

    // Restore any original domStartPos
    m_miner->domStartPosSet(startPosSave);
    m_miner->domStopPosSet(stopPosSave);
    return pos;
}

int LookForWordDomFinder::outputValueFindNext(std::string& outputValue, LookForWordMgr* mgr, const QString& referenceName)
{

    using namespace std;
    LookForWordMgr::ReferenceWordData* wd = referenceWordData(mgr, referenceName);
    if (!wd ||!m_lfwEnabled)
        return 0;

    // Set special look-for-word dom start, stop pos if not zero
    int startPosSave = m_miner->domStartPos();
    int stopPosSave = m_miner->domStopPos();

    m_miner->domStartPosSet(m_lfwStartPos);
    m_miner->domStopPosSet(m_lfwStopPos);

    const bool hasPhpGetDataFun = hasPhpGetDataFunction(mgr);
    const bool hasPhpGetDataFallbackFun = hasPhpGetDataFallbackFunction(mgr);
    const std::string getDataFun = mgr->getDataFunction();
    const std::string getDataFallbackFun = mgr->getDataFallbackFunction();

    int posStart = m_miner->domPos();
    int pos = 0;
    outputValue = "";
    for ( const auto& lfw : *wd) {
        m_miner->domPosSet(posStart);

        std::string sequence = toString(lfw.m_word);
        const std::string preSeq = mgr->lfwPreSequence();
        const std::string postSeq = mgr->lfwPostSequence();
        int nodeTypes = lfw.m_nodeTypes;

        if (!preSeq.empty()) {
            sequence = preSeq + ", " + sequence;
            nodeTypes = crawl::DomNodeTypes::ALL_NODE_TYPES;
        }
        if (!postSeq.empty()) {
            sequence = sequence + ", " + postSeq;
            nodeTypes = crawl::DomNodeTypes::ALL_NODE_TYPES;
        }

        auto seq = DomSeq( 1, sequence, toString(lfw.m_compareFun), 0, nodeTypes, "," );

        bool done = false;
        while (!done) {
            done = true;
            pos = m_miner->domSeqFindNextParams	( 1, seq, "", crawl::DomNodeTypes::ALL_NODE_TYPES );
            if (pos) {
                if (hasPhpGetDataFun)
                    outputValue = m_miner->scriptingClass()->callScriptFunction_String(getDataFun, sequence);
                else
                    outputValue = defaultOutputValueGet(*wd, lfw, postSeq);
                if (outputValue == ""){
                    if (hasPhpGetDataFallbackFun)
                        outputValue = m_miner->scriptingClass()->callScriptFunction_String(getDataFallbackFun, sequence);

                    if (outputValue == "")
                        outputValue = m_miner->valueGet();
                }
                if (outputValue == "__TRY_NEXT_MATCH__"){
                    outputValue = "";
                    done = false;
                }
                if (outputValue == "__NO_VALUE__"){
                    outputValue = "";
                    pos = 0;
                }
                else {
                    pos = m_miner->domPos();
                }
////                break;
            }
            else {
                done = true;
            }
        }
        if (pos)
            break;

    }

    // Restore any original domStartPos, domStopPos
    m_miner->domStartPosSet(startPosSave);
    m_miner->domStopPosSet(stopPosSave);
    return pos;
}

std::string LookForWordDomFinder::defaultOutputValueGet(
        const LookForWordMgr::ReferenceWordData& /*wd*/,
        const LookForWordMgr::ReferenceWordData::LookForWord& lfw,
        const std::string &postSeq) const
{
    using namespace std;
    std::string val = "";

    if (!postSeq.empty()) {
        val = m_miner->valueGet(); // If we have a post seq defined assume it ends exactly at the correct position!
    }
    else {
        QString qval = toQString(m_miner->valueGet());

        // Current DOM value is same as look-for-word
        if (qval.compare(lfw.m_word, Qt::CaseInsensitive) == 0) {
            m_miner->domStep(1, DomNodeTypes::TEXT);
            val = m_miner->valueGet();
        }
        else {

            QString qvalLower = qval.toLower();
            auto wordPos = qvalLower.indexOf(lfw.m_wordLower, 0);

            if (wordPos == 0) {
                // Current DOM value begins with look-for-word

                // See if we should remove the lookForWord (lwf) from the beginning
                // of the result value. We want to do that if res-value begins with
                // lfw followed by a colon or full-stop or semi-colon possibly with leading blanks.
                // So for example: lfw = 'tyres'
                //  - Do remove : 'TYRES Michelin super awsome tyres'
                //  - Do remove : 'Tyres: Michelin super awsome tyres'
                //  - Do remove : 'Tyres : Michelin super awsome tyres'
                //  - Do NOT remove : 'Tyres are super awsome from Michelin'
                int lenRemove = 0;  // How much to remove

                const int lfwSize = lfw.m_word.size();
                int pos = lfwSize;

                const int valueSize = qvalLower.size();
                if (pos < valueSize) {
                    auto ch = qvalLower[pos];
                    if (ch == ':' || ch == '.' || ch == ';')
                        lenRemove = pos +1;
                    else if (ch.isSpace()) {
                        while ( ++pos < valueSize && qvalLower[pos].isSpace()); // Skip blanks
                        ch = qvalLower[pos];
                        if (ch == ':' || ch == '.' || ch == ';')
                            lenRemove = pos +1;


                    }
                }
                if (lenRemove == 0) {
                    // Check all uppercase version
                    if (qval.indexOf(lfw.m_word.toUpper(), 0) == 0) {
                        lenRemove = lfw.m_word.length();
                    }
                }

                // Do remove first part of string - lenRemove can be zero
                qval = qval.remove(wordPos, lenRemove).trimmed();
            }
            val = qval.trimmed().toUtf8().data();

            // If we really only have 'word:' (the word followed by colon) we try the next text node
            if (val.empty()) {
                m_miner->domStep(1, DomNodeTypes::TEXT);
            }
            else if (qval.indexOf(' ') == -1) {     // lfw is part of current value in some way, like it typically begins with the lfw
                                                    // For example currentValue = "Hjulstørrelse" and lfw = "hjul"
                                                    // This if checks to see if in this case currentValue is only one word that contains lfw
                val = "__NO_VALUE__";               // In this case we do NOT want to use it!
            }
            else if (m_matchWholeWordsOnly) {
                val = "__TRY_NEXT_MATCH__";
            }

        }
    }
    return val;

}

LookForWordMgr::ReferenceWordData* LookForWordDomFinder::referenceWordData(LookForWordMgr* mgr, const QString& referenceName)
{
    if (!mgr)
        return 0;
    auto& lfwMgr = *mgr;
    return lfwMgr[referenceName];
}

bool LookForWordDomFinder::hasPhpGetDataFunction(LookForWordMgr* mgr) const
{
    // Assume mgr is not nullptr since this is an internal helper function
    return m_miner->scriptingClass()->scriptFunctionExists(mgr->getDataFunction());
}

bool LookForWordDomFinder::hasPhpGetDataFallbackFunction(LookForWordMgr* mgr) const
{
    // Assume mgr is not nullptr since this is an internal helper function
    return m_miner->scriptingClass()->scriptFunctionExists(mgr->getDataFallbackFunction());
}

bool LookForWordDomFinder::matchWholeWordsOnly() const
{
    return m_matchWholeWordsOnly;
}

void LookForWordDomFinder::matchWholeWordsOnlySet(bool matchWholeWordsOnly)
{
    m_matchWholeWordsOnly = matchWholeWordsOnly;
}


} // namespace crawl

