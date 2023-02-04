#ifndef _CRAWL_NAVIGATE_STATE_BASE_H_
#define _CRAWL_NAVIGATE_STATE_BASE_H_

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <boost/filesystem/path.hpp>
#include <boost/cstdint.hpp>
#include <loki/Visitor.h>
#include <cpaf_compression_functions.h>


class ScriptMiner;
namespace crawl {

class NavigateStateBase : public Loki::BaseVisitable<void>
{
public:
    // -----------------------
    // --- Enums, typedefs ---
    // -----------------------
    enum ResourceTypeE      { resNoneE, resLocalE, resHttpE, resFtpE  };
    enum ResourceFileTypeE  { resFileTxtE, resFileGzE      };

    typedef     std::vector<std::string>    StrVecT;

    /** Hold the info for one option. */
    struct OptionT
    {
        int             iCount;
        std::string     sValue;
        std::string     sSearchFor;
        OptionT( int count, const std::string& value, const std::string& searchFor )
            : iCount(count), sValue(value), sSearchFor(searchFor) {}
    };

    // -----------------
    // --- Constants ---
    // -----------------
    static const int     InvalidOptionIndexE;
    static const int     FirstOptionIndexE;
    static const int     UseDefaultCountParameter;

    // ------------------------------------
    // --- Constructor / Init Functions ---
    // ------------------------------------
                NavigateStateBase();
    virtual		~NavigateStateBase();

    void        setScriptMiner (const ScriptMiner* pScriptMiner) { m_pScriptMiner = pScriptMiner; }
    bool        needValidDomPosToExecute() const { return do_needValidDomPosToExecute(); }

    // -------------------------------
    // --- PUBLIC: State functions ---
    // -------------------------------
    boost::int64_t		nextOption			();
    int                 optionToIndex       ( const std::string& sOption	)	const;
    void                start               ();

    // ------------------------------
    // --- PUBLIC: Info functions ---
    // ------------------------------
    boost::int64_t      firstOptionIndex    () const { return hlp_firstOptionIndex();    }
    boost::int64_t      lastOptionIndex     () const { return do_lastOptionIndexGet();   }
    std::string         firstOption         () const { return do_indexToOption(firstOptionIndex());   }
    std::string         lastOption          () const { return do_indexToOption(lastOptionIndex());    }


    const std::string&  endOption           () const { return m_sEndOption;      }
    boost::int64_t      beginOptionIndex    () const;
    boost::int64_t      endOptionIndex      () const;
    boost::int64_t      numOptions          () const;
    bool                isOption            ( const std::string& sOption ) const;



    void                currentDomTextValue     ( const std::string& sDomVal );
    const std::string&	currentDomTextValue     () const;
    void                currentDomValue         ( const std::string& sDomVal );
    const std::string&	currentDomValue         () const;
    std::string         currentOption           () const;
    void                currentOptionSet        ( const std::string& sOption );
    std::string         currentSearchFor        () const;
    int                 currentCount            () const;
    void                currentOptionIndexSet   ( boost::int64_t iIndex );
    boost::int64_t		currentOptionIndex      () const;
    bool                atEndOption             () const  { return hlp_atEndOption(); }


    // -----------------------------------
    // --- PUBLIC: Set state functions ---
    // -----------------------------------
    void                optionAdd           ( int iCount, const std::string& sValue, const std::string& sSearchFor  );
    void				endOptionSet        ( const std::string& sOption );
    void				endOptionIndexSet   ( boost::int64_t iIndex  ) { do_endOptionIndexSet ( iIndex ); }



    // -----------------------------------
    // --- PUBLIC: Attribute functions ---
    // -----------------------------------
    void		attributeSet            ( const std::string& sOption, const std::string& sAttributeName, const std::string& sAttributeValue );
    std::string	attributeGet            ( const std::string& sOption, const std::string& sAttributeName );
    std::string	attributeGet            ( const std::string& sAttributeName );
    void        attributeNamesCreate    ( const std::vector<std::string>& attributeNames);
    void        attributesAdd           ( const std::vector<std::string>& attributeValues );
    void        autoInputIncreaseLength ( bool bDoIncreaseLength )          { m_bAutoInputDoIncreaseLength = bDoIncreaseLength; }
    bool        autoInputIncreaseLength ( )                        const    { return m_bAutoInputDoIncreaseLength ; }
    void        allMoreSignificantStatesAtEnd  ( bool bHigherAtEnd )        { m_bAllMoreSignificantStatesAtEnd = bHigherAtEnd; }
    bool        allMoreSignificantStatesAtEnd  ( )                 const    { return m_bAllMoreSignificantStatesAtEnd ; }
    StrVecT     attributeNames          () const;
    void        setAttributeNames       (const StrVecT &attributeNames);


    // -------------------------------
    // --- Resource file functions ---
    // -------------------------------
    bool                        resourceIsLocal     () const    { return resLocalE == m_eResourceType; }
    std::string                 urlResource         () const    { return m_sUrlResource;            }
    boost::filesystem::path     fileResource        () const    { return m_fileResource;            }
    std::string                 fileResourceStr     () const    { return m_fileResource.string();   }
    ResourceTypeE               resourceType        () const    { return m_eResourceType;           }
    ResourceFileTypeE           resourceFileType    () const    { return m_eResourceFileType;       }


    void        optionResourceAdd       ( const std::string& sResourcePath, const std::string& sScriptFilterFunction, bool bForceDownload  );
    void        setResourceFile         ( const std::string& sUrlOrFilePath );
    void        downloadRemoteResource  ( bool bForceDownload );
    void        openLocalFile           ();
    void        closeLocalFile          ();
    bool        eofLocalFile            () const;
    std::string readLineFromLocalFile   () const;

    // -------------------------------------
    // --- PUBLIC: Option data functions ---
    // -------------------------------------
    const OptionT*          getOptionData  ( boost::int64_t iOptionIndex ) const;
    const OptionT*          getOptionData  ()                              const;


protected:
    // --- PROTECTED: Typedefs ---
    typedef std::vector<OptionT>    OptionVecT;

    int         addOptionPosCounter     () const  { return m_iAddOptionPosCounter; }
    // --- PROTECTED: Data ---
    boost::int64_t  m_iCurrentOptionIndex;
    boost::int64_t  m_iEndOptionIndex;
    OptionVecT      m_options;

private:
    // --- PRIVATE: Typedefs ---
    typedef std::map<std::string,std::string>               StrStrMapT;
    typedef std::map<std::string, StrStrMapT >              AttributeMapT;
    typedef std::map<std::string, boost::int64_t >          OptionToIndexMapT;

    // --- PRIVATE: Abstract interface (do) functions ---
    virtual bool            do_needValidDomPosToExecute() const = 0;
    virtual void            do_currentOptionIndexSet( boost::int64_t iIndex ) ;
    virtual boost::int64_t	do_currentOptionIndexGet() const;
    virtual boost::int64_t  do_endOptionIndexGet    () const;
    virtual void            do_endOptionIndexSet    ( boost::int64_t iIndex );
    virtual boost::int64_t	do_lastOptionIndexGet   () const;

    virtual std::string     do_indexToOption        ( boost::int64_t iOptionIndex	)   const;
    virtual std::string     do_indexToSearchVal     ( boost::int64_t iOptionIndex	)   const;
    virtual int             do_indexToCount         ( boost::int64_t iOptionIndex	)   const;
    virtual void            do_nextOption			();
    virtual std::string     do_optionAdd            ( int iCount, const std::string& sValue, const std::string& sSearchFor );
    virtual void            do_start                ();
    virtual void            do_addResourceLine      ( const std::string& sLine );

	// --- PRIVATE: Helper functions ---
    virtual std::string     hlp_getCurrentOption        () const;
    virtual boost::int64_t  hlp_optionToIndex           ( const std::string& sOption	)	const;
    virtual void            hlp_insertInOptionToIndex	( boost::int64_t iOptionIndex, const std::string& sOption );
    virtual boost::int64_t  hlp_firstOptionIndex        () const { return FirstOptionIndexE; }
    virtual bool            hlp_atEndOption             () const;

    // --- PRIVATE: Resource functions ---
    void                        readResources       (const std::string& sScriptFilterFunction);


    // --- PRIVATE: Members ---

    mutable std::string			m_sCurrentOption;
    std::string                 m_sCurrentDomTextValue;
    std::string                 m_sCurrentDomValue;
    int                         m_iAddOptionPosCounter;
    std::string                 m_sCurrentOptionAdd;
    AttributeMapT               m_attributeMap;
    StrVecT                     m_attributeNames;
    OptionToIndexMapT           m_optionToIndexMap;
    std::string                 m_sEndOption;
    bool                        m_bAutoInputDoIncreaseLength;
    bool                        m_bAllMoreSignificantStatesAtEnd;

    // --- PRIVATE: Resource Members ---
    std::string                 m_sUrlResource;
    boost::filesystem::path     m_fileResource;
    ResourceTypeE               m_eResourceType;
    ResourceFileTypeE           m_eResourceFileType;
    FILE*                       m_resTxtFileHandle;
    gzFile                      m_resGzFileHandle;
    const ScriptMiner*          m_pScriptMiner;


};


} //END namespace crawl


#endif //_CRAWL_NAVIGATE_STATE_BASE_H_

