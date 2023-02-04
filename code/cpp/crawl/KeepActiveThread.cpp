//#include "KeepActiveThread.h"
//#include <iostream>
//#include <boost/format.hpp>
//#include "ScriptMiner.h"
//#include "scriptcrawl_private.h"


//static void thread_sleep(int iSecs )
//{
//	boost::xtime xt;
//	boost::xtime_get(&xt, boost::TIME_UTC);
//	xt.sec += iSecs;
//	boost::thread::sleep(xt);
//}

//KeepActiveThread::KeepActiveThread(int iIntervalSecs, ScriptMiner& miner)
// :	m_iIntervalSecs(iIntervalSecs),
// 	m_Miner(miner),
// 	m_bExit(false)
  
//{
//	printf( "KeepActiveThread::KeepActiveThread: %p\n" , this );
//}

//KeepActiveThread::~KeepActiveThread()
//{
//	printf( "KeepActiveThread DESTRUCTOR: %p\n" , this );
//}

//void KeepActiveThread::operator()()
//{
//	bool bMiningDone = false;
//	using namespace boost;
//	while (1) {
//    //boost::this_thread::sleep(boost::posix_time::milliseconds(25));
//		this_thread::sleep(posix_time::seconds(m_iIntervalSecs));
//		if ( bMiningDone ) {
//			printf ( "KeepActiveThread: EXIT\n" );
//		 	return;
//		}
//		bMiningDone = m_Miner.keepActive();
//	}
//};


//void KeepActiveThread::sleep( int iSecs )
//{
//	boost::xtime xt;
//	boost::xtime_get(&xt, boost::TIME_UTC);
//	xt.sec += iSecs;
//	boost::thread::sleep(xt);
//	printf("KeepActiveThread: currentLoadingUri()  is '%s' ...\n", m_Miner.currentLoadingUri().c_str() );
//}

//void KeepActiveThread::exit()
//{
//	m_bExit = true;
//}



//LoadUrlWaitThread::LoadUrlWaitThread(ScriptMiner& miner, const std::string& sUrl )
// : m_Miner(miner)
// , m_sUrl(sUrl)
//{
//	printf( "LoadUrlWaitThread CONSTRUCTOR: %p\n", this );
//}

//LoadUrlWaitThread::~LoadUrlWaitThread()
//{
//	printf( "LoadUrlWaitThread DESTRUCTOR: %p\n", this );
//}

//void LoadUrlWaitThread::operator()()
//{
//	printf( "LoadUrlWaitThread start %s\n", m_sUrl.c_str() );
//// 	m_Miner.loadURI(m_sUrl);
//	bool bMiningDone = false;
//	using namespace boost;
//	for ( int i = 0; i < 10; i++ ) {
//		this_thread::sleep( posix_time::milliseconds(500) );
//		printf( "LoadUrlWaitThread ...\n" );
//		if ( bMiningDone ) {
//			printf( "LoadUrlWaitThread: EXIT A\n" );
//		 	return;
//		}
//	}
//	printf( "LoadUrlWaitThread: EXIT B\n" );

//};

