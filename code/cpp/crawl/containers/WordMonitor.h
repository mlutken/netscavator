#ifndef WORDMONITOR_H
#define WORDMONITOR_H

#include <vector>
#include <map>

#include <QString>

namespace crawl {

class WordMonitor
{
public:
    class WordData {
    public:
        struct LookForWord {
            LookForWord (const QString& word, const QString &compareFun) : m_word(word), m_compareFun(compareFun) {}
            QString m_word;
            QString m_compareFun;
        };

        struct WordPos {
            WordPos (const QString& wordMatched, int domPos) : m_wordMatched(wordMatched), m_domPos(domPos) {}
            QString m_wordMatched;
            int     m_domPos;
        };

        using iterator = std::vector<LookForWord>::iterator;
        using const_iterator = std::vector<LookForWord>::const_iterator;

        // ----------------------
        // --- WordData class ---
        // ----------------------
        WordData () = default;

        iterator        begin()             { return m_lookForWords.begin(); }
        iterator        end()               { return m_lookForWords.end(); }
        const_iterator  begin() const       { return m_lookForWords.begin(); }
        const_iterator  end() const         { return m_lookForWords.end(); }

        bool            foundInDom() const  { return !m_domPositionsWord.empty();}
        void            clear()             { m_lookForWords.clear();}
        void            clearRuntimeData()  { m_domPositionsWord.clear();        }

        void addLookForWord(const QString& word, const QString &compareFun)
        {
            auto fn = [word] (const WordData::LookForWord& twLhs) -> bool {
                return twLhs.m_word == word;
            };

            auto it = std::find_if(m_lookForWords.begin(), m_lookForWords.end(), fn);
            if (it != m_lookForWords.end())
                m_lookForWords.push_back(WordData::LookForWord(word,compareFun));

        }

//        bool parserLookupWord (const QString &word) const {
//            const auto wordLower = word.toLower();
//            bool found = true;
//            // Check if word is to be compared case sensitive
//            for ( const auto& tw: m_tokenWords) {
//                if (tw.m_word.toLower() == wordLower) {
//                    if (tw.m_cs && tw.m_word != word)
//                        found = false;
//                    break;
//                }
//            }
//            return found;
//        }

        void addMatch(const QString& wordMatched, int domPos) {
            m_domPositionsWord.push_back(WordPos(wordMatched, domPos));
        }

        // ------------
        // --- DATA ---
        // ------------
    private:
        // Configuration data
        QString                     m_referenceName;    // Output or action name like used in outputValueFind etc...
        std::vector<LookForWord>    m_lookForWords;     // Words to associate/look for for the reference name

        // Runtime data
        std::vector<WordPos>    m_domPositionsWord; // Dom positions where we found any of the words to look for
    };

    // -------------------
    // --- WordMonitor ---
    // -------------------
    WordMonitor();

    void clear();
    void clearReferenceName (const QString& referenceName);
    void addTokenWordDomPos (const QString& word, int domPos);
    void addLookForWord(const QString& referenceName, const QString& word, const QString& compareFun);
//    WordData* parserLookupWord(const QString& word);


    WordData* operator[](const QString& referenceName);
    const WordData* operator[](const QString& referenceName) const;


    QString findDataDomPosFunction() const;
    void findDataDomPosFunctionSet(const QString &findDataDomPosFunction);


    /// Build the lookup map with (string)words linking 'back' WordData for use when
    /// building the linear DOM.
    void buildParserWordLookupMap();
    void clearRuntimeData();

private:

    using TokenWordDomPosMap = std::map<QString, std::vector<int>>;
    std::map<QString, WordData>     m_refNameLookForWordMap;    // Words to look for
    std::map<QString, WordData*>    m_parserWordLookupCIMap;    // Each word(string) to look for is 'linked' to it's WordData : Case insensitive
    TokenWordDomPosMap              m_tokenWordDomPositionsMap;    // All words in 'text' nodes (TEXT_NODE+alt nodes etc with text): Case-Sensitive
    TokenWordDomPosMap              m_tokenWordDomPositionsCIMap;  // All words in 'text' nodes (TEXT_NODE+alt nodes etc with text): Case-Insensitive

    // The (PHP) function to call to get the actual data for the ref-name(output/action name). If no function is defined
    // we use the default strategy, which is to advenace until next TEXT node in th e dom tree.
    QString                         m_findDataDomPosFunction;

};
} // END namespace crawl

#endif // WORDMONITOR_H
