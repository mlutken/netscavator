#ifndef STATUSFILE_H
#define STATUSFILE_H

#include <string>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class ScriptMiner;

namespace crawl {
class ScriptMinerIF;

class StatusFile
{
public:

    // --------------------------------------------
    // --- PUBLIC: Constructors, init functions ---
    // --------------------------------------------
    StatusFile  ( const boost::filesystem::path& outputDir, const std::string& fileName, ScriptMinerIF* pMiner );
    ~StatusFile ();

    const std::string&  fileName    () const                            { return m_fileName;        }
    void                fileNameSet ( const std::string& fileName )     { m_fileName = fileName;    }

    // ------------------------------
    // --- PUBLIC: File functions ---
    // ------------------------------
    void    writeFile   ();
    bool    readFile    ();

    // --------------------------------
    // --- PUBLIC: Access functions ---
    // --------------------------------
    template<class Type>
    Type get (const std::string& propertyPath, const Type& defaultValue ) const
    {
        return m_ptree.get<Type>( propertyPath, defaultValue  );
    }

    boost::posix_time::ptime get (const std::string& path, const boost::posix_time::ptime& defaultValue ) const;


    std::string scriptStatus() const;
    void scriptStatusSet(const std::string& scriptStatus);

private:
    std::string                     m_fileName;
    ScriptMinerIF*                  m_pMiner;
    boost::property_tree::ptree     m_ptree;
    std::string                     m_scriptStatus;
};

} // END namespace crawl

#endif // STATUSFILE_H
