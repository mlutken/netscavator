#ifndef _CPAF_COMMAND_LINE_PARSER_H_
#define _CPAF_COMMAND_LINE_PARSER_H_

#include <string>
#include <map>
#include <loki/Singleton.h>

namespace crawl {

class CommandLineParser 
{
public:
	struct Cmd {
		enum EType { eNonExistingCmd, eEmptyCmd, eString, eDouble };
		EType			eType;
		std::string		sArg;
		std::string		sVal;
		double			fVal;	
		std::string		sDefaultVal;
		Cmd() : eType(eNonExistingCmd), sArg(""), sVal(""), fVal(0), sDefaultVal("") {}
	};

	CommandLineParser();
	~CommandLineParser();
	
	void			defaultValsSet	( const std::string sDefaults	 );
	
	bool			parse			( int argc, char** argv		);
	void			parseStart		();
	bool			parseArg		( const std::string sArgument	 );
	
	Cmd				valGet			( const std::string sArgName ) const ;	
	std::string		valStrGet		( const std::string sArgName ) const ;	
	double			valNumGet		( const std::string sArgName ) const ;	
	
    void            valStrForceSet	( const std::string sArgName, const std::string& sVal ) ;
    void			valNumForceSet	( const std::string sArgName, double fVal ) ;

private:
	typedef std::map< std::string, Cmd >	CommandsT;
	
	CommandsT		m_commands;
	CommandsT		m_commandsDefaults;
	
};

typedef Loki::SingletonHolder<CommandLineParser, Loki::CreateStatic>		G_CommandLineParser;

void						cmdDefaultValsSet	( const std::string sDefaults	);

void						cmdParseStart		();
bool						cmdParseArg			( const std::string sArgument	);
bool						cmdParse			( int argc, char** argv			);

CommandLineParser::Cmd		cmdValGet			( const std::string sArgName 	);	
std::string					cmdValStrGet		( const std::string sArgName 	);	
double						cmdValNumGet		( const std::string sArgName 	);	
void                        cmdValStrForceSet	( const std::string sArgName, const std::string& sVal );
void                        cmdValNumForceSet	( const std::string sArgName, double fVal );

} // END namespace crawl

#endif //_CPAF_COMMAND_LINE_PARSER_H_


