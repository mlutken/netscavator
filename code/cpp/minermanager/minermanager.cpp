
#include <iostream>
#include <stdio.h>

#include <boost/format.hpp>
#include <boost/thread/thread.hpp>

#include <cpaf_http_convenience.h>
#include <cpaf_session.h>

#include "_examples/command_lines.cpp"
#include "_examples/posix_communication.cpp"
#include "_examples/example_kill.cpp"

int main ( int argc, char* argv[] )
{

	kill_example();
//	download_url_wget( "http://www.doxys.dk/doxys_homepage/index.html", sStdOut );
//	cout<<sStdOut<<endl;

//	command_lines_example( argc, argv );
//	posix_communication_example( argc, argv );
	return 0;
}

