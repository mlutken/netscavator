
#include <cstdlib>
#include <iostream>

#include <boost/process.hpp>

namespace bp = ::boost::process;


static int
kill_example ( )
{
	using namespace std;
	using boost::format;
	using boost::io::group;
	namespace pt = ::boost::posix_time;
	namespace cn = ::cpaf::net;



	std::string sStdOut;
//	bp::command_line 		cl1 ( "/usr/bin/xclock" );
	bp::command_line cl1 = bp::command_line::shell( "/usr/bin/xclock" );
	
	bp::child cp = start_it ( cl1 );
//	cp.wait();
//	cout << "Running: " << cp.running() << endl;
	cout << "Sleep a litte" << endl;
	boost::this_thread::sleep ( pt::time_duration ( 0,0,6,0 ) );
	cout << "Kill" << endl;
	cp.kill ( false );
	cout << "Sleep a litte again" << endl;
	boost::this_thread::sleep ( pt::time_duration ( 0,0,3,0 ) );

	return EXIT_SUCCESS;
}


// quickbook:end(code)
