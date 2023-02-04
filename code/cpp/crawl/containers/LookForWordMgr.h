#ifndef LOOKFORWORDMGR_H
#define LOOKFORWORDMGR_H

#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include <QString>

namespace crawl {

class LookForWordMgr
{
public:
    class ReferenceWordData {
    public:
        struct LookForWord {
            LookForWord (const QString& word, const QString &compareFun, int nodeTypes)
                : m_word(word), m_wordLower(word.toLower()), m_compareFun(compareFun), m_nodeTypes(nodeTypes) {}
            QString m_word;
            QString m_wordLower;
            QString m_compareFun;
            int m_nodeTypes;
            friend bool operator ==(const LookForWord& lhs, const LookForWord& rhs) {
                return lhs.m_word == rhs.m_word && lhs.m_compareFun == rhs.m_compareFun && lhs.m_nodeTypes == rhs.m_nodeTypes;
            }
        };

        using iterator          = std::vector<LookForWord>::iterator;
        using const_iterator    = std::vector<LookForWord>::const_iterator;

        // ----------------------
        // --- WordData class ---
        // ----------------------
        ReferenceWordData () = default;

        iterator        begin   ()          { return m_lookForWords.begin();    }
        iterator        end     ()          { return m_lookForWords.end();      }
        const_iterator  begin   () const    { return m_lookForWords.begin();    }
        const_iterator  end     () const    { return m_lookForWords.end();      }

        void            clear   ()          { m_lookForWords.clear();}

        void addLookForWord(const QString& word, const QString &compareFun, int nodeTypes)
        {
            const LookForWord lfw(word, compareFun, nodeTypes);
            auto it = std::find(m_lookForWords.begin(), m_lookForWords.end(), lfw);
            if (it != m_lookForWords.end())
                *it = std::move(lfw);
            else
                m_lookForWords.push_back(std::move(lfw));
        }

        void removeLookForWord(const QString& word)
        {
            auto fnRemove = [word] (const LookForWord& lfw) {
                return lfw.m_word == word;
            };

            auto it = std::remove_if(m_lookForWords.begin(), m_lookForWords.end(), fnRemove);
            m_lookForWords.erase(it, m_lookForWords.end());
        }

        // ------------
        // --- DATA ---
        // ------------
    private:
        // Configuration data
        QString                     m_referenceName;    // Output or action name like used in outputValueFind etc...
        std::vector<LookForWord>    m_lookForWords;     // Words to associate/look for for the reference name
        std::set<QString>           m_exceptions;       // If current value is one of these, don't match. For example if word is 'fork' we add 'fork material' as exception

    };

    // ----------------------
    // --- LookForWordMgr ---
    // ----------------------
    LookForWordMgr();
    void                clear                       ();
    void                clear                       (const QString& referenceName);
    void                addLookForWord              (const QString& referenceName, const QString& word, const QString& compareFun, int nodeTypes);
    void                removeLookForWord           (const QString& referenceName, const QString& word);

    ReferenceWordData* operator[]                   (const QString& referenceName);
    const ReferenceWordData* operator[]             (const QString& referenceName) const;

    void                getDataFunctionSet          (const std::string& getDataFunction);
    std::string         getDataFunction             () const;
    std::string         getDataFallbackFunction     () const;
    void                getDataFallbackFunctionSet  (const std::string& getDataFallbackFunction);
    std::string         lfwPreSequence              () const;
    void                lfwPreSequenceSet           (const std::string& lfwPreSequence);
    std::string         lfwPostSequence             () const;
    void                lfwPostSequenceSet          (const std::string& lfwPostSequence);

    std::string         lfwStartPosDomSeq           () const;
    void                lfwStartPosDomSeqSet        (const std::string& lfwStartPosDomSeq);
    std::string         lfwStopPosDomSeq            () const;
    void                lfwStopPosDomSeqSet         (const std::string& lfwStopPosDomSeq);

private:
    std::map<QString, ReferenceWordData>    m_refNameLookForWordMap;    // Words to look for

    // The (PHP) function to call to get the actual data for the ref-name(output/action name). If no function is defined
    // we use the default strategy, which is:
    // case 'iequals' the look-for-word: We advance to next TEXT node and use that as value
    // case 'istartsWith' the look-for-word: We use current node, but remove the look-for-word plus any trailing colon ':'
    std::string         m_getDataFunction;
    std::string         m_getDataFallbackFunction;  // Same as above, but only called if default handling yields empty string value.
    std::string         m_lfwPreSequence;
    std::string         m_lfwPostSequence;
    std::string         m_lfwStartPosDomSeq;   // DOM sequence to find lfw start pos
    std::string         m_lfwStopPosDomSeq;    // DOM sequence to find lfw stop pos

};
} // END namespace crawl

#endif // LOOKFORWORDMGR_H
