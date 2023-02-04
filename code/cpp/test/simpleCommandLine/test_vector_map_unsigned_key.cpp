#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <boost/unordered_map.hpp>


template <typename DATA>
class sparse_vector
{
public:
    typedef unsigned int            unsigned_type_t;
    typedef DATA                    data_type_t;

    explicit sparse_vector( const unsigned_type_t& maxVectorSize )
        : m_maxVectorSize(maxVectorSize)
        , m_vectorData(maxVectorSize)
        , m_mapData()
    {

    }

    void    erase ( const unsigned_type_t& index )
    {
        removeData(index);
    }

    const data_type_t&   operator[] (const unsigned_type_t& index ) const
    {
        return getReferenceToData (index ) ;
    }

    data_type_t&   operator[] (const unsigned_type_t& index )
    {
        return getReferenceToData (index ) ;
    }


    // -------------------------------------
    // --- PUBLIC: Simple info functions ---
    // -------------------------------------
    unsigned_type_t  max_vector_size    () const { return m_maxVectorSize;  }
    unsigned_type_t  vector_size        () const { return m_vectorSize;     }
    unsigned_type_t  map_size           () const { return m_mapData.size(); }
    unsigned_type_t  size               () const { return vector_size() + map_size(); }

private:
    // -------------------------
    // --- PRIVATE: Typedefs ---
    // -------------------------
    struct vector_data_type_t
    {
        bool            hasData;
        data_type_t     data;
        vector_data_type_t() : hasData(false), data() {}
        explicit vector_data_type_t( const data_type_t& d) : hasData(true), data(d) {}
    };

    typedef std::vector<vector_data_type_t>             vector_type_t;
    typedef std::map<unsigned_type_t, data_type_t>      map_type_t;

    // ---------------------------------
    // --- PRIVATE: Helper functions ---
    // ---------------------------------
    const data_type_t&   referenceToVectorData ( const unsigned_type_t& index ) const
    {
        return m_vectorData[index];
    }

    data_type_t&   referenceToVectorData ( const unsigned_type_t& index )
    {
        m_vectorData[index].hasData = true;
        return m_vectorData[index].data;
    }

    const data_type_t&   getReferenceToData (const unsigned_type_t& index ) const
    {
        if ( index < max_vector_size() ) {
            return referenceToVectorData(index);
        }
        else {
            return m_mapData[index];
        }
    }

    data_type_t&   getReferenceToData (const unsigned_type_t& index )
    {
        if ( index < max_vector_size() ) {
            return referenceToVectorData(index);
        }
        else {
            return m_mapData[index];
        }
    }

    void    addData( const unsigned_type_t& index, const data_type_t& d )
    {
        if ( index < max_vector_size() ) {
            addDataToVector(index,d);
        }
        else {
            m_mapData.insert( std::make_pair(index,d) );
        }
    }

    void    addDataToVector ( const unsigned_type_t& index, const data_type_t& d )
    {
        m_vectorData[index].hasData = true;
        m_vectorData[index].data    = d;
    }

    void    removeData ( const unsigned_type_t& index )
    {
        if ( index < max_vector_size() ) {
            removeDataFromVector(index);
        }
        else {
            m_mapData.erase(index);
        }
    }

    void    removeDataFromVector ( const unsigned_type_t& index )
    {
        m_vectorData[index].hasData = false;
    }

    unsigned_type_t     countElemsInVector() const
    {
        unsigned_type_t iCount = 0;
        for ( unsigned_type_t i = 0; i < m_maxVectorSize; ++i ) {
            if ( m_vectorData[i].hasData ) iCount++;
        }
        return iCount;
    }

    // ---------------------
    // --- PRIVATE: Data ---
    // ---------------------
    unsigned_type_t             m_maxVectorSize;
    vector_type_t               m_vectorData;
    map_type_t                  m_mapData;

    unsigned_type_t             m_vectorSize;

};




typedef sparse_vector<std::string> MyVec1T;

void test_sparse_vector(int argc, char** argv)
{
    printf("test_FastMap\n");
    MyVec1T map(100);
    printf("map.max_vector_size(): %d\n", map.max_vector_size());


}


