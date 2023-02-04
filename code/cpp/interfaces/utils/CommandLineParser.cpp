#include "CommandLineParser.h"

#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>

namespace crawl {

CommandLineParser::CommandLineParser()
{
}

CommandLineParser::~CommandLineParser()
{

}

void CommandLineParser::defaultValsSet	( const std::string sDefaults )
{
	using namespace cpaf;
	m_commandsDefaults.clear();
	StringVecT sv1;
	boost::split( sv1, sDefaults, boost::is_any_of(";") );
	StringVecT::iterator it1 = sv1.begin(); 
	
	for ( ; it1 != sv1.end(); ++it1 ){
		std::string sTrimmed = boost::trim_copy( *it1 );
		StringVecT sv2;
		boost::split( sv2, sTrimmed, boost::is_any_of("=") );
		if ( sv2.size() == 2 ){
			Cmd cmd;
			cmd.eType 				= Cmd::eString;
			cmd.fVal 				= 0;
			cmd.sArg 				= boost::trim_copy( sv2[0] );
			cmd.sVal 				= boost::trim_copy( sv2[1] );
			cmd.sDefaultVal 		= boost::trim_copy( sv2[1] );
			if ( cpaf::to_double ( cmd.sVal, cmd.fVal ) ) {
				cmd.eType = Cmd::eDouble;
			}	
			m_commandsDefaults[cmd.sArg] 	= cmd;		 	
		}
	}
}

void CommandLineParser::parseStart()
{
	m_commands = m_commandsDefaults;
}

bool CommandLineParser::parse( int argc, char** argv )
{
	parseStart();
	
	for ( int i = 1; i < argc; i++ ) {
		std::string sArgument(argv[i]);
		parseArg ( sArgument );
	}
	return true;
}



bool CommandLineParser::parseArg ( const std::string sArgument )
{
	using namespace std;
	using namespace boost;
	
	
	Cmd cmd;
	cmd.eType = Cmd::eString;
	cmd.fVal = 0;
	cmd.sArg = sArgument;
	cmd.sVal = "";
	
	cpaf::StringVecT sv;
	split( sv, sArgument, is_any_of("=") );
	if ( sv.size() == 2 ){
		cmd.sArg = boost::trim_copy( sv[0] );
		cmd.sVal = boost::trim_copy( sv[1] );
	}
	else {
		// --- See if there's a default value set ---
		Cmd cmdDefaultVal = valGet( cmd.sArg );
		if ( cmdDefaultVal.eType != Cmd::eNonExistingCmd ) {
			cmd.sVal = cmdDefaultVal.sDefaultVal;
		}
	}
	
	erase_all( cmd.sArg, "--"); 	
	if ( cpaf::to_double ( cmd.sVal, cmd.fVal ) ) {
		cmd.eType = Cmd::eDouble;
	}	
	m_commands[cmd.sArg] = cmd;		 
	return true;
}


CommandLineParser::Cmd CommandLineParser::valGet( const std::string sArgName ) const 
{
	Cmd cmd;
	CommandsT::const_iterator it = m_commands.find( sArgName );
	if ( it != m_commands.end() ) {
		cmd = it->second;
	}
	return cmd;
}

std::string CommandLineParser::valStrGet( const std::string sArgName ) const 
{
	Cmd cmd = valGet( sArgName );
	if ( cmd.eType == Cmd::eNonExistingCmd )	return "";
	return cmd.sVal;
}

double CommandLineParser::valNumGet( const std::string sArgName ) const 
{
	Cmd cmd = valGet( sArgName );
	if ( cmd.eType == Cmd::eNonExistingCmd )	return 0;
	return cmd.fVal;
}

void CommandLineParser::valStrForceSet	( const std::string sArgName, const std::string& sVal )
{
    CommandsT::iterator it = m_commands.find( sArgName );
    if ( it != m_commands.end() ) {
        it->second.sVal = sVal;
    }
}


void CommandLineParser::valNumForceSet	( const std::string sArgName, double fVal )
{
    CommandsT::iterator it = m_commands.find( sArgName );
    if ( it != m_commands.end() ) {
        it->second.fVal = fVal;
    }
}



void cmdDefaultValsSet	( const std::string sDefaults	)
{
	G_CommandLineParser::Instance().defaultValsSet( sDefaults );
}



void cmdParseStart	()
{
	G_CommandLineParser::Instance().parseStart();
}

bool cmdParseArg ( const std::string sArgument	)
{
	return G_CommandLineParser::Instance().parseArg( sArgument );
}


bool cmdParse ( int argc, char** argv )
{
	return G_CommandLineParser::Instance().parse( argc, argv );
}

CommandLineParser::Cmd cmdValGet( const std::string sArgName )
{
	return G_CommandLineParser::Instance().valGet( sArgName );
}

std::string cmdValStrGet ( const std::string sArgName )
{
	return G_CommandLineParser::Instance().valStrGet( sArgName );
}

double cmdValNumGet	( const std::string sArgName )
{
	return G_CommandLineParser::Instance().valNumGet( sArgName );
}


void cmdValStrForceSet	( const std::string sArgName, const std::string& sVal )
{
    G_CommandLineParser::Instance().valStrForceSet( sArgName, sVal );
}


void cmdValNumForceSet	( const std::string sArgName, double fVal )
{
    G_CommandLineParser::Instance().valNumForceSet( sArgName, fVal );
}


} // END namespace crawl

