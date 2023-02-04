#include <iostream>
#include <boost/assign/list_of.hpp> 
#include <boost/format.hpp>
#include <boost/filesystem/convenience.hpp>
#include <cpaf_special_dirs.h>


#include "../Url.h"

using namespace crawl;	// Using clauses like this is ok in test files, else better to put in function perhaps
using namespace std;
using boost::format;

typedef std::vector<std::string> StringVecT;

#if 1
static const StringVecT				TestUrls = boost::assign::list_of 
("http://www.tv2.dk/nyheder/index.html")
("https://www.tv2.dk")
("www.tv2.dk")
("https://tv2.dk/nyheder/index.html?login=ml&password=mypasswd")
("http://www.bbc.co.uk/")
("/nyheder/index.html?login=ml&password=mypasswd")
("../nyheder/index.html?login=ml&password=mypasswd")
("./nyheder/index.html?login=ml&password=mypasswd")
("https://www.tv2.dk/nyheder//index.html")
("https://www.tv2.dk/nyheder/index.html?login=ml")
("https://www.tv2.dk/nyheder/index.html?login=ml&password=mypasswd")
("https://www.tv2.dk/nyheder/?login=ml&password=mypasswd")
("https://www.tv2.dk/?login=ml&password=mypasswd")
("https://www.tv2.dk/nyheder?login=ml&password=mypasswd")
("http://www.tv2.dk?login=ml&password=mypasswd")
("http://www.tv2.dk#?login=ml&password=mypasswd")
("http://www.tv2.dk#login=ml&password=mypasswd")
("http://www.tv2.dk/hest/ged?login=ml&password=mypasswd")
("http://localhost/test.html?login=ml&password=mypasswd#hash_string_here")
("www.tv2.dk/ged.html#hash")
("http://www.nyheder.tv2.dk")
("http://www.nyheder.tv2.dk/")
("http://www.nyheder.tv2.dk/.")
("http://www.nyheder.tv2.dk/.")
("www.tv2.dk/nyheder")
("www.tv2.dk/nyheder/")
("www.tv2.dk/nyheder/.")
("www.tv2.dk/nyheder/..")
("https://www.tv2.dk///nyheder///index.html")
;

#else 
static const StringVecT				TestUrls = boost::assign::list_of 
("https://www.tv2.dk/nyheder/index.html?login=ml")
("https://www.tv2.dk/nyheder/index.html?login=ml&password=mypasswd")
;
#endif
void test_Url()
{
	cout<<"Testing Url class"<<endl;
//	namespace fs = boost::filesystem;
//	fs::path p("/home/ml/") / fs::path("test_Url");	
//	fs::path p("C:\\Documents and Settings\\mlu") ;	
//	p /= fs::path("test_Url");
//	fs::path p = cpaf::filesystem::special_dirs::home() / fs::path("test_Url");

	for ( StringVecT::const_iterator it = TestUrls.begin(); it != TestUrls.end(); ++it ) {
		cout<<"Test             : "<<*it<<endl;		
		Url Url(*it);
		cout<<"parsed_string    : "<<Url.parsed_string()<<endl; 
		cout<<"Protocol         : "<<Url.protocol()<<endl; 
		cout<<"Domain           : "<<Url.domain_as_string()<<endl; 
		cout<<"Top Domain       : "<<Url.top_domain()<<endl; 
		cout<<"2nd Level Domain : "<<Url.second_level_domain()<<endl; 
		cout<<"Sub Domains      : "<<Url.sub_domains()<<endl; 
		cout<<"Path             : "<<Url.path()<<endl; 
// 		cout<<"Save path        : "<<Url.savePath()<<endl; 
		cout<<"Parameters       : "<<Url.parameters_as_string()<<endl; 
		cout<<"hash             : "<<Url.hash()<<endl; 
		if ( Url.parsed_string() != Url.string() ) {
			cout << boost::format ( "ERROR: correct string, parsed_string:\n%1%\n%2%\n" ) % Url.string() % Url.parsed_string();
		}
//		fs::path p1 = p /  Url.savePath();
//		fs::create_directories( p1 );
		cout<<endl;
	}
}



class TestUrlClass {
public:
	TestUrlClass() {
		printf("TestUrlClass\n");
		test_Url();
	}
};


// parse_domain: www.tv2.dk?login=ml&password=mypasswd
// END parse_domain: k?login=ml&password=mypasswd
// parse_path: ?login=ml&password=mypasswd
// parse_parameters: ?login=ml&password=mypasswd

// parse_domain: www.tv2.dk#?login=ml&password=mypasswd
// END parse_domain: k#?login=ml&password=mypasswd
// parse_path: #?login=ml&password=mypasswd
// END parse_path: k#?login=ml&password=mypasswd
// parse_parameters: k#?login=ml&password=mypasswd

