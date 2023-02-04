#ifndef CRAWL_DATAWRITERJSON_H
#define CRAWL_DATAWRITERJSON_H

#include <DataWriterIF.h>
#include <fstream>
#include <boost/filesystem.hpp>

namespace crawl {

class DataWriterJson : public DataWriterIF
{
public:
    DataWriterJson( const boost::filesystem::path& outputDir, const std::string sBaseOutputName );
    virtual ~DataWriterJson();

private:
    // ---------------------------------
    // --- PRIVATE: Helper functions ---
    // ---------------------------------
    const std::string   fileName            ();
    void                outputLineToStream  ( std::string sLine );
    void                outputIndention     ( int iIndentLevel );
    void                ensureOpen          ();

    // ------------------------------------
    // --- PRIVATE: Writer do_functions ---
    // ------------------------------------
    virtual void    do_close                    () override;
    virtual void    do_restart                  () override;
    virtual void    do_configOutputEncloseCDATA (bool bDoEncloseInCDATA) override;
    virtual void    do_beginMining              () override;
    virtual void    do_endMining                () override;
    virtual void    do_pushContext              (const std::string& newContext, const std::string& prevContext,
                                                 int iIndentLevel, size_t contextCount ) override;
    virtual void    do_popContext               (const std::string& sContext, int indentLevel, size_t contextCount) override;
    virtual void    do_outputValueDirect        (const std::string& fieldName, const std::string& sValue, int indentLevel,
                                                 size_t valuesCount ) override;
    virtual void    do_outputList               (const std::string& fieldName, const std::vector<std::string> &list
                                                , int indentLevel, size_t valuesCount) override;


    // ----------------------------
    // --- PRIVATE: Member data ---
    // ----------------------------
    boost::filesystem::path m_outputDir;
    bool                    m_bDoEncloseInCDATA;
    std::string             m_sBaseOutputName;
    std::fstream            m_os;
    int                     m_iIndentLevel;
};

} // namespace crawl

#endif // CRAWL_DATAWRITERJSON_H
