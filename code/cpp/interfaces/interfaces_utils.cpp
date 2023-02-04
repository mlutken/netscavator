#include "interfaces_utils.h"

#include <boost/algorithm/string.hpp>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>
#include <DomNodeIF.h>

namespace crawl {

    /** Convert a DomNodeIF node type to a string representation.
    \todo Implement nodeTypeToString */
    std::string
            nodeTypeToString ( boost::shared_ptr<DomNodeIF> const& pNode )
    {
        switch ( pNode->nodeType() )
        {
            case DomNodeTypes::ELEMENT                  : return "ELEMENT"					;
            case DomNodeTypes::ATTRIBUTE 				: return "ATTRIBUTE"				;
            case DomNodeTypes::TEXT 					: return "TEXT"						;
            case DomNodeTypes::CDATA_SECTION 			: return "CDATA_SECTION"			;
            case DomNodeTypes::ENTITY_REFERENCE 		: return "ENTITY_REFERENCE"			;
            case DomNodeTypes::ENTITY		 			: return "ENTITY"					;
            case DomNodeTypes::PROCESSING_INSTRUCTION 	: return "PROCESSING_INSTRUCTION"	;
            case DomNodeTypes::COMMENT                  : return "COMMENT"					;
            case DomNodeTypes::DOCUMENT 				: return "DOCUMENT"					;
            case DomNodeTypes::DOCUMENT_TYPE 			: return "DOCUMENT_TYPE"			;
            case DomNodeTypes::DOCUMENT_FRAGMENT 		: return "DOCUMENT_FRAGMENT"		;
            case DomNodeTypes::NOTATION 				: return "NOTATION"					;
            case DomNodeTypes::ATTRIBUTE_VALUE          : return "ATTRIBUTE_VALUE"			;
            case DomNodeTypes::ELEMENT_END_TAG          : return "ELEMENT_END_TAG"			;
            default                                     : return "UNKNOWN_TYPE"				;
        }
    }


    std::string trimBlanksCopy	( const std::string& sInput )
    {
        std::string sRet = boost::algorithm::trim_copy( sInput );
        return sRet;
    }

    std::string toString ( RunModeE eRunMode )
    {
        switch (eRunMode ) {
        case rmCrawlerE : return "crawler";
        case rmDesignE  : return "design";
        case rmDebugE   : return "debug";
        default         : return "normal";
        }
    }

    RunModeE toRunMode ( const std::string& sRunMode )
    {
        if      ( sRunMode == "crawler" ) return rmCrawlerE;
        else if ( sRunMode == "design"  ) return rmDesignE;
        else if ( sRunMode == "debug"   ) return rmDebugE;
        else                              return rmNormalE;
    }

    bool stringToBool ( const std::string& sValue )
    {
        std::string sVal = boost::algorithm::to_lower_copy( sValue );
//        if ( sVal == "yes" || sVal == "true" )  return true;
        if ( sVal == "" || sVal == "no" || sVal == "false" || sVal == "0" )  return false;
        return true;
    }


    void createScriptParams  (
            const std::string& sScriptPath
            , const StrVecT& params
            , int& argcOut
            , char* argvOut[] )
    {
        if ( sScriptPath != "" ) {
            strcpy( argvOut[0], sScriptPath.c_str() );
        }
        else strcpy( argvOut[0], "DEFAULT_SCRIPT.php");

        for ( size_t i = 0; i < params.size(); ++i ){
            strcpy(argvOut[i+1], params[i].c_str() );
        }
        argcOut = static_cast<int32_t>(params.size()) + 1;
    }

    void createScriptParams  (
            const std::string& sScriptPath
            , const std::string& params
            , int& argcOut
            , char* argvOut[] )
    {
        StrVecT vecParams = cpaf::splitv_trim( params, " ");
        createScriptParams( sScriptPath, vecParams, argcOut, argvOut );
    }


} // END namespace crawl

