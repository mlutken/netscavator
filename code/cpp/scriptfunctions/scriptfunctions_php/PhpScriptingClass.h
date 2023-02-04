#ifndef _SCRIPTCRAWL_PHP_SCRIPTING_CLASS_H_
#define _SCRIPTCRAWL_PHP_SCRIPTING_CLASS_H_

#include <boost/shared_ptr.hpp>
#include <ScriptingClassIF.h>



class PhpScriptingClass : public crawl::ScriptingClassIF
{
public:
	// ----------------
	// --- Typedefs ---
	// ----------------

    // --------------------------------
    // --- Constructors/destructors ---
    // ---------------------------------
                 PhpScriptingClass();
    virtual     ~PhpScriptingClass();
    virtual void     readScriptFunctions () override;

    // --------------------------------------
    // --- Call script function functions ---
    // --------------------------------------
    virtual bool						scriptFunctionExists        ( const std::string& sFunName 	) const override;

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

private:


};


#endif // _SCRIPTCRAWL_PHP_SCRIPTING_CLASS_H_



