#include <iostream>
//#include <boost/process.hpp>
#include "url_functions.h"

#ifdef USE_CURL
#include <cUrl/cUrl.h>
#endif

 

namespace crawl { 


#ifdef USE_CURL
namespace {
struct InitLibCUrlHelper
{
	InitLibCUrlHelper( ) { cUrl_global_init(  CURL_GLOBAL_ALL ); }
	~InitLibCUrlHelper( ) { cUrl_global_cleanup(); }
};

static InitLibCUrlHelper initLibCUrlHelperDummyInstance = InitLibCUrlHelper();
} // end unamed namespace




static size_t writeMemoryCallback(void* pData, size_t iSize, size_t iNmemb, void* pDstStruct )
{
	size_t iRealSize = iSize * iNmemb;
//	std::string* psPageData = (std::string*) pDstStruct;
	str_ptr_t* psPageData  = (str_ptr_t*) pDstStruct;
	(*psPageData)->append( (const char*)pData, iRealSize );
	return iRealSize;
}


/** Download content of URL (page) to a string using libcUrl.
\return Exit status from libcUrl. */
str_ptr_t download_Url ( 
	const Url& Url  	///< 
	) 
{
	
	str_ptr_t psPageData (new std::string);
//	std::string* psPageData (new std::string);
	CURL* hEasy;
	CURLcode iResCode;
	hEasy = cUrl_easy_init();
	if ( hEasy ) { 
		std::string sUrl = Url.string();
		cUrl_easy_setopt( hEasy, CURLOPT_URL, sUrl.c_str() );
		cUrl_easy_setopt( hEasy, CURLOPT_WRITEFUNCTION, writeMemoryCallback ); 
		cUrl_easy_setopt( hEasy, CURLOPT_WRITEDATA, (void *)&psPageData );
		cUrl_easy_setopt( hEasy, CURLOPT_NOPROGRESS, 1);
		cUrl_easy_setopt( hEasy, CURLOPT_USERAGENT, "libcUrl-agent/1.0" );
		cUrl_easy_setopt( hEasy, CURLOPT_HEADER, 1 ); 
		iResCode = cUrl_easy_perform( hEasy );
		cUrl_easy_cleanup( hEasy );
	}
	return str_ptr_t(psPageData);
}

#endif


/** Download content of URL (page) to a string. */
// str_ptr_t download_url_wget	( 
// 	const Url& Url 
// )
// {
// 	namespace bp = ::boost::process;
// 	str_ptr_t psPageData (new std::string);
// 	bp::command_line cl("wget");
// 	cl.argument( std::string("-q"));
// 	cl.argument( std::string("-T"));
// 	cl.argument( std::string("10"));
// 	cl.argument( std::string("-t"));
// 	cl.argument( std::string("3"));
// 	cl.argument( std::string("-O"));
// 	cl.argument( std::string("-"));
// 	cl.argument( Url.string() );
// 	
// 	bp::launcher l;
// 	l.set_stdout_behavior(bp::redirect_stream);
// 	l.set_merge_out_err(true);
// 	bp::child c = l.start(cl);
// 	
// 	bp::pistream& is = c.get_stdout();
// 	std::string line;
// 	while (std::getline(is, line)) {
// 		line.append("\n");
// 		psPageData->append( line );
// 	}
// 	bp::status s = c.wait();
// 
// 	return psPageData;
// }


/** Download content of URL (page) to a string. */
// int	download_url_wget	( 
// 	std::string const & sUrl, 		///< [in] Url to download 
// 	std::string& sData )			///< [out] String to place resulting/downloaded data ind
// {
// 	namespace bp = ::boost::process;
// 	bp::command_line cl("wget");
// 	cl.argument( std::string("-q"));
// 	cl.argument( std::string("-T"));
// 	cl.argument( std::string("10"));
// 	cl.argument( std::string("-t"));
// 	cl.argument( std::string("3"));
// 	cl.argument( std::string("-O"));
// 	cl.argument( std::string("-"));
// 	cl.argument( sUrl );
// 	
// 	bp::launcher l;
// 	l.set_stdout_behavior(bp::redirect_stream);
// 	l.set_merge_out_err(true);
// 	bp::child c = l.start(cl);
// 	
// 	bp::pistream& is = c.get_stdout();
// 	std::string line;
// 	while (std::getline(is, line)) {
// 		sData.append( line + "\n" );
// 	}
// 	bp::status s = c.wait();
// 	return s.exit_status();
// }


/** Download content of URL (page) to a string.
\return Exit status from wget. */
/*int download_Url( 	
	const			std::string& sUrl,	///< [in]
	bool			bQuiet,				///< [in]
	std::string&	sDest				///< [out]
)
{ 
	namespace bp = ::boost::process;
	bp::command_line cl("wget");
	if ( bQuiet ) cl.argument( std::string("-q"));
//	cl.argument( std::string("--output-file=wgetlog.txt"));
	cl.argument( std::string("-T"));
	cl.argument( std::string("10"));
	cl.argument( std::string("-t"));
	cl.argument( std::string("3"));
	cl.argument( std::string("-O"));
	cl.argument( std::string("-"));
	cl.argument( sUrl );
	
	bp::launcher l;
	l.set_stdout_behavior(bp::redirect_stream);
	l.set_merge_out_err(true);
	bp::child c = l.start(cl);
	
	bp::pistream& is = c.get_stdout();
	std::string line;
	while (std::getline(is, line)) {
		line.append("\n");
		sDest.append( line );
	}
	bp::status s = c.wait();

	return s.exit_status();
}*/
 
/** Download content of URL (page) to specified filename.
\todo Finish download_Url() function so it works!
\return Exit status from wget. */
// int download_Url( 	
// 	const							std::string& sUrl,	///< [in]  
// 	bool							bQuiet,				///< [in]
// 	const boost::filesystem::path	filePath			///< 
// )
// {
// 	namespace bp = ::boost::process;
// 	bp::command_line cl("wget");
// 	if ( bQuiet ) cl.argument( std::string("-q"));
// 	cl.argument( std::string("-O"));
// 	cl.argument( std::string("-"));
// 	cl.argument( sUrl );
// 	
// 	bp::launcher l;
// 	l.set_stdout_behavior(bp::redirect_stream);
// 	//l.set_merge_out_err(true);
// 	l.set_work_directory( filePath.branch_path().string() );
// 	bp::child c = l.start(cl);
// 	
// 	bp::pistream& is = c.get_stdout();
// 	std::string line;
// 	while (std::getline(is, line))
// 		std::cout << "Got line from child: " << line << std::endl;
// 
// 	bp::status s = c.wait();
// 
// 	if (s.exited() && s.exit_status() == EXIT_SUCCESS)
// 		std::cout << "Directory updated successfully." << std::endl;
// 	else
// 		std::cout << "Update failed." << std::endl;
// 	std::cout << std::endl;
// 
// 	return s.exit_status();
// }


 


/** Check to see if URL points to a valid page.
\return True if link works, false otherwise. */
// bool linkValid(
// 	const std::string& sUrl		///< [in]
// )
// {
// 	return true;
// }


// boost::process::child 
// openUrl( 	
// 	const std::string& sUrl		///< [in] Url to read
// )
// 
// {
// 	namespace bp = ::boost::process;
// 	bp::command_line cl("wget");
// 	cl.argument( std::string("-O"));
// 	cl.argument( std::string("-"));
// 	cl.argument( sUrl );
// 	
// 	bp::launcher l;
// 	l.set_stdout_behavior(bp::redirect_stream);
// //	l.set_merge_out_err(true);
// 	return l.start(cl);
// 	
// //	bp::pistream& is = c.get_stdout();
// //	return is;
// }



} // END namespace crawl



// namespace {
// static WidgetPtr		MyWidget_Create() { return new MyWidget; }
// 
// static int MyWidget_Register_Type() {
// 	G::Instance().WidgetFactory.Register("MyWidget", MyWidget_Create); 
// 	return 0;
// }
// 
// static MyWidget_Dummy_Int = MyWidget_Register_Type();
// } // end unamed namespace






#if 0

struct MemoryStruct {
	char* pMemory;
	size_t iSize;
};
 
/* There might be a realloc() out there that doesn't like reallocing NULL pointers, so we take care of it here */
static void* safeRealloc(void* pData, size_t iSize )
{
	if ( pData )	return realloc( pData, iSize);
	else			return malloc( iSize );
}
 

static size_t writeMemoryCallback2(void* pData, size_t iSize, size_t iNmemb, void* pDstStruct )
{
//	printf("writeMemoryCallback2(void* pData, size_t iSize, size_t iNmemb, void* pUserp): (%p, %i, %i, %p)\n", pData, iSize, iNmemb, pDstStruct );
	size_t iRealSize = iSize * iNmemb;
	struct MemoryStruct* pMem = (struct MemoryStruct*) pDstStruct;
 
	pMem->pMemory = (char*)safeRealloc(pMem->pMemory, pMem->iSize + iRealSize + 1);
	if (pMem->pMemory) {
		memcpy(&(pMem->pMemory[pMem->iSize]), pData, iRealSize );
		pMem->iSize += iRealSize;
		pMem->pMemory[pMem->iSize] = 0;	// NULL termination
	}
	return iRealSize;
}

/** Download content of URL (page) to a string using libcUrl.
\return Exit status from libcUrl. */
str_ptr_t download_Url2 ( 
	const Url& Url  	///< 
	) 
{
	struct MemoryStruct memChunk;
	memChunk.pMemory	= NULL; /* we expect realloc(NULL, size) to work */
 	memChunk.iSize 		= 0;    /* no data at this point */	
	
	str_ptr_t psPageData (new std::string);
	CURL* hEasy;
	CURLcode iResCode;
	hEasy = cUrl_easy_init();
	if ( hEasy ) { 
//		cUrl_easy_setopt( hEasy, CURLOPT_URL, Url.string().c_str() );
		std::string sUrl = Url.string();
		//sUrl = "http://home.dk";
		cUrl_easy_setopt( hEasy, CURLOPT_URL, sUrl.c_str() );
		cUrl_easy_setopt( hEasy, CURLOPT_WRITEFUNCTION, writeMemoryCallback2 ); 
		cUrl_easy_setopt( hEasy, CURLOPT_WRITEDATA, (void *)&memChunk );
		cUrl_easy_setopt( hEasy, CURLOPT_NOPROGRESS, 1);
		cUrl_easy_setopt( hEasy, CURLOPT_USERAGENT, "libcUrl-agent/1.0" );
//		cUrl_easy_setopt ( hEasy, CURLOPT_VERBOSE, true );
		iResCode = cUrl_easy_perform( hEasy );
		cUrl_easy_cleanup( hEasy );
	}
	psPageData->assign( memChunk.pMemory, memChunk.iSize );
	//std::cout << "ml:" << *psPageData << std::endl;
  	if ( memChunk.pMemory )	free( memChunk.pMemory );	
	return psPageData;
}



#endif

