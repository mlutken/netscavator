#ifndef PHP_EMBEDDING_CALLBACKS_H
#define PHP_EMBEDDING_CALLBACKS_H
#include <boost/function.hpp>
#include <loki/Singleton.h>

struct PhpEmbedCallbacks {
    typedef boost::function< int  ( struct _sapi_module_struct *sapi_module ) > StartShutdownFunctorT;
    typedef boost::function< int  ( const char* str, unsigned int strLength ) > WriteFunctorT;
    typedef boost::function< void ( const char* str                         ) > LogMsgFunctorT;
    typedef boost::function< void ( void* ) >                                   FlushFunctorT;

    bool                        logToStdOut = false;
    StartShutdownFunctorT       startUpFun;
    StartShutdownFunctorT       shutDownFun;
    WriteFunctorT               writeFun;
    LogMsgFunctorT              logMsgFun;
    FlushFunctorT               flushFun;
};

typedef Loki::SingletonHolder<PhpEmbedCallbacks, Loki::CreateStatic>	g_phpEmbedCallbacks;

#endif // PHP_EMBEDDING_CALLBACKS_H
