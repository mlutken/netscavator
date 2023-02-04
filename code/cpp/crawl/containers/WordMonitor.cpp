#include "WordMonitor.h"

namespace crawl {

WordMonitor::WordMonitor()
{

}

void WordMonitor::clear()
{
    m_refNameLookForWordMap.clear();
}

void WordMonitor::clearReferenceName(const QString& referenceName)
{
    m_refNameLookForWordMap[referenceName].clear();
}

void WordMonitor::addTokenWordDomPos(const QString &word, int domPos)
{
    // Add case sensitive
    {
        std::vector<int>& vec = m_tokenWordDomPositionsMap[word];
        const bool empty = vec.empty();
        if ( empty || (!empty && vec.back() != domPos))
            vec.push_back(domPos);
    }
    // Add case in-sensitive
    {
        std::vector<int>& vec = m_tokenWordDomPositionsCIMap[word.toLower()];
        const bool empty = vec.empty();
        if ( empty || (!empty && vec.back() != domPos))
            vec.push_back(domPos);
    }
}

void WordMonitor::addLookForWord(const QString& referenceName, const QString& word, const QString &compareFun)
{
    m_refNameLookForWordMap[referenceName].addLookForWord(word, compareFun);
}

//WordMonitor::WordData* WordMonitor::parserLookupWord(const QString& word)
//{
//    const auto it = m_parserWordLookupCIMap.find(word.toLower());
//    if (it == m_parserWordLookupCIMap.end())
//        return nullptr;

//    WordData* wordDataPtr = it->second;

//    if (!wordDataPtr->parserLookupWord(word))
//        wordDataPtr = nullptr;

//    return wordDataPtr;
//}

WordMonitor::WordData* WordMonitor::operator[](const QString& referenceName)
{
    auto it = m_refNameLookForWordMap.find(referenceName);
    if (it == m_refNameLookForWordMap.end())
        return nullptr;
    else
        return &(it->second);
}

const WordMonitor::WordData* WordMonitor::operator[](const QString &referenceName) const
{
    const auto it = m_refNameLookForWordMap.find(referenceName);
    if (it == m_refNameLookForWordMap.end())
        return nullptr;
    else
        return &(it->second);
}

void WordMonitor::buildParserWordLookupMap()
{
    clearRuntimeData();
    m_parserWordLookupCIMap.clear();
    for (auto& pair : m_refNameLookForWordMap) {
        WordData* wordDataPtr = &pair.second;

        for (const auto& tw : *wordDataPtr)
            m_parserWordLookupCIMap[tw.m_word.toLower()] = wordDataPtr;
    }
}

void WordMonitor::clearRuntimeData()
{
    m_tokenWordDomPositionsMap.clear();
    m_tokenWordDomPositionsCIMap.clear();
    for (auto& pair : m_refNameLookForWordMap) {
        WordData* wordDataPtr = &pair.second;
        wordDataPtr->clearRuntimeData();
    }
}

QString WordMonitor::findDataDomPosFunction() const
{
    return m_findDataDomPosFunction;
}

void WordMonitor::findDataDomPosFunctionSet(const QString &findDataDomPosFunction)
{
    m_findDataDomPosFunction = findDataDomPosFunction;
}

} // END namespace crawl
