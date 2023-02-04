//#include <MozBrowserWx.h>

#include <stdio.h>
#include <iostream>

#include <utils/CommandLineParser.h>
  
void test_CommandLineParser(int argc, char** argv)
{
	using namespace std;
	using namespace crawl;
	
	printf("CommandLineParser test\n");
// 	CommandLineParser cmd;
// 	bool bRes = cmd.parse( argc, argv );
// 	cout << "MyCmd: '" << cmd.valStrGet("MyCmd") << "'" << endl;
	cmdDefaultValsSet("MyCmd=123;Run=true");
	bool bRes = cmdParse( argc, argv );
	cout << "MyCmd: '" << cmdValStrGet("MyCmd") << "'" << endl;
	cout << "Run: '" << cmdValStrGet("Run") << "'" << endl;
}
