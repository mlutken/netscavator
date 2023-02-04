#include "LookForWordMgr.h"

#include <iostream>

namespace crawl {

LookForWordMgr::LookForWordMgr()
{

}

void LookForWordMgr::clear()
{
    m_refNameLookForWordMap.clear();
}

void LookForWordMgr::clear(const QString& referenceName)
{
    m_refNameLookForWordMap[referenceName].clear();
}


void LookForWordMgr::addLookForWord(const QString& referenceName, const QString& word, const QString &compareFun, int nodeTypes)
{
    m_refNameLookForWordMap[referenceName].addLookForWord(word, compareFun, nodeTypes);
}

void LookForWordMgr::removeLookForWord(const QString& referenceName, const QString& word)
{
    m_refNameLookForWordMap[referenceName].removeLookForWord(word);
}

LookForWordMgr::ReferenceWordData* LookForWordMgr::operator[](const QString& referenceName)
{
    auto it = m_refNameLookForWordMap.find(referenceName);
    if (it == m_refNameLookForWordMap.end())
        return nullptr;
    else
        return &(it->second);
}

const LookForWordMgr::ReferenceWordData* LookForWordMgr::operator[](const QString &referenceName) const
{
    const auto it = m_refNameLookForWordMap.find(referenceName);
    if (it == m_refNameLookForWordMap.end())
        return nullptr;
    else
        return &(it->second);
}

void LookForWordMgr::getDataFunctionSet(const std::string& findDataDomPosFunction)
{
    m_getDataFunction = findDataDomPosFunction;
}

std::string LookForWordMgr::getDataFunction() const
{
    return m_getDataFunction;
}

std::string LookForWordMgr::getDataFallbackFunction() const
{
    return m_getDataFallbackFunction;
}

void LookForWordMgr::getDataFallbackFunctionSet(const std::string& getDataFallbackFunction)
{
    m_getDataFallbackFunction = getDataFallbackFunction;
}

std::string LookForWordMgr::lfwPreSequence() const
{
    return m_lfwPreSequence;
}

void LookForWordMgr::lfwPreSequenceSet(const std::string& lfwPreSequence)
{
    m_lfwPreSequence = lfwPreSequence;
}

std::string LookForWordMgr::lfwPostSequence() const
{
    return m_lfwPostSequence;
}

void LookForWordMgr::lfwPostSequenceSet(const std::string& lfwPostSequence)
{
    m_lfwPostSequence = lfwPostSequence;
}

std::string LookForWordMgr::lfwStartPosDomSeq() const
{
    return m_lfwStartPosDomSeq;
}

void LookForWordMgr::lfwStartPosDomSeqSet(const std::string& lfwStartPosDomSeq)
{
    m_lfwStartPosDomSeq = lfwStartPosDomSeq;
}

std::string LookForWordMgr::lfwStopPosDomSeq() const
{
    return m_lfwStopPosDomSeq;
}

void LookForWordMgr::lfwStopPosDomSeqSet(const std::string& lfwStopPosDomSeq)
{
    m_lfwStopPosDomSeq = lfwStopPosDomSeq;
}


} // END namespace crawl
