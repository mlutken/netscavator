#pragma once
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>


namespace crawl {

    class DomNodeIF;
    class ScriptMinerIF;




    /// Small set of classes to handle different number of parameters to the dom actions in a uniform way
    /// using virtual functions. This class is the base class from which concrete implementations must derive.
    class DomActionAbstraction
    {
    public:
        DomActionAbstraction(){}
        virtual ~DomActionAbstraction(){}

        bool                    doActionBool	( 	boost::shared_ptr<ScriptMinerIF> pCrawler,
                                                    const std::string& sP1, const std::string& sP2 )
        {
            return doActionBool( pCrawler.get(), sP1, sP2 );
        }
        virtual bool			doActionBool	( 	ScriptMinerIF*,
                                                    const std::string&, const std::string& ) { return true; }
    };


    // -------------------------------------------------
    // --- DomActionAbstraction look up static class ---
    // -------------------------------------------------


    /**
Static class for looking up dom abstraction classes based on a string alias  
names and integer 'handles'. */
    struct G_DomActionAbstractionLookUp {

        typedef std::map< std::string, boost::shared_ptr<DomActionAbstraction> >	MapT;

        static const MapT		 									AliasMap;

        static boost::shared_ptr<DomActionAbstraction> 				fromAlias	( const std::string& sFunAlias );

    };

    // -------------------------
    // --- NodeClickLoadHref ---
    // -------------------------

    /// Do click on dom node
    class NodeClickLoadHref : public DomActionAbstraction
    {
    public:
        virtual bool			doActionBool	( 	ScriptMinerIF* pCrawler,
                                                    const std::string& sParam1, const std::string& sParam2 );
    };


    // -----------------
    // --- NodeClick ---
    // -----------------

    /// Do click on dom node
    class NodeClick : public DomActionAbstraction
    {
    public:
        virtual bool			doActionBool	( 	ScriptMinerIF* pCrawler,
                                                    const std::string& sParam1, const std::string& sParam2 );
    };

    /// Do click on dom node and wait for dom ready
    class NodeClickWait : public DomActionAbstraction
    {
    public:
        virtual bool			doActionBool	( 	ScriptMinerIF* pCrawler,
                                                    const std::string& sTimeoutInMs, const std::string& sParam2 );
    };

    // ------------------
    // --- MouseEvent ---
    // ------------------

    /// Send mouse event(s) to a dom node
    class MouseEvent : public DomActionAbstraction
    {
    public:
        virtual bool			doActionBool	( 	ScriptMinerIF* pCrawler,
                                                    const std::string& sParam1, const std::string& sParam2 );
    };

    // ------------------------------
    // --- NodeJavaScriptEvaluate ---
    // ------------------------------

    /// Send mouse event(s) to a dom node
    class NodeJavaScriptEvaluate : public DomActionAbstraction
    {
    public:
        virtual bool			doActionBool	( 	ScriptMinerIF* pCrawler,
                                                    const std::string& sParam1, const std::string& sParam2 );
    };

    // ---------------
    // --- LoadUrl ---
    // ---------------

    /// Load URL into browser
    class LoadUrl : public DomActionAbstraction
    {
    public:
        virtual bool			doActionBool	( 	ScriptMinerIF* pCrawler,
                                                    const std::string& sParam1, const std::string& sParam2 );
    };

    /// Load URL into browser and wait for dom ready
    class LoadUrlWait : public DomActionAbstraction
    {
    public:
        virtual bool			doActionBool	( 	ScriptMinerIF* pCrawler,
                                                    const std::string& sTimeoutInMs, const std::string& sParam2 );
    };

    // ------------------
    // --- InputValue ---
    // ------------------

    /// Input value to a (text) field in browser.
    class InputValue : public DomActionAbstraction
    {
    public:
        virtual bool			doActionBool	( 	ScriptMinerIF* pCrawler,
                                                    const std::string& sParam1, const std::string& sParam2 );
    };



    // ------------------
    // --- FormSubmit ---
    // ------------------

    /// Submit a form in the browser in browser.
    class FormSubmit : public DomActionAbstraction
    {
    public:
        virtual bool			doActionBool	( 	ScriptMinerIF* pCrawler,
                                                    const std::string& sParam1, const std::string& sParam2 );
    };


    // -----------------
    // --- FormReset ---
    // -----------------

    /// Submit a form in the browser in browser.
    class FormReset : public DomActionAbstraction
    {
    public:
        virtual bool			doActionBool	( 	ScriptMinerIF* pCrawler,
                                                    const std::string& sParam1, const std::string& sParam2 );
    };


    // -------------------
    // --- SelectIndex ---
    // -------------------

    /// Select specified index in SELECT specified by \a pNode .
    class SelectIndex : public DomActionAbstraction
    {
    public:
        virtual bool			doActionBool	( 	ScriptMinerIF* pCrawler,
                                                    const std::string& sParam1, const std::string& sParam2 );
    };

    /// Select specified index in SELECT specified by \a pNode .
    class SelectIndexWait : public DomActionAbstraction
    {
    public:
        virtual bool			doActionBool	(ScriptMinerIF* pCrawler,
                                                    const std::string& sParam1, const std::string& sTimeoutInMs );
    };

    // --------------------
    // --- SelectOption ---
    // --------------------

    /// Select OPTION element specified by \a pNode in it's owning SELECT.
    class SelectOption : public DomActionAbstraction
    {
    public:
        virtual bool			doActionBool	( 	ScriptMinerIF* pCrawler,
                                                    const std::string& sParam1, const std::string& sParam2 );
    };


} //namespace crawl
