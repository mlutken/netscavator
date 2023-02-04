// MultipleReaderWriteQueue.cpp : Defines the entry point for the console application.
//

#ifdef _WIN
#include "stdafx.h"
#endif

#include <vector>
#include <iostream>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/cstdint.hpp>

typedef boost::shared_mutex                         MutexT;
typedef boost::unique_lock< boost::shared_mutex >   UniqueLockT;
//typedef DC::Shared::CriticalSection               MutexT;
//typedef DC::Shared::CriticalSection::Lock         UniqueLockT;

// ---------------------------
// --- atomic_operations.h ---
// ---------------------------


// ----------------------------------------------
// --- SingleWriterSingleReaderLocklessFifo.h ---
// ----------------------------------------------

template <typename T, class Allocator = std::allocator<T> >
class SingleWriterSingleReaderLocklessFifo
{
private:
  typedef std::vector<T, Allocator >    QueueVec_t;
public:
  // ------------------------
  // --- PUBLIC: Typedefs ---
  // ------------------------
  typedef T                                     value_type;
  typedef boost::uint32_t                       size_type;
  typedef Allocator                             allocator_type;
  typedef typename QueueVec_t::difference_type  difference_type;
  typedef typename QueueVec_t::reference        reference;
  typedef typename QueueVec_t::const_reference  const_reference;
  typedef typename QueueVec_t::pointer          pointer;
  typedef typename QueueVec_t::const_pointer 	const_pointer;

  explicit SingleWriterSingleReaderLocklessFifo ( size_type queueSize )
    : m_queue(queueSize)
    , m_writeIndex(0)
    , m_readIndex(0)
  {

  }

  SingleWriterSingleReaderLocklessFifo ( size_type queueSize, const allocator_type& allocator )
    : m_queue(queueSize, allocator)
    , m_writeIndex(0)
    , m_readIndex(0)
  {

  }

  bool  push ( const T& v )
  {
    size_type nextWriteIndex = incIndex(m_writeIndex);
    if ( nextWriteIndex != m_readIndex ) {
      m_queue[m_writeIndex] = v;
      m_writeIndex = nextWriteIndex;
      return true;
    }
    return false;
  }


  bool  pop ()
  {
    if ( empty () ) return false;
    m_readIndex = incIndex (m_readIndex);
    return true;
  }

  T&  front ()
  {
    return m_queue[m_readIndex];
  }

  bool full () const
  {
     size_type writeCheck = incIndex(m_writeIndex);
     return (writeCheck == m_readIndex);
  }

  bool empty () const
  {
     return (m_writeIndex == m_readIndex);
  }


private:
  // -----------------------------
  // PRIVATE: Helper functions ---
  // -----------------------------
  size_type    incIndex ( size_type index ) const { return (index +1) % m_queue.size(); } 

  // ------------------------
  // PRIVATE: Member data ---
  // ------------------------
  volatile size_type  m_writeIndex;
  QueueVec_t          m_queue;      // Queue declared between the two indexes which hopefully avoids "false sharing"
  volatile size_type  m_readIndex;

};


// ---------------------------------------
// --- MutipleWriterSingleReaderFifo.h ---
// ---------------------------------------


/** 
Fifo to support an (unspecified) number of writers/producers and a single reader/consumer.
The write ( push(elem) ) functions blocks other writes but not the reader. */
template <typename T, class Allocator = std::allocator<T> >
class MutipleWriterSingleReaderFifo
{
private:
  typedef std::vector<T, Allocator >    QueueVec_t;
public:
  // ------------------------
  // --- PUBLIC: Typedefs ---
  // ------------------------
  typedef T                                     value_type;
  typedef boost::uint32_t                       size_type;
  typedef Allocator                             allocator_type;
  typedef typename QueueVec_t::difference_type  difference_type;
  typedef typename QueueVec_t::reference        reference;
  typedef typename QueueVec_t::const_reference  const_reference;
  typedef typename QueueVec_t::pointer          pointer;
  typedef typename QueueVec_t::const_pointer 	const_pointer;

  explicit MutipleWriterSingleReaderFifo ( size_type queueSize )
    : m_queue(queueSize)
    , m_writeIndex(0)
    , m_readIndex(0)
  {

  }

  MutipleWriterSingleReaderFifo ( size_type queueSize, const allocator_type& allocator )
    : m_queue(queueSize, allocator)
    , m_writeIndex(0)
    , m_readIndex(0)
  {

  }

  bool  push ( const T& v )
  {
    UniqueLockT lock(m_writeGuard);
    size_type nextWriteIndex = incIndex(m_writeIndex);
    if ( nextWriteIndex != m_readIndex ) {
      m_queue[m_writeIndex] = v;
      m_writeIndex = nextWriteIndex;
      return true;
    }
    return false;
  }


  bool  pop ()
  {
    if ( empty () ) return false;
    m_readIndex = incIndex (m_readIndex);
    return true;
  }

  T&  front ()
  {
    return m_queue[m_readIndex];
  }

  bool full () const
  {
     size_type writeCheck = incIndex(m_writeIndex);
     return (writeCheck == m_readIndex);
  }

  bool empty () const
  {
     return (m_writeIndex == m_readIndex);
  }


private:
  // ---------------------
  // PRIVATE: Typedefs ---
  // ---------------------

  // -----------------------------
  // PRIVATE: Helper functions ---
  // -----------------------------
  MutipleWriterSingleReaderFifo(MutipleWriterSingleReaderFifo const&);
  MutipleWriterSingleReaderFifo& operator=(MutipleWriterSingleReaderFifo const&);        

  //bool    tryIncWriteIndex ( size_type& oldWriteIndex ) 
  //{ 
  //  UniqueLockT lock(m_incWriteIndexGuard);
  //  oldWriteIndex = m_writeIndex;
  //  size_type nextWriteIndex = incIndex(m_writeIndex);
  //  if ( nextWriteIndex != m_readIndex ) {
  //    m_writeIndex = nextWriteIndex;
  //    return true;
  //  }
  //  return false; 
  //} 


  size_type    incIndex ( size_type index ) const { return (index +1) % m_queue.size(); } 

  // ------------------------
  // PRIVATE: Member data ---
  // ------------------------
  volatile size_type  m_writeIndex;
  QueueVec_t          m_queue;      // Queue declared between the two indexes which hopefully avoids "false sharing"
  volatile size_type  m_readIndex;
  mutable MutexT      m_writeGuard;

};


// --- ---

template <typename T>
struct DefaultModuloPolicy
{
  unsigned int  getModuloVal( const T& val ) const { return static_cast<unsigned int>(val); }
};


template <typename T, template <typename T, class Allocator> class FifoClass, class ModuloPolicy, class Allocator = std::allocator<T> >
class ModuloFifo
{
private:
  typedef FifoClass<T, Allocator >    Fifo_t;

public:
  // ------------------------
  // --- PUBLIC: Typedefs ---
  // ------------------------
  typedef T                                     value_type;
  typedef boost::uint32_t                       size_type;
  typedef Allocator                             allocator_type;
  typedef typename Fifo_t::difference_type      difference_type;
  typedef typename Fifo_t::reference            reference;
  typedef typename Fifo_t::const_reference      const_reference;
  typedef typename Fifo_t::pointer              pointer;
  typedef typename Fifo_t::const_pointer 	    const_pointer;

  explicit ModuloFifo ( size_type queueSize, size_type moduloBase )
    : m_fifos( moduloBase, 0 )
    , m_moduloPolicy()
  {
    for ( int i = 0 ; i < m_fifos.size() ; ++i )
    {
      m_fifos[i] = new Fifo_t(queueSize);
    }
  }

  ModuloFifo ( size_type queueSize, size_type moduloBase, const allocator_type& allocator )
    : m_fifos( moduloBase, 0 )
    , m_moduloPolicy()
  {
    for ( int i = 0 ; i < m_fifos.size() ; ++i )
    {
      m_fifos[i] = new Fifo_t(queueSize);
    }
  }

  ~ModuloFifo ()
  {
    for ( int i = 0 ; i < m_fifos.size() ; ++i )
    {
      delete m_fifos[i];
    }
  }

  bool  push ( const T& v )
  {
    size_type queueIndex = queueIndexGet(v);
    return m_fifos[queueIndex]->push(v);
  }


  bool  pop ( size_type queueIndex )
  {
    return m_fifos[queueIndex]->pop();
  }

  T&  front ( size_type queueIndex )
  {
    return m_fifos[queueIndex]->front();
  }

  bool full ( size_type queueIndex ) const
  {
     return  m_fifos[queueIndex]->full();
  }

  bool empty ( size_type queueIndex ) const
  {
     return  m_fifos[queueIndex]->empty();
  }


private:
  // ---------------------
  // PRIVATE: Typedefs ---
  // ---------------------
  typedef std::vector< Fifo_t* >       FifoVec_t;

  // -----------------------------
  // PRIVATE: Helper functions ---
  // -----------------------------
  ModuloFifo(ModuloFifo const&);
  ModuloFifo& operator=(ModuloFifo const&);        

  size_type    queueIndexGet ( const T& v ) const 
  {
    size_type moduloVal = m_moduloPolicy.getModuloVal(v);
    return moduloVal % m_fifos.size(); 
  } 

  // ------------------------
  // PRIVATE: Member data ---
  // ------------------------
  FifoVec_t         m_fifos;
  ModuloPolicy      m_moduloPolicy;

};



// ---------------
// --- Testing ---
// ---------------

using namespace std;


struct MyRec
{
  MyRec() : m_uic(0), m_val(0) {}
  MyRec( unsigned int uic, unsigned int val ) : m_uic(uic), m_val(val) {}

  boost::uint32_t m_uic;
  boost::uint32_t m_val;
};

struct MyRecModuloPolicy
{
  unsigned int  getModuloVal( const MyRec& val ) const { return val.m_uic; }
};


std::ostream& operator<< ( std::ostream& os, const MyRec& myRec  ) 
{ 
  os << myRec.m_uic << " " << myRec.m_val; 
  return os;
}


typedef SingleWriterSingleReaderLocklessFifo<MyRec> Fifo1_t;
typedef MutipleWriterSingleReaderFifo<MyRec>        Fifo2_t;
typedef ModuloFifo<MyRec, SingleWriterSingleReaderLocklessFifo, MyRecModuloPolicy> ModuloFifo1_t;
typedef ModuloFifo<MyRec, MutipleWriterSingleReaderFifo, MyRecModuloPolicy> ModuloFifo2_t;



void SingleWriterSingleReaderLocklessFifo_test1()
{
  Fifo2_t fifo1(4);
  cout << "fifo1.empty(): " << fifo1.empty() << " fifo1.full(): " << fifo1.full() << "  front(): " << fifo1.front() << endl;
  fifo1.push(MyRec(1,1));
  cout << "fifo1.empty(): " << fifo1.empty() << " fifo1.full(): " << fifo1.full() << "  front(): " << fifo1.front() << endl;
  fifo1.push(MyRec(2,2));
  cout << "fifo1.empty(): " << fifo1.empty() << " fifo1.full(): " << fifo1.full() << "  front(): " << fifo1.front() << endl;
  fifo1.push(MyRec(3,3));
  cout << "fifo1.empty(): " << fifo1.empty() << " fifo1.full(): " << fifo1.full() << "  front(): " << fifo1.front() << endl;
  fifo1.push(MyRec(4,4));
  cout << "fifo1.empty(): " << fifo1.empty() << " fifo1.full(): " << fifo1.full() << "  front(): " << fifo1.front() << endl;
  fifo1.pop();
  cout << "fifo1.empty(): " << fifo1.empty() << " fifo1.full(): " << fifo1.full() << "  front(): " << fifo1.front() << endl;
  fifo1.pop();
  cout << "fifo1.empty(): " << fifo1.empty() << " fifo1.full(): " << fifo1.full() << "  front(): " << fifo1.front() << endl;
  fifo1.pop();
  cout << "fifo1.empty(): " << fifo1.empty() << " fifo1.full(): " << fifo1.full() << "  front(): " << fifo1.front() << endl;
  fifo1.pop();
  cout << "fifo1.empty(): " << fifo1.empty() << " fifo1.full(): " << fifo1.full() << "  front(): " << fifo1.front() << endl;
}


void ModuloFifo_test1()
{
  ModuloFifo2_t fifo1(4, 2);
  cout << "fifo1.empty(0): " << fifo1.empty(0) << " fifo1.full(0): " << fifo1.full(0) << "  front(0): " << fifo1.front(0) << endl;
  cout << "fifo1.empty(1): " << fifo1.empty(1) << " fifo1.full(1): " << fifo1.full(1) << "  front(1): " << fifo1.front(1) << endl << endl;
  fifo1.push(MyRec(1,1));
  cout << "fifo1.empty(0): " << fifo1.empty(0) << " fifo1.full(0): " << fifo1.full(0) << "  front(0): " << fifo1.front(0) << endl;
  cout << "fifo1.empty(1): " << fifo1.empty(1) << " fifo1.full(1): " << fifo1.full(1) << "  front(1): " << fifo1.front(1) << endl << endl;
  fifo1.push(MyRec(2,2));
  fifo1.push(MyRec(3,3));
  cout << "fifo1.empty(0): " << fifo1.empty(0) << " fifo1.full(0): " << fifo1.full(0) << "  front(0): " << fifo1.front(0) << endl;
  cout << "fifo1.empty(1): " << fifo1.empty(1) << " fifo1.full(1): " << fifo1.full(1) << "  front(1): " << fifo1.front(1) << endl << endl;
  fifo1.push(MyRec(4,4));
  fifo1.push(MyRec(5,5));
  cout << "fifo1.empty(0): " << fifo1.empty(0) << " fifo1.full(0): " << fifo1.full(0) << "  front(0): " << fifo1.front(0) << endl;
  cout << "fifo1.empty(1): " << fifo1.empty(1) << " fifo1.full(1): " << fifo1.full(1) << "  front(1): " << fifo1.front(1) << endl << endl;

  fifo1.pop(0);
  fifo1.pop(1);
  cout << "fifo1.empty(0): " << fifo1.empty(0) << " fifo1.full(0): " << fifo1.full(0) << "  front(0): " << fifo1.front(0) << endl;
  cout << "fifo1.empty(1): " << fifo1.empty(1) << " fifo1.full(1): " << fifo1.full(1) << "  front(1): " << fifo1.front(1) << endl << endl;

  fifo1.pop(0);
  fifo1.pop(1);
  cout << "fifo1.empty(0): " << fifo1.empty(0) << " fifo1.full(0): " << fifo1.full(0) << "  front(0): " << fifo1.front(0) << endl;
  cout << "fifo1.empty(1): " << fifo1.empty(1) << " fifo1.full(1): " << fifo1.full(1) << "  front(1): " << fifo1.front(1) << endl << endl;

  fifo1.pop(0);
  fifo1.pop(1);
  cout << "fifo1.empty(0): " << fifo1.empty(0) << " fifo1.full(0): " << fifo1.full(0) << "  front(0): " << fifo1.front(0) << endl;
  cout << "fifo1.empty(1): " << fifo1.empty(1) << " fifo1.full(1): " << fifo1.full(1) << "  front(1): " << fifo1.front(1) << endl << endl;
}

//template <typename T, template <typename T, class Allocator> class FifoClass, class ModuloPolicy, class Allocator = std::allocator<T> >
//class ModuloFifo



// ------------------------
// --- Threaded Testing ---
// ------------------------
const boost::uint32_t g_packetsToSendPerWriteThreadCount    = 3;
const boost::uint32_t g_writerThreadCount                   = 4;
const boost::uint32_t g_packetsToSendCount                  = g_writerThreadCount*g_packetsToSendPerWriteThreadCount;
const boost::uint32_t g_moduloBase                          = 2;      // Same as number of reader threads
const boost::uint32_t g_maxQueueSize                        = 4;
MutexT                g_incSequencenumberGuard;

ModuloFifo2_t g_fifo(g_maxQueueSize, g_moduloBase);

#ifdef _WIN
__declspec( align( 4 ) )boost::uint32_t g_sequenceNumber = 0;
#else
boost::uint32_t g_sequenceNumber = 0;
#endif

boost::uint32_t getNextSequenceNumber()
{
    UniqueLockT lock(g_incSequencenumberGuard);
    boost::uint32_t oldVal = g_sequenceNumber;
    ++g_sequenceNumber;
    return oldVal;
}

void writerThread()
{
    for (boost::uint32_t i= 0; i < g_packetsToSendPerWriteThreadCount; ++i ) {
        boost::uint32_t val = getNextSequenceNumber();
        boost::uint32_t uic = val;
        MyRec rec(uic, val);
        if ( !g_fifo.push(rec) ) {
            printf("Err queue full: %d\n", val);
        }

    }
}

void ModuloFifo_threadTest1()
{
  cout << "g_fifo.empty(0): " << g_fifo.empty(0) << " g_fifo.full(0): " << g_fifo.full(0) << "  front(0): " << g_fifo.front(0) << endl;
  cout << "g_fifo.empty(1): " << g_fifo.empty(1) << " g_fifo.full(1): " << g_fifo.full(1) << "  front(1): " << g_fifo.front(1) << endl << endl;
  g_fifo.push(MyRec(1,1));
  cout << "g_fifo.empty(0): " << g_fifo.empty(0) << " g_fifo.full(0): " << g_fifo.full(0) << "  front(0): " << g_fifo.front(0) << endl;
  cout << "g_fifo.empty(1): " << g_fifo.empty(1) << " g_fifo.full(1): " << g_fifo.full(1) << "  front(1): " << g_fifo.front(1) << endl << endl;
  g_fifo.push(MyRec(2,2));
  g_fifo.push(MyRec(3,3));
  cout << "g_fifo.empty(0): " << g_fifo.empty(0) << " g_fifo.full(0): " << g_fifo.full(0) << "  front(0): " << g_fifo.front(0) << endl;
  cout << "g_fifo.empty(1): " << g_fifo.empty(1) << " g_fifo.full(1): " << g_fifo.full(1) << "  front(1): " << g_fifo.front(1) << endl << endl;
  g_fifo.push(MyRec(4,4));
  g_fifo.push(MyRec(5,5));
  cout << "g_fifo.empty(0): " << g_fifo.empty(0) << " g_fifo.full(0): " << g_fifo.full(0) << "  front(0): " << g_fifo.front(0) << endl;
  cout << "g_fifo.empty(1): " << g_fifo.empty(1) << " g_fifo.full(1): " << g_fifo.full(1) << "  front(1): " << g_fifo.front(1) << endl << endl;

  g_fifo.pop(0);
  g_fifo.pop(1);
  cout << "g_fifo.empty(0): " << g_fifo.empty(0) << " g_fifo.full(0): " << g_fifo.full(0) << "  front(0): " << g_fifo.front(0) << endl;
  cout << "g_fifo.empty(1): " << g_fifo.empty(1) << " g_fifo.full(1): " << g_fifo.full(1) << "  front(1): " << g_fifo.front(1) << endl << endl;

  g_fifo.pop(0);
  g_fifo.pop(1);
  cout << "g_fifo.empty(0): " << g_fifo.empty(0) << " g_fifo.full(0): " << g_fifo.full(0) << "  front(0): " << g_fifo.front(0) << endl;
  cout << "g_fifo.empty(1): " << g_fifo.empty(1) << " g_fifo.full(1): " << g_fifo.full(1) << "  front(1): " << g_fifo.front(1) << endl << endl;

  g_fifo.pop(0);
  g_fifo.pop(1);
  cout << "g_fifo.empty(0): " << g_fifo.empty(0) << " g_fifo.full(0): " << g_fifo.full(0) << "  front(0): " << g_fifo.front(0) << endl;
  cout << "g_fifo.empty(1): " << g_fifo.empty(1) << " g_fifo.full(1): " << g_fifo.full(1) << "  front(1): " << g_fifo.front(1) << endl << endl;
}

#ifdef _WIN
int _tmain(int argc, _TCHAR* argv[])
{
	cout << "hello" << endl;
  //SingleWriterSingleReaderLocklessFifo_test1();
  ModuloFifo_test1();
  return 0;
}
#endif

