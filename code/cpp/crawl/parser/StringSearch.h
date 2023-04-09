#ifndef _CRAWL_STRING_SEARCH_H_
#define _CRAWL_STRING_SEARCH_H_

#include <fstream>
#include <stack>
#include <map>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/function.hpp>

#include <url/Url.h>

namespace crawl { 

class Configuration;
class StrModifierAbstraction;
class DataWriterIF;

/** 
XXX Detailed description here ... XXX
\author Martin Lütken */
class StringSearch 
{
public:
	
	enum 	EMatchPos { MATCH_FIRST = 0, MATCH_LAST = 1	};

    // ----------------
    // --- Typedefs ---
    // ----------------
    typedef std::vector< boost::shared_ptr<DataWriterIF> >  DataWriterVecT;

    typedef boost::function< bool (const std::string&, const std::string&  ) >									StringCompareFunT;		///< Prototype string compare function
    typedef boost::function< std::string (const boost::shared_ptr<Configuration>, const std::string& ) >		StringCopyManipFun1T;	///< Prototype string maipulation function
    typedef boost::function< std::string (const boost::shared_ptr<Configuration> pConfig, const std::string&, const std::string& ) >							StringCopyManipFun2T;	///< Prototype string maipulation function
    typedef boost::function< std::string (const boost::shared_ptr<Configuration> pConfig, const std::string&, const std::string&, const std::string&  ) >		StringCopyManipFun3T;	///< Prototype string maipulation function
    typedef boost::function< std::string (const boost::shared_ptr<Configuration> pConfig, const std::string&, const std::string&, const std::string&, int  ) >	StringCopyManipFun4T;	///< Prototype string maipulation function
	
	typedef boost::iterator_range<std::string::iterator>		StringRangeT;
	typedef boost::find_iterator<std::string::iterator> 		StringFindIteratorT;
	
	typedef boost::iterator_range<std::string::const_iterator>	StringRangeConstT;
	typedef boost::find_iterator<std::string::const_iterator> 	StringFindConstIteratorT;
    // ------------------------------------
    // --- Constructor / Init Functions ---
    // ------------------------------------
 ////   StringSearch( boost::shared_ptr<std::ostream> pDataBaseStreamOut, boost::shared_ptr<Configuration> pConfig );
 ////   StringSearch( boost::shared_ptr<std::ostream> pDataBaseStreamOut, boost::shared_ptr<DataWriterIF> pDataWriter, boost::shared_ptr<Configuration> pConfig );
    StringSearch( boost::shared_ptr<DataWriterIF> pDataWriter, boost::shared_ptr<Configuration> pConfig );
    StringSearch( boost::shared_ptr<DataWriterIF> pDataWriter1, boost::shared_ptr<DataWriterIF> pDataWriter2, boost::shared_ptr<Configuration> pConfig );
    StringSearch( const DataWriterVecT& dataWriters, boost::shared_ptr<Configuration> pConfig );


    void        assignDataWriters       ( const DataWriterVecT dataWriters  );
    void        restart                 ( const std::string sBaseOutputName );
    void        outputNameSet           ( const std::string sBaseOutputName );
    void        doContinueModeSet       ( bool bDoContinue, int iContinueCounter );

    void        reset                   ();
    void        dataWriterOutputClose   ();

    void 		debugOutput             ( bool bDebugOutput ) {	m_bDebugOutput = bDebugOutput;	}

	// ------------------------
	// --- Parser Functions ---
	// ------------------------
    void		newSearchString			( std::string const& sSearchIn, std::string const& sFieldName );
    void		newSearch				( std::string const& sFieldName );
    bool 		canFindRegex			( std::string const& sRegex ) 					const;
    void		beginNewValue			( std::string const& sFieldName );

	// ------------------------
	// --- Parse Functions ---
	// ------------------------
    bool		parseRegex				( int iCount, const std::string& sRegex, 		EMatchPos postMarkerPos, bool bIgnoreCase, bool bParseTo	)	;
    bool		parseToString			( int iCount, const std::string& sSubstring, 	EMatchPos postMarkerPos, bool bIgnoreCase					)	;
    bool		parseToEnd				()																												;

	// ------------------------
	// --- Marker Functions ---
	// ------------------------
    void 		resetMarkersBeginEnd	() 																			;
    bool		findBeginNext			( int iCount, const std::string& sPattern, 	EMatchPos setBeginToPos		)	;
    bool		findEndNext				( int iCount, const std::string& sPattern, 	EMatchPos setEndToPos		)	;
    bool		ifindBeginNext			( int iCount, const std::string& sPattern, 	EMatchPos setBeginToPos		)	;
    bool		ifindEndNext			( int iCount, const std::string& sPattern, 	EMatchPos setEndToPos		)	;
    bool		findRegexBeginNext		( int iCount, const std::string& sRegex, 	EMatchPos setBeginToPos		)	;
    bool		findRegexEndNext		( int iCount, const std::string& sRegex, 	EMatchPos setEndToPos		)	;
	
    void 		resetMarkersToPageTop	()												const 	;
    void 		resetMarkersToPageBottom()												const 	;
    void 		setEndToPageBottom		()												const 	;
	// --- Marker Move Functions ---
    bool		moveBegin				( int iNumChars )										;
    bool		moveEnd					( int iNumChars )								 		;

	// ------------------------------------------------------------------
	// --- Assign to current value string (m_sCurrentValue) Functions ---
	// ------------------------------------------------------------------
	std::string 			setValueBeginEndRegex	( std::string const& sRegex )	;
	void		 			setValueBeginEnd		()								;
	std::string 			setValueRegex			( std::string const& sRegex )	;
	std::string const& 		getValue				() const						;
	void					setValue				( std::string const& sValue )	;
    void                    valueWasSetExplicitlyClear();
	void					setValueToPageUrl		()								;
	void					setValueToSiteUrl		()								;
	std::string 			getParseMatch			( int iMatchNumber ) const		;
	std::string 			getParseRest			( ) const						;
	int 					getParseMatchCount		( )	const						;
	
	
	
	// --------------------------------------
	// --- Modify Current Value Functions ---
	// --------------------------------------
	
	void					modifyValue				( boost::shared_ptr<StrModifierAbstraction> pManip, 
													  const std::string& sParam1, const std::string& sParam2, 
                                                      const std::string& sParam3, const std::string& sParam4 );
	void					modifyValue				( const StringCopyManipFun1T& fnManip )													; 
	void					modifyValue				( const StringCopyManipFun2T& fnManip, 
													  const std::string& sManipParam )														; 
	void					modifyValue				( const StringCopyManipFun3T& fnManip, 
													  const std::string& sManipParam1, const std::string& sManipParam2 )					; 
	void					modifyValue				( const StringCopyManipFun4T& fnManip, 
													  const std::string& sManipParam1, const std::string& sManipParam2,int iIntParam )		; 
	
	// ------------------------
	// --- Output Functions ---
	// ------------------------
    void					beginMining				(const std::string& outputName)															;
	void					endMining				( )																						;
    void					pushContext				(const std::string& sContext, bool bDoPushWritersContext )	;
    void					popContext				()																						;
    void					outputValueDirectUnit	(const std::string& sFieldName, const std::string& sValue)	;
	
	/// This function is only intended for scriptcrawl modifyValue functions, since if we use a StringSearch member
	/// for this we would also need here to know the lookup map where the manipulation functions are stored 
    /// in order for us to be able to prefer a user defined function over the built-ins. Since this
	/// map (as well as the functionality to call PHP functions) is in scriptcrawl project , which depends on 
    /// this one, it seems better for now not to rip everthing apart or
	/// introducing cyclic dependencies :~(
	/// \note This function is is }not} equivalent to setValue()
    void					currentValueSetDirect	( const std::string& sNewCurrentVal );
	const std::string&		currentValue			() const 								{	return m_sCurrentValue;				}
	
    // ----------------------
    // --- Misc Functions ---
    // ----------------------
    void 					configOutputEncloseCDATA( bool bDoEncloseInCDATA );
    void                    configOutputWriteToFile ( bool bDoWriteOutputToFile );

    std::string				outputValueGet( const std::string& sFieldName, const std::string sContextName );


    void                    contextOutputSaveAs         ( const std::string& sContextName );
    void                    contextFallbackOutputLoad   ( const std::string& sContextName );
    void                    contextFallbackOutputClear  ();
    std::string             contextFallbackValueGet     ( const std::string& sFieldName ) const;
    void                    contextFallbackValueSet     ( const std::string& sFieldName, const std::string& sValue ) ;

    bool                    contextFallbackValueExists  ( const std::string& sFieldName ) const;
    void                    contextFallbackValueDelete  ( const std::string& sFieldName );
    bool                    contextSavedOutputExists    ( const std::string& sContextName ) const;

    void                    contextSavedOutputDelete    ( const std::string& sContextName );
//    void                    outputStream                ( boost::shared_ptr<std::ostream> pDataBaseStreamOut )  { m_pDataBaseStreamOut = pDataBaseStreamOut; }

//    boost::shared_ptr<std::ostream>
//                            outputStream                () const                                                { return m_pDataBaseStreamOut; }

    bool                    fieldIsList             ( const std::string& fieldName) const;

    // -----------------------
    // --- Debug Functions ---
    // -----------------------


protected:

private:
    size_t  valuesCount() const;
    void    incValuesCount();
    size_t  contextCount() const;
    void    incContextCount();
    size_t  indentLevel() const;

    typedef std::vector<std::string>                StringVecT;
    typedef std::map<std::string, std::string>      StrStrMapT;
    typedef std::map<std::string, StringVecT>       OutputListsT;

    struct Context {
        explicit Context (const std::string& context) : m_context(context) {}
        std::string     m_context = "";
        size_t          m_valuesCount = 0;  // Values written in current context
        size_t          m_contextCount = 0; // Contexts written in current (parent) context
        //OutputListsT    m_outputValues; // TODO: use this as output values instead
    };

    typedef std::stack<Context>                     ContextStackT;
    typedef boost::shared_ptr<StrStrMapT>           StrStrMapPtrT;
    typedef std::map<std::string, StrStrMapPtrT>    ContextOutputValsT;

	// -------------------------
	// --- Private Functions ---
	// -------------------------
    void                    dwBeginMining           ( const std::string outputName );
    void                    dwOutputNameSet         ( const std::string outputName );
    void                    dwDoContinueModeSet     ( bool bDoContinue, int iContinueCounter );
    void                    dwRestart               (const std::string outputName );
    void                    dwConfigOutputEncloseCDATA( bool bDoEncloseInCDATA );
    void					dwEndMining				();
    void					dwPushContext			(const std::string& sContext, const std::string& prevContext, size_t ctxCount);
    void					dwPopContext			(const std::string& sContext, size_t parentContextCount );
    void					dwOutputValueDirect     ( const std::string& sFieldName, const std::string& sValue );

	// -------------------
	// --- Member Data ---
	// -------------------
    boost::shared_ptr<Configuration>        m_pConfig;
	std::string 							m_sSearchIn;
	std::string 							m_sCurrentValue;		///< Current active parsing value. Assigned using getValXXX functions
    boost::shared_ptr<std::ostream>         m_pDataBaseStreamOut;
	mutable std::string::const_iterator		m_itSubStrBegin;
	mutable std::string::const_iterator		m_itSubStrEnd;
	std::string 							m_sCurrentFieldName;
	std::string								m_sINSERT_INTO;
	std::string								m_sVALUES;
	bool									m_bDebugOutput;
    ContextStackT							m_ContextStack;
    boost::match_results<std::string::const_iterator> 	m_parseMatchResults;
	std::string 							m_sParseIn;
	std::string								m_sParseRest;
	bool									m_bDoEncloseInCDATA;
    bool                                    m_bDoWriteOutputToFile;
    StrStrMapPtrT                           m_pCurContextVals;          ///< output values currently being written to output
    StrStrMapT                              m_curContextFallbackVals;   ///< Current loaded context values for use in 'automatic' output from outputValueFindXX functions
    ContextOutputValsT						m_contextOutputVals;        ///< Cache from where the script can get the values of earlier 'outputted' values by name.
    DataWriterVecT                          m_dataWriters;
    bool                                    m_bDoContinueMode;  // True if continue scanning has been requested from the command line (-c). Only used in crawler, never in creator
    std::string                             m_autoListSuffix = "_list";
    OutputListsT                            m_outputLists;  // For each output field name that is a list we keep a vector of the elements, which is written to output when we pop the current context.
    bool                                    m_valueWasSetExplicitlyFromScript = false;
};

// -------------------------------
// --- Inline member functions ---
// -------------------------------

/** Assign to current value string the string between the begin and end markers. */
inline void StringSearch::setValueBeginEnd()
{
	m_sCurrentValue.assign(m_itSubStrBegin, m_itSubStrEnd);
}

/** Get current value string the string between the begin and end markers. */
inline std::string const& 
StringSearch::getValue() const
{
	return m_sCurrentValue;
}

// ----------------------
// --- Free Functions ---
// ----------------------

} // END namespace crawl


#endif //_CRAWL_STRING_SEARCH_H_


