#ifndef _URL_H_
#define _URL_H_

#include <vector>
#include <boost/filesystem/path.hpp>

#include "url_string_functions.h"

namespace crawl { 

/** 
XXX Brief description XXX.
XXX Detailed description here ... XXX
\author Veriquin */
class Url
{
public:

    // ----------------
    // --- Typedefs ---
    // ----------------
	

    // ------------------------------------
    // --- Constructor / Init Functions ---
    // ------------------------------------
    Url				() : m_bUseParsed(true) {}
	Url				( const std::string& sUrl );
    Url				( const std::string& sUrl, bool bAssumeRelativeLink );
    Url             ( const Url& url );

    // ----------------------------
    // --- Inline Get Functions ---
    // ----------------------------
	
	/// Get protocol
	std::string				protocol()	const	{ return m_sProtocol;	}

//    /// Get path
//	boost::filesystem::path	path()		const	{ return m_Path;		}
    /// Get subdir
    boost::filesystem::path	subdirPath()const	{ return m_subDir;              }
    std::string             subdir()    const	{ return m_subDir.string();		}

	/// Get domain parts vector
    string_vec_t&			domainVec()         { return m_Domain;		}
    const string_vec_t&		domainVec()const	{ return m_Domain;		}
    std::string             domain()    const;

    const std::string&		leaf() const 		{ return m_sLeaf;		}

//	/// Get parameters
//	parameter_vec_t&		parameters() 		{ return m_Parameters;	}
//	const parameter_vec_t&	parameters() const 	{ return m_Parameters;	}
//	const std::string&		hash() const 		{ return m_sHash;		}

	/// Is this URL representing something that is/can-besaved-to a file? As opposed to a directory. 
	bool					isFile()	 const	{ return m_bIsFile; 	}

    // ----------------------------
    // --- Inline Set Functions ---
    // ----------------------------
	
//	/// Set path part of Url.
//	void					path		( const boost::filesystem::path& path )		///< [in] Path to assign.
//		{ m_Path = path; }
    /// Set subdir part of Url.
    void					subdirSet		( const std::string& subdir             );
    void					subdirSet		( const boost::filesystem::path& subdir );

    /// Set file/url property.
    void					isFileSet		( bool bIsFile )						///< [in] Set to true if this URL represents a file. Set to true if it's a directory.
		{ m_bIsFile = bIsFile; 	}

    /// Set force use parsed property.
    void					useParsedSet	( bool bUseParsed )						///< [in] Set to false to disable using the parsed version and instead using the raw url string.
        { m_bUseParsed = bUseParsed; 	}

    // ---------------------
    // --- Set Functions ---
    // ---------------------

    void					protocolAutoSet	();
    void					protocolSet     ( const std::string& sProtocol		);
    void					domainSet       ( const std::string& sSite			);
    void					domainSet       ( const string_vec_t& site			)
		{ m_Domain = site; }
//	void					parameters	( const std::string& sParameters	);

    // ---------------------
    // --- Get Functions ---
    // ---------------------
	/// Get URL as string. 
    std::string				string()                    const;
    std::string				rawString()                 const { return m_sRawUrl;	}
    std::string				rawStringWithProtocol()     const;
    std::string				parsedString()              const;
    std::string				protocolCompose()           const;
    std::string				domainCompose()             const;
    std::string				subdirCompose()             const;
    std::string				leafCompose()               const;
    std::string				topDomain()                 const;
    std::string				secondLevelDomain()         const;
    std::string				subDomains()                const;
    std::string 			siteDomain()                const;


    // ----------------------------------
    // --- Convenience Info Functions ---
    // ----------------------------------
    bool					hasProtocol()				const	{ return !protocol().empty(); 				}
    bool					hasSubdir()                 const	{ return !subdir().empty();                 }
//	bool					has_path()					const	{ return !path().empty(); 					}
    bool					hasDomain()					const	{ return !domainVec().empty(); 			}
    bool					hasLeaf()                   const	{ return !leaf().empty(); 			}
//	bool					has_parameters()			const	{ return !parameters().empty(); 			}
//	bool					has_hash()					const	{ return !hash().empty(); 					}
    bool					hasTopDomain()				const	{ return !topDomain().empty();				}
    bool					hasSecondLevelDomain()		const	{ return !secondLevelDomain().empty();	}
    bool					hasSubDomains()				const	{ return !subDomains().empty();			}
    bool					isJavaScript()				const;
    bool					isJavaScriptFunctionCall()  const;
    bool					isSectionLink()				const;
    bool					isLocalSectionLink()		const;
    bool					isMailAddress()				const;
    bool					empty()						const	{ return !(hasProtocol() || hasSubdir() || hasDomain() || hasLeaf()); }


    // ----------------------
    // --- Misc Functions ---
    // ----------------------
    Url&					operator=           ( const Url& url );
    Url&                    makeDefaultProtocol	();
    Url&                    makeLinkComplete    ( const Url& owningPageUrl );
    Url                     linkComplete        ( const Url& owningPageUrl ) const;

    // ----------------------
    // --- Friend Functions ---
    // ----------------------
	friend bool				operator==	(const Url& lhs, const Url& rhs);

protected:

private:
    // -------------------------
    // --- Private Functions ---
    // -------------------------

    void	assign	( const std::string& sUrl, bool bAssumeRelativeLink );

    // -------------------
    // --- Member Data ---
    // -------------------
	std::string				m_sRawUrl;	// Raw URL as string 
	std::string				m_sProtocol;
    string_vec_t			m_Domain;
    boost::filesystem::path	m_subDir;
    std::string				m_sLeaf;

//    boost::filesystem::path	m_Path;
//    parameter_vec_t			m_Parameters;
//	std::string				m_sHash;
	bool					m_bIsFile;			///< True if this URL represents a file, as opposed to
    bool					m_bUseParsed;	///< True if this URL represents a file, as opposed to
};



// ----------------------------
// --- Convenience Typedefs ---
// ----------------------------

typedef std::vector<Url>	UrlVecT;

// ----------------------
// --- Free Functions ---
// ----------------------

Url         linkComplete  ( const Url& owningPageUrl, const std::string& link );
std::string linkComplete  ( const std::string& owningPageUrl, const std::string& link );
std::string ensureProtocol( const std::string& url );

/// Not equal comparison. \return True if URLs are not eaqual.
inline bool				operator!=	(const Url& lhs, const Url& rhs)
	{ return !(lhs==rhs);}


std::ostream&	operator <<( std::ostream& os, const Url& Url );


//void copy_if ( ) 


} // END namespace crawl

#endif

