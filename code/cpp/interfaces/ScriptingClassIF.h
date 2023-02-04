#ifndef _CRAWL_SCRIPTING_CLASS_IF_H_
#define _CRAWL_SCRIPTING_CLASS_IF_H_


#include <string>
#include <set>
#include <vector>
#include <boost/any.hpp>

namespace crawl {


class ScriptingClassIF
{
public:
	// ----------------
	// --- Typedefs ---
	// ----------------
    typedef 	std::vector<std::string>	FunctionsVecT;
    typedef 	std::set<std::string>		FunctionsSetT;

    // --------------------------------
    // --- Constructors/destructors ---
    // ---------------------------------
                 ScriptingClassIF();
    virtual     ~ScriptingClassIF();
    virtual void     readScriptFunctions ();

    // ----------------------
    // --- Info functions ---
    // ----------------------

    const FunctionsVecT&                allFunctionsVec() const { return m_allFunctionsVec;   }
    const FunctionsSetT&                allFunctionsSet() const { return m_allFunctionsSet;   }

    // --------------------------------------
    // --- Call script function functions ---
    // --------------------------------------
    virtual bool						scriptFunctionExists        ( const std::string& sFunName 	) const;

    virtual void						callScriptFunction_Void 	( const std::string& sFunName 	) const;
    virtual void						callScriptFunction_Void     ( const std::string& sFunName, const std::string& sParam ) const;

    virtual long						callScriptFunction_Long		( const std::string& sFunName 	) const;

    virtual double						callScriptFunction_Double	( const std::string& sFunName 	) const;
    virtual double						callScriptFunction_Double	( const std::string& sFunName, const std::string& sParam  	) const;
    virtual double						callScriptFunction_Double	( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2  	) const;

    virtual bool						callScriptFunction_Bool 	( const std::string& sFunName 	) const;
    virtual bool						callScriptFunction_Bool		( const std::string& sFunName, const std::string& sParam 	) const;
    virtual bool						callScriptFunction_Bool		( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2  	) const;
    virtual bool						callScriptFunction_Bool		( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2, const std::string& sParam3 ) const;
    virtual bool						callScriptFunction_Bool		( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2, const std::string& sParam3, const std::string& sParam4 ) const;


    virtual std::string					callScriptFunction_String 	( const std::string& sFunName 	) const;
    virtual std::string					callScriptFunction_String	( const std::string& sFunName, const std::string& sParam 	) const;
    virtual std::string					callScriptFunction_String	( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2  	) const;
    virtual std::string					callScriptFunction_String	( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2, const std::string& sParam3 ) const;
    virtual std::string					callScriptFunction_String	( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2, const std::string& sParam3, const std::string& sParam4 ) const;

    virtual boost::any					callScriptFunction_Any      ( const std::string& sFunName 	) const;

    // -----------------------------------
    // --- Set/get variables functions ---
    // -----------------------------------
    virtual void						varSet        ( const std::string& sName, const std::string& sValue	) const;
    virtual std::string					varGet_String ( const std::string& sName ) const;

protected:
    void                clearFunctions  () { m_allFunctionsVec.clear(); m_allFunctionsSet.clear();	}
    void                addFunction     ( std::string const& sFunctionName );
    FunctionsVecT		m_allFunctionsVec;
    FunctionsSetT		m_allFunctionsSet;


private:
		

};


} // END namespace crawl

#endif // _CRAWL_SCRIPTING_CLASS_IF_H_



