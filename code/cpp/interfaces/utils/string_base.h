#ifndef CRAWL_STRING_BASE_H
#define CRAWL_STRING_BASE_H

#include <string>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <Configuration.h>
//#include <boost/any.hpp>
//#include <utils/string_algorithms.h>




namespace crawl {
    // Prototypes for string manipulation functions
    typedef boost::function< std::string ( const boost::shared_ptr<Configuration> pConfig, std::string const& ) >																StringManipStrT;
    typedef boost::function< std::string ( const boost::shared_ptr<Configuration> pConfig, std::string const&, std::string const& ) >											StringManipStrStrT;
    typedef boost::function< std::string ( const boost::shared_ptr<Configuration> pConfig, std::string const&, std::string const&, std::string const& ) >						StringManipStrStrStrT;
    typedef boost::function< std::string ( const boost::shared_ptr<Configuration> pConfig, std::string const&, std::string const&, std::string const&, std::string const& ) >	StringManipStrStrStrStrT;
    typedef boost::function< std::string ( const boost::shared_ptr<Configuration> pConfig, std::string const&, std::string const&, int ) >										StringManipStrStrIntT;
    typedef boost::function< std::string ( const boost::shared_ptr<Configuration> pConfig, std::string const&, std::string const&, std::string const&, int ) >					StringManipStrStrStrIntT;


    /// Small set of classes to handle different number of parameters to the functions in a uniform
    /// using virtual functions. This class is the base class from which concrete implementations must derive.
    class StrModifierAbstraction
    {
    public:
        typedef	boost::shared_ptr<StrModifierAbstraction>	PtrT;

        virtual ~StrModifierAbstraction(){}
        virtual std::string		callMeStr	( const boost::shared_ptr<Configuration> /*pConfig*/, const std::string& /*sParam1*/, const std::string& /*sParam2*/, const std::string& /*sParam3*/, const std::string& /*sParam4*/ )
        {	return ""; }
    };

    /// Call functions with 1 string parameter
    class StringManipStr_Str : public StrModifierAbstraction
    {
    public:
        explicit StringManipStr_Str( const StringManipStrT& fn ) : m_fn(fn) {}
        virtual std::string		callMeStr	( const boost::shared_ptr<Configuration> pConfig, const std::string& sParam1, const std::string& /*sParam2*/, const std::string& /*sParam3*/, const std::string& /*sParam4*/ )
        {	return m_fn(pConfig, sParam1); }
        StringManipStrT				m_fn;
    };

    /// Call functions with 2 string parameters
    class StringManipStr_StrStr : public StrModifierAbstraction
    {
    public:
        explicit StringManipStr_StrStr( const StringManipStrStrT& fn ) : m_fn(fn) {}

        virtual std::string		callMeStr	( const boost::shared_ptr<Configuration> pConfig, const std::string& sParam1, const std::string& sParam2, const std::string& /*sParam3*/, const std::string& /*sParam4*/ )
        {	return m_fn(pConfig, sParam1, sParam2); }
        StringManipStrStrT			m_fn;
    };

    /// Call functions with 3 string parameters
    class StringManipStr_StrStrStr : public StrModifierAbstraction
    {
    public:
        explicit StringManipStr_StrStrStr( const StringManipStrStrStrT& fn ) : m_fn(fn) {}

        virtual std::string		callMeStr	( const boost::shared_ptr<Configuration> pConfig, const std::string& sParam1, const std::string& sParam2, const std::string& sParam3, const std::string& /*sParam4*/ )
        {	return m_fn(pConfig, sParam1, sParam2, sParam3); }
        StringManipStrStrStrT		m_fn;
    };

    /// Call functions with 4 string parameters
    class StringManipStr_StrStrStrStr : public StrModifierAbstraction
    {
    public:
        explicit StringManipStr_StrStrStrStr( const StringManipStrStrStrStrT& fn ) : m_fn(fn) {}

        virtual std::string		callMeStr	( const boost::shared_ptr<Configuration> pConfig, const std::string& sParam1, const std::string& sParam2, const std::string& sParam3, const std::string& sParam4  )
        {	return m_fn(pConfig, sParam1, sParam2, sParam3, sParam4); }
        StringManipStrStrStrStrT	m_fn;
    };

} //namespace crawl


#endif //CRAWL_STRING_BASE_H

