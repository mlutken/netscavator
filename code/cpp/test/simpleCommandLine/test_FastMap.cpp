#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <boost/unordered_map.hpp>


template <typename KEY, typename DATA, typename TO_UNSIGNED_TYPE_PRED, typename UNSIGNED_TYPE=unsigned int>
class vector_map
{
public:
    typedef UNSIGNED_TYPE           unsigned_type_t;
    typedef KEY                     key_type_t;
    typedef DATA                    data_type_t;
    typedef TO_UNSIGNED_TYPE_PRED   to_unsigned_type_pred_t;

    explicit vector_map( const unsigned_type_t& maxVectorSize )
        : m_maxVectorSize(maxVectorSize)
        , m_vectorData(maxVectorSize)
        , m_mapData()
    {

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

    typedef std::vector<vector_data_type_t>         vector_type_t;
    typedef std::map<key_type_t, data_type_t>       map_type_t;

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

    const data_type_t&   getReferenceToData (const key_type_t& key ) const
    {
        const unsigned_type_t index = to_unsigned_type_pred_t()(key);
        if ( index < max_vector_size() ) {
            return referenceToVectorData(index);
        }
        else {
            return m_mapData[key];
        }
    }

    data_type_t&   getReferenceToData (const key_type_t& key )
    {
        const unsigned_type_t index = to_unsigned_type_pred_t()(key);
        if ( index < max_vector_size() ) {
            return referenceToVectorData(index);
        }
        else {
            return m_mapData[key];
        }
    }

    void    addDataToVector ( const unsigned_type_t& index, const data_type_t& d )
    {
        m_vectorData[index].hasData = true;
        m_vectorData[index].data    = d;
    }

    void    removeDataFromVector ( const unsigned_type_t& index, const data_type_t& d )
    {
        m_vectorData[index].hasData = false;
    }

    // ---------------------
    // --- PRIVATE: Data ---
    // ---------------------
    unsigned_type_t             m_maxVectorSize;
    vector_type_t               m_vectorData;
    map_type_t                  m_mapData;

    unsigned_type_t             m_vectorSize;

};


struct TestKey
{
    unsigned int primaryID;
    unsigned int secondaryID;
};

bool operator< (const TestKey& lhs, const TestKey& rhs)
{
    return  (lhs.primaryID < rhs.primaryID) ||
            ( (lhs.primaryID == rhs.primaryID) && (lhs.secondaryID < rhs.secondaryID) )
            ;
}

struct TestKeyToIntPred
{
    unsigned int operator ()(const TestKey& key )
    {
        return key.primaryID;
    }
};


typedef vector_map<TestKey, std::string, TestKeyToIntPred> MyFastMapT;

void test_FastMap(int argc, char** argv)
{
    printf("test_FastMap\n");
    MyFastMapT map(100);
    printf("map.max_vector_size(): %d\n", map.max_vector_size());


}


